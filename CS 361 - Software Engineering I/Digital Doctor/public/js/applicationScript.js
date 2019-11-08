var url = "http://flip2.engr.oregonstate.edu"
//var url = "localhost"
var port = ":3310"

function getFields() {
	var fields = {
		"userName":document.getElementById("userName").value,
		"firstName":document.getElementById("firstName").value,
		"lastName":document.getElementById("lastName").value,
		"city":document.getElementById("city").value,
		"state":document.getElementById("state").value,
		"license":document.getElementById("license").value,
	    "ref1":document.getElementById("ref1").value,
	    "ref2":document.getElementById("ref2").value,
	    "ref3":document.getElementById("ref3").value,
    };

		 if (checkEmptyFields(fields)) {
			application(fields);
			//alert("Application submitted. We will get in touch with you!")
		}
		else {
			alert("Please enter data in all fields.");
		}
}

/**
 * returns false if any field is empty, otherwise true
 */
function checkEmptyFields(fields) {
	return (fields.userName != "" &&
			fields.firstName != "" &&
			fields.lastName != "" &&
			fields.city != "" &&
			fields.state != "" &&
			fields.license != "" &&
			fields.startTime != "" &&
			fields.endTime != "" &&
			fields.ref1 != "" &&
			fields.ref2 != "" &&
			fields.ref3 != ""
			);
}

function application(fields) {
	event.preventDefault();

    var postURL = url + port + "/apply";
    var payload = {};

    var req = new XMLHttpRequest();
  	req.open("POST", postURL, true);
  	req.setRequestHeader("Content-type", "application/json");

    var payload = {};
    payload.userName = fields.userName;
    payload.firstName = fields.firstName;
    payload.lastName = fields.lastName;
    payload.city = fields.city;
    payload.state = fields.state;
    payload.license = fields.license;
    payload.ref1 = fields.ref1;
    payload.ref2 = fields.ref2;
    payload.ref3 = fields.ref3;

    // console.log("Attempting to post " + JSON.stringify(payload))
    req.addEventListener("load", function(){
			if(req.status >= 200 && req.status < 400)
			{
        		var response = req.responseText;
		        console.log(response);
		        document.getElementById("response").textContent = response;
			}
			else
			{
				console.log("Error in network request: " + req.status + " " + req.statusText);
			}
		});

		req.send(JSON.stringify(payload));
}


