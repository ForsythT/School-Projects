
function logInPatient(){
  var userNameInput = document.getElementById("patientUserName").value;
  var userPasswordInput = document.getElementById("patientPassword").value;
  //var queryString;
  //queryString = "SELECT UserID FROM loginDatabase WHERE UserName = \""+userNameInput+"\" AND Password = \""+userPasswordInput+"\"";  
  var req = new XMLHttpRequest();
  var payload = {USERNAME:userNameInput, PASSWORD:userPasswordInput};
 // var payload = {newQuery:queryString};
  req.open("POST", "http://flip3.engr.oregonstate.edu:3310/logInPatient", true);
  req.setRequestHeader('Content-Type', 'application/json');
  req.addEventListener('load',function(){
      if(req.status >= 200 && req.status < 400){
        console.log("Data Sent!");
        //alert("Data Sent!");
        //event.preventDefault();

      } 
      else {
          console.log("Error in network request: " + req.statusText);
          //event.preventDefault();
      }
  });
  req.send(JSON.stringify(payload));
  //event.preventDefault();
}


function logInDoctor(){
  var userNameInput = document.getElementById("doctorUserName").value;
  var userPasswordInput = document.getElementById("doctorPassword").value;
  var userPinInput = document.getElementById("doctorPin").value;
  //var queryString;
  //queryString = "SELECT UserID FROM loginDatabase WHERE UserName = \""+userNameInput+"\" AND Password = \""+userPasswordInput+"\"";  
  var req = new XMLHttpRequest();
  var payload = {USERNAME:userNameInput, PASSWORD:userPasswordInput, PIN:userPinInput};
 // var payload = {newQuery:queryString};
  req.open("POST", "http://flip3.engr.oregonstate.edu:3310/logInDoctor", true);
  req.setRequestHeader('Content-Type', 'application/json');
  req.addEventListener('load',function(){
      if(req.status >= 200 && req.status < 400){
        console.log("Data Sent!");
        //alert("Data Sent!");
        //event.preventDefault();

      } 
      else {
          console.log("Error in network request: " + req.statusText);
          //event.preventDefault();
      }
  });
  req.send(JSON.stringify(payload));
  //event.preventDefault();
}


function checkInput(){
	var body = document.body;
	document.getElementById("patientLogIn").addEventListener("click", function(){
       var userNameInput = document.getElementById("patientUserName").value;
       var userPasswordInput = document.getElementById("patientPassword").value;
       alert(userPasswordInput);
		
		
	});
	document.getElementById("doctorLogIn").addEventListener("click", function(){
		
	});

}

//checkInput();

//http://flip3.engr.oregonstate.edu:3309/
