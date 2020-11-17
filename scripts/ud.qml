import BotApi 1.0
import "http.js" as HTTP

BotScript {
 	name: "urbandict"
	
	commands: {
		".ud" : "ud",
		".udnext" : "udnext",
		".udprev" : "udprev"
	}
	
	property var baseUri: 'http://api.urbandictionary.com/v0/'
	
	property var results: []
	
	property int pos: 0
	
	function ud(context) {
		
		var args = context.content.split(" ");
		
		console.log(args)
		
		if (args.length > 1) {
			
			var searchTerm = ""
			
			for (var i = 1; i < args.length; ++i) {
				searchTerm += args[i] + " "
			}
			
			var uri = baseUri + 'define?term=' + encodeURI(searchTerm);
			
		} else {
			var uri = baseUri + "random"			
		}
			
		getResults(context, uri);
	} 
	
	function getResults(context, uri) {
		var resultStr = HTTP.get(uri);
		
		if (resultStr.length == 0) {
			cCreateMessage(context.target_payload = { content : "No results found." })
			return
		}

		results = JSON.parse(resultStr).list
		
		pos = 0
		
		sendResult(context, results[pos])
	}
	
	function udnext(context) {
		if (results.length == 0) {
			cCreateMessage(context.target_payload = { content : "No results found." })
			return
		}
		
		if (++pos === results.length) {
			pos = 0
		}
		
		sendResult(context, results[pos])
	}

	function udprev(context) {
		if (results.length == 0) {
			cCreateMessage(context.target_payload = { content : "No results found." })
			return
		}
		
		if (--pos < 0 ) {
			pos = results.length - 1
		}
		
		sendResult(context, results[pos])
	}


	function sendResult(context, result) {
		var displayPos = pos + 1
			
		var message = `\`Results found: ${results.length}\`` 
				+ `\n**Result #:**\t${displayPos} / ${results.length}`
				+ "\n**Date :**\t\t" + result.written_on.substring(0, result.written_on.indexOf('T'))
				+ `\n**Permalink :**\t\`${result.permalink}\``
				+ "\n**Term :**\t\t" + result.word				
				+ "\n**Definition :**\t  \`" + result.definition + "\`"
				+ "\n**Example :**\t  \`" + result.example + "\`"
		
		context.target_payload = { content: message }
		cCreateMessage(context)
	}
}
