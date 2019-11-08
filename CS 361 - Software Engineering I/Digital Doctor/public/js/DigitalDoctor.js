var url = "http://flip2.engr.oregonstate.edu"
//var url = "localhost"
var port = ":3310"

// User account creation
function register() {
    event.preventDefault();

    var username = document.getElementById("signupemail").value;
    var password = document.getElementById("signuppassword").value;
    var usertype = document.getElementById("newUserAccountForm").elements["userTypeSelector"].value;

    var req = new XMLHttpRequest();
    var payload = {
        "username":username,
        "password":password,
        "usertype":usertype,
    };

    var postURL = url + port + "/create";
    req.open("POST", postURL, true);
    req.setRequestHeader('Content-Type', 'application/json');
    
    req.addEventListener('load',function(){
        if(req.status >= 200 && req.status < 400){
            var response = req.responseText;
            console.log(response);
            document.getElementById("response").textContent = response;
        } 
        else {
            console.log("Error in network request: " + req.statusText);
        }
    });

    req.send(JSON.stringify(payload));
}