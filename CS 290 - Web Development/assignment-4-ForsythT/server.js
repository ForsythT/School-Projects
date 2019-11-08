/*
 * Write your server code in this file.
 */
var http = require("http");

var server = http.createServer(function (request, response) {
	response.statusCode = 200;
	response.setHeader("Content-Type", "text/html");
	response.write("<html>");
	response.write("<body>");
	response.write("<h1>Hello!</h1>");
	response.write("<p>");
	response.write("You requested: " + request.url);
	response.write("</p>");
	response.write("</body>");
	response.write("</html>");
	response.end();
});

server.listen(3000);
