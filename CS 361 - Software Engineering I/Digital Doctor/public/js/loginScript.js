var url = "http://flip2.engr.oregonstate.edu"
//var url = "localhost"
var port = ":3310"

function getInfoPage(){
  var req = new XMLHttpRequest();
  var postURL = url + port + "/infoPage";
  req.open("GET", postURL, true);
  req.setRequestHeader('Content-Type', 'application/json');
  
  req.addEventListener('load',function(){
      if(req.status >= 200 && req.status < 400){
        window.location = postURL;
      } 
      else {
        console.log("Error in network request: " + req.statusText);
      }
  });
  req.send(null);
  event.preventDefault();
}

function logInPatient(){
  event.preventDefault();

  var userNameInput = document.getElementById("patientUserName").value;
  var userPasswordInput = document.getElementById("patientPassword").value;
  
  var req = new XMLHttpRequest();
  var payload = {USERNAME:userNameInput, PASSWORD:userPasswordInput};
  
  var postURL = url + port + "/logInPatient";
  req.open("POST", postURL, true);
  req.setRequestHeader('Content-Type', 'application/json');
  
  req.addEventListener('load',function(){
      if(req.status >= 200 && req.status < 400){
        var response = req.responseText;
        console.log(response);
        if (response == "Invalid username or password"){
          document.getElementById("response").textContent = response;
        }
        else{
          getInfoPage();
        }
      } 
      else {
          console.log("Error in network request: " + req.statusText);
      }
  });
  
  req.send(JSON.stringify(payload));
}



function logInDoctor(){
  event.preventDefault();

  var userNameInput = document.getElementById("doctorUserName").value;
  var userPasswordInput = document.getElementById("doctorPassword").value;
  var userPinInput = document.getElementById("doctorPin").value;
  
  var req = new XMLHttpRequest();
  var payload = {USERNAME:userNameInput, PASSWORD:userPasswordInput, PIN:userPinInput};
  
  var postURL = url + port + "/logInDoctor";
  req.open("POST", postURL, true);
  req.setRequestHeader('Content-Type', 'application/json');
  
  req.addEventListener('load',function(){
      if(req.status >= 200 && req.status < 400){
        var response = req.responseText;
        console.log(response);
        if(response == "Invalid username, password, or PIN"){
          document.getElementById("response").textContent = response;
        }
        else{
          getInfoPage();
        }
      } 
      else {
          console.log("Error in network request: " + req.statusText);
      }
  });
  
  req.send(JSON.stringify(payload));
}