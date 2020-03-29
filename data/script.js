function blueButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "blue", true);
    xhttp.send();
}

function greenButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "green", true);
    xhttp.send();
}

function redButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "red", true);
    xhttp.send();
}

function whiteButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "white", true);
    xhttp.send();
}

function restartButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "restart", true);
    xhttp.send();
}
setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("score").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "readScore", true);
    xhttp.send();
}, 2000);

setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("highScore").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "readHighScore", true);
    xhttp.send();
}, 2000);