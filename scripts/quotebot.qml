import BotApi 1.0

BotScript {

    name: "quoteBot"

    commands: {
		".quotenext" : "quoteNext",
		".quoteprev" : "quotePrev"
    }
	
	event_bindings: [
		{ 
			"binding_type" : "command",
			"command" : ".quote",
			"function" : "quote", 
			"description" : "Gets a quote from the database."
		}
	]
	
	property string randomQuote: "SELECT quote,author,date FROM quotes.quote ORDER BY RAND() LIMIT 1"
	
	property var qry: {}
	
    function quote(context) {
		bLogInfo(context.content)
	
        var db = new SqlDatabase();
		
		if (db.open()) {
			qry = new SqlQuery(db);
		
			var args = context.content.split(" ");
			
			bLogInfo(args)
			
			if (args.length > 1) {
				
				var likeClause = ""
				for (var i = 1; i < args.length; ++i) {
					likeClause += args[i] + " "
				}
				
				likeClause = "%" + likeClause.trim() + "%"

				qry.prepare("SELECT quote,author,date FROM quotes.quote WHERE quote LIKE ?");
				qry.bindValue(0, likeClause);
			} else {
				qry.prepare(randomQuote);
			}
			
			qry.exec();		
			
			if (qry.size() > 1) {
				qry.seek(Math.floor(Math.random() * qry.size()));
			} else if (!qry.next()) {
				return { content: "No quotes found..." }
			} 
			
			context.target_payload = { content: buildQuoteString() }
			
			cCreateMessage(context)	
		}
    }
	
	function buildQuoteString() : string {
		var size = qry.size();
		var pos = qry.at() + 1;
		var quote = `\`Quotes found: ${size}\`` 
					+ `\n**Quote #:**\t${pos} / ${size}`
					+ "\n**Author :**\t" + qry.value(1)
					+ "\n**Date :**\t\t" + qry.value(2)
					+ "\n**Quote:**\t  \`" + qry.value(0) + "\`"
		return quote;
	}
	
	function quoteNext(context) {
		var size = qry.size();
		if (size == 0 || !qry.isValid()) {			
			qry.exec(randomQuote)
		} else if (!qry.next()) {
			qry.seek(0)
		}
		
		context.target_payload = { content: buildQuoteString() }
		
        cCreateMessage(context)		
	}
	
	function quotePrev(context) {
		var size = qry.size();
		if (size == 0 || !qry.isValid()) {
			qry.exec(randomQuote)
		} else if (!qry.previous()) {
			qry.seek(size - 1);
		}
		
		context.target_payload = { content: buildQuoteString() }
		
        cCreateMessage(context)		
	}
}
