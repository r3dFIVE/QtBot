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
		},
		{ 
			"binding_type" : "command",
			"command" : ".addquote",
			"function" : "addQuote", 
			"description" : "Adds a quote to the database."
		}
	]
	
	property string databaseName: "quotes"
	
	property string tableName: "quotebot"
	
	property string randomQuoteSql: `SELECT quote,author,date FROM ${databaseName}.${tableName} ORDER BY RAND() LIMIT 1`
	
	property string searchQuoteSql: `SELECT quote,author,date FROM ${databaseName}.${tableName} WHERE quote LIKE ?`
	
	property string addQuoteSql: `INSERT INTO ${databaseName}.${tableName} (chan_id, quote, author, date) VALUES (?, ?, ?, ?);`
	
	property var qry: {}
	
	function addQuote(context) {
		var args = context.args;
		
		if (args.length == 1) {
			context.target_payload.content = "You cannot add empty quotes!"			
		} else {
			var db = new SqlDatabase();
			
			if (db.open()) {			
				var sqlQuery = new SqlQuery(db);
				var quote = ""				
				for (var i = 1; i < args.length; ++i) {
					quote += args[i] + " "
				}				
				var dateTime = new Date().toLocaleString(Qt.locale(), 'yyyy-MM-dd hh:mm:ss');				
				sqlQuery.prepare(addQuoteSql);		
				bLogInfo(dateTime);
				
				sqlQuery.bindValue(0, context.channel_id);				
				sqlQuery.bindValue(1, quote);
				sqlQuery.bindValue(2, context.author.username)
				sqlQuery.bindValue(3, dateTime)
				
				if (sqlQuery.exec()) {
					context.target_payload.content = "**Quote Added!**";
				} else {
					var e = new SqlError(sqlQuery.lastError());
					bLogWarning(sqlError.databaseText());
					return
				}
			}
		}
		
		cCreateMessage(context)
	}
	
    function quote(context) {	
        var db = new SqlDatabase();
		
		if (db.open()) {
			qry = new SqlQuery(db);
		
			var args = context.args;
						
			if (args.length > 1) {
				
				var likeClause = ""
				for (var i = 1; i < args.length; ++i) {
					likeClause += args[i] + " "
				}
				
				likeClause = "%" + likeClause.trim() + "%"

				qry.prepare(searchQuoteSql);
				qry.bindValue(0, likeClause);
			} else {
				qry.prepare(randomQuoteSql);
			}
			
			if (!qry.exec()) {
				logSqlError(qry);
				return;
			}		
			
			if (qry.size() > 1) {
				qry.seek(Math.floor(Math.random() * qry.size()));				
				context.target_payload.content = buildQuoteString();
			} else if (qry.next()) {			
				context.target_payload.content = buildQuoteString();
			} else {				
				context.target_payload.content = "No quotes found...";
			}
						
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
		if (isEmpty(qry)) {
			context.content = context.args[0];			
			quote(context);
			return;
		} else if (!qry.next()) {
			qry.seek(0);
		}		
		context.target_payload.content = buildQuoteString();		
        cCreateMessage(context);
	}
	
	function quotePrev(context) {		
		if (isEmpty(qry)) {
			context.content = context.args[0];			
			quote(context);
			return;
		} else if (!qry.previous()) {
			qry.seek(qry.size() - 1);
		}		
		context.target_payload.content = buildQuoteString();		
        cCreateMessage(context);
	}
	
	function isEmpty(obj) {
		for(var prop in obj) {
			if(obj.hasOwnProperty(prop)) {
			  return false;
			}			
		}
		return JSON.stringify(obj) === JSON.stringify({}) || typeof obj === "undefined"
	}
	
	function logSqlError(qry) {
		var e = new SqlError(qry.lastError());
		bLogWarning(e.text());
	}
}
