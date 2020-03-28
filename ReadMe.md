# Modern Simon Game

Simon is an electronic game of memory skills. The device creates a series of tones and lights and requires a user to repeat the sequence in a given time. This Simon game is a little bit different from the classic one: instead of having physical buttons you can push, you virtual buttons, *i.e.* you need to click, either with your computer or smartphone, on the web application's buttons.

## Installation

To install the game, you'll need:

* a ESP8266;
* an IDE (either Arduino IDE or VSCode's extension platformIO);
* 4 LEDs and 4 resistors.

The electronic schema is quite simple since you don't need physical buttons:

![electronicSchema](img/adafruit_project_webapp.png "Electonic Schema")

You just to pull my repository, upload the file system (with the css, JS and HTML files), build main.cpp and upload the binary file.

## Interface