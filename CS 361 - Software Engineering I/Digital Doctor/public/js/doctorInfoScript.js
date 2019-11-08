var url = "http://flip2.engr.oregonstate.edu"
//var url = "localhost"
var port = ":3310"

function updateDoctorInfo(){
  //event.preventDefault();

  var hours = document.getElementById("hours").value;
  var specialty = document.getElementById("specialty").value;
  var patientTypes = document.getElementById("patientTypes").value;
  var insTypes = document.getElementById("insTypes").value;
  
  var req = new XMLHttpRequest();
  var payload = {hours:hours, specialty:specialty, patientTypes:patientTypes, insTypes:insTypes};
  
  var postURL = url + port + "/updateDoctorInfo";
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