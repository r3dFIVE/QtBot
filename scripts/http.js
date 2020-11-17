function get(uri) {
	var resultsStr = ""
	var doc = new XMLHttpRequest();
	doc.open('GET', uri, false);
	doc.onload = function() {
		resultsStr = doc.responseText;
	}
	
	doc.send();	
	bLogInfo(resultsStr)
	return resultsStr
}
