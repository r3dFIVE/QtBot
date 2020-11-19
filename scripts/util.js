const RunningState = {
	STOPPED: 'Stopped',
	AWAITING_PLAYERS: 'Awaiting Players',
	STARTED: 'Started'
}

const PlayerState = {
	FIRST_ACTION: 'First Action',
	NO_ACTION: 'No Action',
	INVALID_ACTION: 'Invalid Action',
	OK: 'Eveything OK'
}

function shuffleArray(array) {
	var currentIndex = array.length, temporaryValue, randomIndex;

	while (0 !== currentIndex) {
		randomIndex = Math.floor(Math.random() * currentIndex--);
		temporaryValue = array[currentIndex];
		array[currentIndex] = array[randomIndex];
		array[randomIndex] = temporaryValue;
	}

	return array;
}

function getRndInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1) ) + min;
}