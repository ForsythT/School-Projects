var express = require('express');
var path = require('path');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var bodyParser = require('body-parser');
var request = require('request');
var mysql = require('./dbcon.js')


app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3310);
app.use(express.static('public'));

var LOGGEDINUSERID = null;
var DOP = null;

/********** Routes for URLs **********/

// Note, this function console.logs various database calls to check data; all queries can be removed for final product.
app.get('/',function(req, res, next){
	res.render('loginPage');

  console.log("Currently logged in = " + LOGGEDINUSERID + "DOP = " + DOP);

  //log the loginDatabase data to console
  mysql.pool.query('SELECT * FROM `loginDatabase`', function (err, rows, fields) {
    console.log(rows);
  })

  // log the fields in the given table
  mysql.pool.query('SELECT * FROM `doctorApplication`', function (err, rows, fields) {
    console.log(rows);
  })

  // log the complete list of tables to console
  // mysql.pool.query('SELECT table_name FROM information_schema.tables', function (err, rows, fields) {
  //     console.log(rows);
  // });

});
app.get('/register', function(req, res, next) {
    res.render('register');
});
app.get('/docApp', function(req, res, next) {
  res.render('docApp');
});


app.get('/infoPage', function(req, res, next) {
	var context = {};

  if (DOP == "P"){
    mysql.pool.query('SELECT * FROM `patientInfo` WHERE id=?', [LOGGEDINUSERID], function(err, rows) {      
    if (err) {
      console.log(err);
      next(err);
        return;
      }
    context.results = rows;
    res.render('patientInfo', context);
    });
  }
  else if(DOP == "D"){
    //NEED TO CREATE DOCTOR INFO TABLE
    mysql.pool.query('SELECT * FROM `doctorInfo` WHERE id=?', [LOGGEDINUSERID], function(err, rows) {      
    if (err) {
      console.log(err);
      next(err);
        return;
      }
    context.results = rows;
    res.render('doctorInfo', context);
    });
  }
});

/********** Routes for database access **********/

//Logging in as patient -- fully tested and operational as of 3/10/18
app.post('/logInPatient', function(req, res, next){
  var context = {};
  var userName = req.body.USERNAME;
  var password = req.body.PASSWORD;

  mysql.pool.query('SELECT UserID FROM `loginDatabase` WHERE UserName=? AND Password=? AND DorP!=?',[userName,password,"D"], function(err, rows, fields){
    if(err){
      next(err);
      return;
    }

    if (rows == ''){
    	console.log("Invalid username or password " + userName + " " + password);
      res.send("Invalid username or password");
    }
    else{
      context.results = rows;
      var id = context.results[0].UserID;
      LOGGEDINUSERID = id;
      DOP = "P";
    	console.log("Valid user " + userName + " " + password + " " + id + " " + LOGGEDINUSERID);
      res.send("Valid patient! " + LOGGEDINUSERID);
    }
  });
});

//Logging in as doctor -- fully tested and operational as of 3/10/18
app.post('/logInDoctor', function(req, res, next){
  var context = {};
  var userName = req.body.USERNAME;
  var password = req.body.PASSWORD;
  var pin = req.body.PIN;

  mysql.pool.query('SELECT UserID FROM `loginDatabase` WHERE UserName=? AND Password=? AND Pin=?',[userName,password,pin], function(err, rows, fields){
    if(err){
      next(err);
      return;
    }

    if (rows == ''){
      console.log("Invalid username, password, or PIN " + userName + " " + password + " " + pin);
      res.send("Invalid username, password, or PIN");
    }
    else{
      context.results = rows;
      var id = context.results[0].UserID;
      LOGGEDINUSERID = id;
      DOP = "D";
      //context.user = JSON.stringify(rows); 
      console.log("Valid user " + userName + " " + password + " " + pin);
      res.send("Valid doctor! " + LOGGEDINUSERID);
    }
  });
});


// Creating a new account
app.post('/create', function (req, res) {
    var context = {};
    var username = req.body.username;
    var password = req.body.password;
    var usertype = req.body.usertype;
    var pin = Math.floor((Math.random() * 9999) + 1);

    mysql.pool.query("SELECT * FROM `loginDatabase` WHERE UserName = ?", username,
    function (err, rows, fields) {
        if (rows.length == 0) {
            if (usertype == "P") {
                pin = null;
            }

            var queryArray = [username, password, usertype, pin];
            var queryStrInsert = "INSERT INTO `loginDatabase` (`UserName`, `Password`, `DorP`, `pin`) VALUES (?,?,?,?)"

            mysql.pool.query(queryStrInsert, queryArray, function(err, res) {
              if (err) {
                console.log(err);
                next(err);
                return;
              }

              console.log("New account for " + username);
              res.send("New account created");
            });
        }
    });
});

//Applying to be a doctor with this service
app.post('/docApp', function(req, res, next) {
  var queryArray = [
    req.body.userName,
    req.body.firstName,
    req.body.lastName,
    req.body.city,
    req.body.state,
    req.body.license,
    req.body.ref1,
    req.body.ref2,
    req.body.ref3
  ];

var queryStrInsert = "INSERT INTO doctorApplication (\
`userName`, `firstName`, `lastName`, `city`, `state`, `license`, `ref1`, `ref2`, `ref3`) \
VALUES (?,?,?,?,?,?,?,?,?)";

  mysql.pool.query(queryStrInsert, queryArray, function(err, res) {
    if (err) {
      console.log(err);
      next(err);
      return;
    }

    console.log("New doctor application for " + userName);
    res.send("New doctor application for " + userName);
  });
});

app.post('/updatePatientInfo', function(req, res, next) {
	var queryArray = [
		req.body.medHx,
		req.body.insID,
		req.body.insCo,
		req.body.card,
		req.body.addr,
		req.body.city,
		req.body.state,
		req.body.zip,
		req.body.pharm,
		req.body.pharmZip,
    	req.body.consent,
    	LOGGEDINUSERID
	];

	mysql.pool.query("UPDATE patientInfo SET medHx=?, insID=?, insCo=?, card=?, addr=?, city=?, state=?, zip=?, pharm=?, pharmZip=?, consent=? WHERE id=?", queryArray, function(err, res) {
		if (err) {
			console.log(err);
			next(err);
			return;
		}

		console.log("Data saved for user " + LOGGEDINUSERID);
		//res.send("Dava saved for user " + LOGGEDINUSERID);
	});
});

app.post('/updateDoctorInfo', function(req, res, next) {
  var queryArray = [
    req.body.hours,
    req.body.specialty,
    req.body.patientTypes,
    req.body.insTypes,
    LOGGEDINUSERID
  ];

  mysql.pool.query("UPDATE doctorInfo SET hours=?, specialty=?, patientTypes=?, insTypes=? WHERE id=?", queryArray, function(err, res) {
    if (err) {
      console.log(err);
      next(err);
      return;
    }

    console.log("Data saved for user " + LOGGEDINUSERID);
    //res.send("Dava saved for user " + LOGGEDINUSERID);
  });
});

/********** Utility routes **********/
// Page not found
app.use(function(req,res){
  res.status(404);
  res.render('404');
});

// Server error
app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});