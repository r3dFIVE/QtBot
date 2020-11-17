import BotApi 1.0

BotScript {

	name: "helloWorld"
	
	commands: {
		".hello" : "world"		
	}
	
	function world(context) {				
		context.target_payload.content = `Hello ${context.author.username}, to my bot world!`  
		cCreateMessage(context)
	}
}
