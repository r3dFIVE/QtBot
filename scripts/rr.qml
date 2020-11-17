import BotApi 1.0

import "util.js" as Util

BotScript {

	///////////////////////////////////////////////////////////////////
	//                     SCRIPT CONFIGURATION                      //
	///////////////////////////////////////////////////////////////////
	
	// chamberCount - the maxim number of possible bullet chambers
	property int chamberCount: 6 							

	// defaultTimer - the default .rrstart timer
	property int defaultTimer: 60

	// turnDuration - the amount of seconds before a player forfeits their turn
	property int turnDuration: 10		

	// maxDeathMinutes - the maximum amount of minutes a player can be "dead" for.
	property int maxDeathMinutes: 5

	// scoreFileName - the absolute or relative path to your score file. Will create new files.
	property var scoreFileName: "rrscore.json"

	///////////////////////////////////////////////////////////////////
	// DO NOT MODIFY BELOW HERE UNLESS YOU KNOW WHAT YOU ARE DOING!! //
	///////////////////////////////////////////////////////////////////

	name: "rr"
	
	commands: {
		".rrstart" : "rrStart",
		".rrstop" : "rrStop",
		".rrjoin" : "rrJoin",
		".rr" : "rr",
		".rrspin" : "rrSpin",
		".rrscore" : "rrScore"
	}
	
	property int roundNum: 0	
	property int playerIndex: 0	
	property var queuedEventId: ""
	property var gameState: Util.RunningState.STOPPED;	
	property var previousPlayerState: Util.PlayerState.OK;
	property var currentPlayers: []
	property var gameScores: []
	property var haveSpunIds: []
	property var deadPlayerIds: []
	property var warnedDeadIds: []
	property int bulletChamberIndex: 0	
	property int currentChamberIndex: 0
	
	property var startGameTimedEvent: {
		"function" : "startGame", 
		"description" : "Starts a game of rr."
	}	
	property var processTurnTimedEvent: {
		"function" : "processTurn", 
		"description" : "Processes and starts a new turn."
	}	
	property var newRoundTimedEvent: {
		"function" : "newRound", 
		"description" : "Starts a new round after player death."
	}	
	property var revivePlayerTimedEvent: {
		"function" : "revivePlayer"
	}
		
	function rrStart(context) {
		if (isPlayerDead(context)) {
			return;
		}
		
		var duration = defaultTimer;
		
		if (context.args.length == 2) {
			duration = parseInt(context.args[1]);
		}
		
		if (gameState != Util.RunningState.STOPPED) {
			if (gameState == Util.RunningState.STARTED) {
				context.target_payload.content = "A game is already being played! Wait until its done then type `.rrstart` to start a new game";
			} else {
				context.target_payload.content = "A new game will be starting shortly. Type `.rrjoin` to play.";
			}
			cCreateMessage(context);
			return;
		}		
		
		gameState = Util.RunningState.AWAITING_PLAYERS;

		context.target_payload.content = `${context.author.username} is starting a new game of **RR** in ${duration} seconds! Type \`.rrjoin\` to play.`
		cCreateMessage(context);
		
		currentPlayers.push({ user_id: context.author.id, username: context.author.username})
		
		startGameTimedEvent.context = context;
		startGameTimedEvent.fire_after = duration;		

		gameScores = [];
		haveSpunIds = [];

		queuedEventId = bQueueTimedEvent(startGameTimedEvent);		
	}
	
	function updateScores(context) {
		let allSavedGuildScores = readScoreFile();
		let guildId = context.guild_id;
		let guildScores = {guild_id: guildId, scores: []}
		let isNewGuild = true;
		for (let i = 0; i < allSavedGuildScores.length; ++i) {
			if (allSavedGuildScores[i].guild_id == guildId) {
				guildScores = allSavedGuildScores[i];
				isNewGuild = false;
				break;
			}
		}	
		
		for (let i = 0; i < gameScores.length; ++i) {
			let playerScore = gameScores[i];
			let isNewPlayer = true;
			for (let j = 0; j < guildScores.scores.length; ++j) {
				if (guildScores.scores[j].user_id == playerScore.user_id) {
					isNewPlayer = false;					
					guildScores.scores[j].wins += playerScore.wins;
					guildScores.scores[j].deaths += playerScore.deaths;
					guildScores.scores[j].forfeits += playerScore.forfeits;					
					break;
				}					
			}
			
			if (isNewPlayer == true) {
				guildScores.scores.push(playerScore);
			} 
		}
		
		if (isNewGuild) {
			allSavedGuildScores.push(guildScores)
		}
		
		let scoreFile = new File(scoreFileName, OpenMode.WriteOnly | OpenMode.Truncate);
		
		if (scoreFile.open()) {
			scoreFile.writeLine(JSON.stringify(allSavedGuildScores, null, 2));
		} else {
			bLogWarning(`Failed to open score file ${scoreFileName}, reason: ${scoreFile.lastError()}`);
		}
	}
	
	function readScoreFile() {
		let scoreFile = new File(scoreFileName, OpenMode.ReadWrite);
		
		let allSavedGuildScores = [];
		
		if (scoreFile.exists() && scoreFile.open()) {
			let scoreString = scoreFile.readAll();
			
			if (scoreString) {
				allSavedGuildScores = JSON.parse(scoreString);
			}
		} else {
			bLogWarning(`Failed to open ${scoreFileName}, reason: ${scoreFile.errorString()}`); 
		}

		return allSavedGuildScores;
	}
	
	function rrStop(context) {
		stopGame(context);	
	}
	
	function rrScore(context) {
		if (gameState == Util.RunningState.STOPPED) {
			let playerScore = {wins: 0, deaths: 0, forfeits: 0}
			let allGuildScores = readScoreFile();
			let guildScores = { guild_id: context.guild_id, scores: [] }
			let playerFound = false;

			for (let i = 0; i < allGuildScores.length; ++i) {
				if (allGuildScores[i].guild_id == context.guild_id) {
					let guildScores = allGuildScores[i].scores;
					for (let j = 0; j < guildScores.length; ++j) {
						if (guildScores[j].user_id == context.user_id) {
							playerScore = guildScores[j];
							playerFound = true;
							break;
						}
					}
				}
				if (playerFound) {
					break;
				}
			}				
			context.target_payload.content = `Score for <@${context.user_id}>:\n**WINS:** \`${playerScore.wins}\` | **DEATHS:** \`${playerScore.deaths}\` | **FORFEITS:** \`${playerScore.forfeits}\``
			cCreateMessage(context);
		}					
	}
	
	function rrJoin(context) {
		if (isPlayerDead(context)) {
			return;
		}
		
		if (gameState != Util.RunningState.AWAITING_PLAYERS) {
			if (gameState == Util.RunningState.STARTED) {
				context.target_payload.content = "A game is already being played! Wait until its done then type `.rrstart` to start a new game";
			} else {
				context.target_payload.content = "No games of RR are currently being played. Type `.rrstart` to start a new game";
			}
			cCreateMessage(context);
			return;
		}
		
		var newPlayer = { user_id: context.author.id, username: context.author.username }
		
		for (let i = 0; i < currentPlayers.length; ++i) {
			if (newPlayer.user_id == currentPlayers[i].user_id) {
				bLogInfo(`Player ${newPlayer.user_id}:${newPlayer.username} is already registered to play.`);
				return;
			}
		}			
		currentPlayers.push(newPlayer);
	}		
	
	function startGame(context) {
		if (currentPlayers.length == 1) {
			context.target_payload.content = `Stopping game, only ${currentPlayers[0].username} registered to play. There's only one way that can end...`;
			cCreateMessage(context);
			stopGame(context);
			return;
		}	
		
		reloadRandomChamber();
		
		gameState = Util.RunningState.STARTED;
						
		context.target_payload.content = `\`${currentPlayers.length}\` players registered. First round starting in 5 seconds...`
		
		cCreateMessage(context);
		
		newRoundTimedEvent.fire_after = 5;
		newRoundTimedEvent.context = context;
		queuedEventId = bQueueTimedEvent(newRoundTimedEvent);
	}
	
	function newRound(context) {
		if (currentPlayers.length == 1) {
			context.target_payload.content = "";
			gameWon(context);
			return;
		}
		
		Util.shuffleArray(currentPlayers)
		
		reloadRandomChamber();
		
		currentChamberIndex = 0;			
		roundNum++;	
		playerIndex = 0;
		previousPlayerState = Util.PlayerState.NO_ACTION;
		
		let playerOrder = ""
		
		for (let i = 0; i < currentPlayers.length; ++i) {
			playerOrder += "\`" + currentPlayers[i].username + "\` ";
		}
		
		context.target_payload.content = `Player order for **Round #${roundNum}**: ${playerOrder}`
		cCreateMessage(context);
		
		bPause(2000);
				
		promptUserTurn(context);
		
		processTurnTimedEvent.fire_after = turnDuration;
		processTurnTimedEvent.context = context;
		queuedEventId = bQueueTimedEvent(processTurnTimedEvent)
	}
	
	function promptUserTurn(context) {
		context.target_payload.content = `<@${currentPlayers[playerIndex].user_id}> you have ${turnDuration} seconds to go... \`.rr\``;
				
		if (!currentPlayerHasSpun()) {
		   context.target_payload.content += ` or \`.rrspin\``;
		}
		
		cCreateMessage(context);
	}
		
	function processTurn(context) {
		if (previousPlayerState != Util.PlayerState.OK) {
			let userId = currentPlayers[playerIndex].user_id;			
			gameScores.push({user_id: userId, wins: 0, deaths: 0, forfeits: 1});
			let killPlayerContext = context;
			delete killPlayerContext.author;
			killPlayerContext.username = currentPlayers[playerIndex].username;
			killPlayerContext.target_payload.content = `<@${userId}> chickened out and forfeits... so I shot them anyway. `;
			killPlayerContext.user_id = userId;
			killPlayer(killPlayerContext)
		}
		
		if (currentPlayers.length == 1) {
			gameWon(context);
			return;
		}
				
		if (++playerIndex >= currentPlayers.length) {
			playerIndex = 0;
		}

		previousPlayerState = Util.PlayerState.NO_ACTION;		
		
		promptUserTurn(context);
		
		processTurnTimedEvent.fire_after = turnDuration;
		processTurnTimedEvent.context = context;
		queuedEventId = bQueueTimedEvent(processTurnTimedEvent)
	}
	
	function gameWon(context) {
		gameScores.push({user_id: currentPlayers[0].user_id, wins: 1, deaths: 0, forfeits: 0});
		context.target_payload.content += `<@${currentPlayers[0].user_id}> wins!!!`
		cCreateMessage(context)
		updateScores(context);
		stopGame(context);
	}
	
	function stopGame(context) {
		killQueuedEvent(context);
		gameState = Util.RunningState.STOPPED;
		currentPlayers.length = 0;
		currentChamberIndex = 0;			
		roundNum = 0;
		playerIndex = 0;
	}
	
	function killQueuedEvent(context) {		
		context.job_id = queuedEventId;		
		bRemoveTimedEventByJobId(context);
		queuedEventId = "";
	}

	function rr(context) {		
		if (gameState != Util.RunningState.STARTED) {
			if (gameState == Util.RunningState.STOPPED) {
				context.target_payload.content = "No games of RR are currently being played. Type `.rrstart` to start a new game";
			} else {
				context.target_payload.content = "A new game will be starting shortly. Type `.rrjoin` to play.";
			}
			cCreateMessage(context);
			return;
		}
		if (isUserTurn(context)) {
			pullTrigger(context);
		}		
	}
	
	function rrSpin(context) {
		if (!isUserTurn(context)) {
			return;			
		} else if (currentPlayerHasSpun()) {
			return;
		} else {
			haveSpunIds.push(currentPlayers[playerIndex].user_id);
		}
		currentChamberIndex = Util.getRndInt(0, 5);
		pullTrigger(context, "BZzzzzzz........ ");
	}
	
	function pullTrigger(context, prefixString) {	
		bLogCritical("playerDies" + JSON.stringify(context));
		killQueuedEvent(context);
		
		previousPlayerState = Util.PlayerState.OK;		
		
		context.target_payload.content = ""
		if (prefixString) {
			context.target_payload.content = prefixString;
		}
		
		if (currentChamberIndex == bulletChamberIndex) {
			playerDies(context);			
		} else {					
			playerLives(context);
		}		
		cCreateMessage(context);
	}
	
	function playerDies(context) {
		bLogCritical("playerDies" + JSON.stringify(context));
		gameScores.push({user_id: currentPlayers[playerIndex].user_id, wins: 0, deaths: 1, forfeits: 0});
		newRoundTimedEvent.fire_after = 2;
		newRoundTimedEvent.context = context;
		queuedEventId = bQueueTimedEvent(newRoundTimedEvent);
		context.target_payload.content = `**BANG!!!**... ${context.author.username} is **dead**.`
		killPlayer(context);
		reloadRandomChamber();
	}
	
	function revivePlayer(context) {
		bLogCritical("revivePlayer" + JSON.stringify(context));
		let idx = deadPlayerIds.indexOf(context.user_id);
		if (idx > -1) {
			deadPlayerIds.splice(idx, 1);
		}
		context.target_payload.mute = false;
		context.target_payload.deaf = false;
		gModifyGuildMember(context);
		context.target_payload.content = `<@${context.user_id}> has risen from the dead... someone needs to put another bullet in them.`;
		cCreateMessage(context)
	}
	
	function killPlayer(context) {
		bLogCritical("killPlayer" + JSON.stringify(context));

		currentPlayers.splice(playerIndex, 1);
		deadPlayerIds.push(context.user_id);
		context.target_payload.mute = true;
		context.target_payload.deaf = true;
		gModifyGuildMember(context);
		let deathMinutes = Util.getRndInt(1, maxDeathMinutes);
		context.target_payload.content += `\n\`Dead for ${deathMinutes} minutes. Dead players can't talk, I got ya muted!\`\n`;
		revivePlayerTimedEvent.fire_after = deathMinutes * 60;
		revivePlayerTimedEvent.description = `${context.username}'s death timer.`;
		revivePlayerTimedEvent.context = context;
		bQueueTimedEvent(revivePlayerTimedEvent);
	}
	
	function playerLives(context) {
		bLogCritical("playerLives" + JSON.stringify(context));
		context.target_payload.content += "**CLICK!!!** Survived another turn...";
		if (++currentChamberIndex == chamberCount) {
			currentChamberIndex = 0;
		}				
		processTurnTimedEvent.fire_after = 1;
		processTurnTimedEvent.context = context;
		queuedEventId = bQueueTimedEvent(processTurnTimedEvent);
	}
	
	function isPlayerDead(context) {
		bLogCritical("isPlayerDead" + JSON.stringify(context));
		bLogCritical("deadPlayerIds" + deadPlayerIds);
		if (deadPlayerIds.includes(context.user_id)) {
			if (!warnedDeadIds.includes(context.user_id)) {
				warnedDeadIds.push(context.user_id);
				context.target_payload.content = "Dead players can't play games...";
				cCreateMessage(context);
			}
			return true;
		}
		return false;
	}
	
	function isUserTurn(context) {
		bLogCritical("isUserTurn" + JSON.stringify(context));
		return context.user_id == currentPlayers[playerIndex].user_id;
	}
	
	function currentPlayerHasSpun() {
		return haveSpunIds.includes(currentPlayers[playerIndex].user_id);
	}
	
	function reloadRandomChamber() {
		currentChamberIndex = 0;
		
		bulletChamberIndex = Util.getRndInt(0, chamberCount - 1);
	}
}
