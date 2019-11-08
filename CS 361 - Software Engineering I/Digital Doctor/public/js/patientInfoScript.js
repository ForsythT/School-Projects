var url = "http://flip2.engr.oregonstate.edu"
//var url = "localhost"
var port = ":3310"

function updatePatientInfo(){
  //event.preventDefault();

  var medHx = document.getElementById("medHx").value;
  var insID = document.getElementById("insID").value;
  var insCo = document.getElementById("insCo").value;
  var creditCard = document.getElementById("creditCard").value;
  var address = document.getElementById("address").value;
  var city = document.getElementById("city").value;
  var state = document.getElementById("state").value;
  var zip = document.getElementById("zip").value;
  var pharm = document.getElementById("pharm").value;
  var pharmZip = document.getElementById("pharmZip").value;
  var consent = document.getElementById("hipaa").value;
  
  var req = new XMLHttpRequest();
  var payload = {medHx:medHx, insID:insID, insCo:insCo, card:creditCard, addr:address, city:city, state:state, zip:zip, pharm:pharm, pharmZip:pharmZip, consent:consent};
  
  var postURL = url + port + "/updatePatientInfo";
  req.open("POST", postURL, true);
  req.setRequestHeader('Content-Type', 'application/json');
  
  req.addEventListener('load',function(){
      if(req.status >= 200 && req.status < 400){
        var response = req.responseText;
        console.log(response);
        var refreshURL = url + port + "/infoPage";
        window.location = refreshURL;
      } 
      else {
          console.log("Error in network request: " + req.statusText);
      }
  });
  
  req.send(JSON.stringify(payload));
}