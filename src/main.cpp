#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <FS.h>

const char *ssid = "ssidNetwork";
const char *password = "password";

uint8_t randNumbers[100];
int count = 1;
const int blueLed = 14;
const int greenLed = 3;
const int redLed = 12;
const int whiteLed = 13;
uint8_t highScore = 0;
int soundPin = 0;
int stateGreenLed = 0;
int stateRedLed = 0;
int stateWhiteLed = 0;
int stateBlueLed = 0;
unsigned long timeLeft = 1000;
unsigned long timeGiven = 1000;
int timeHigh = 500;
uint8_t correct = 1;
uint8_t score = 0;
int stateRestartButton = 0;
int buttonPressed = -1;
int stateBlueButton = 0;
int stateRedButton = 0;
int stateWhiteButton = 0;
int stateGreenButton = 0;
int blueState = 0;
int redState = 0;
int whiteState = 0;
int greenState = 0;
AsyncWebServer server(80);

void setup() {
  //##################################
  //              Serial
  //##################################
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("\n");

  //##################################
  //              GPIO
  //##################################
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  ledsLow();

  //##################################
  //              SPIFFS
  //##################################
  if(!SPIFFS.begin())
  {
    Serial.println("SPIFFS Error...");
    return;
  }


  //##################################
  //              WIFI
  //##################################
  WiFi.begin(ssid, password);
	Serial.print("Connection in progress...");
	
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}
	
	Serial.println("\n");
	Serial.println("Connection established!");
	Serial.print("IP Adresse: ");
	Serial.println(WiFi.localIP());

  //##################################
  //              Server
  //##################################
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/w3.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  server.on("/blue", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    stateBlueButton = 1;
    request->send(204);
  });

  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    stateRedButton = 1;
    request->send(204);
  });

  server.on("/green", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    stateGreenButton = 1;
    request->send(204);
  });

  server.on("/white", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    stateWhiteButton = 1;
    request->send(204);
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    stateRestartButton = 1;
    request->send(204);
  });

  server.on("/readScore", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    String scoreString = String(score);
    request->send(200, "text/plain", scoreString);
  });

  server.on("/readHighScore", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    String highScoreString = String(highScore);
    request->send(200, "text/plain", highScoreString);
  });

  server.begin();
  Serial.println("Server actif!");
}

void loop() {
  if (!correct){

    ledsHigh();
    // tone(soundPin, 140);
    delay(500);

    ledsLow();
    // noTone(soundPin);
    delay(500);
    score = 0;
    if(stateRestartButton){
      count = 1;
      correct = 1;
      score = 0;
      stateRestartButton = 0;
    }


  }else {

    randNumbers[count - 1] = random(1,5);
    ledsHigh();
    delay(500);
    ledsLow();
    delay(500);

    for(int j = 0; j < count; j++){
      ledsLow();
      ledHigh(randNumbers[j]);
      delay(timeHigh);
      ledsLow();
      delay(timeHigh);
      
      
    }

    ledsLow();

    for (int t = 0; t < count; t++){
      buttonPressed = -1;
      timeLeft = millis();

      while (buttonPressed == -1 && ((millis() - timeLeft) < timeGiven )){
        delay(100);

        blueState = stateBlueButton;
        greenState = stateGreenButton;
        whiteState = stateWhiteButton;
        redState = stateRedButton;

        if (blueState){
          buttonPressed = 1;
          stateBlueButton = 0;
        }else if (greenState){
          buttonPressed = 2;
          stateGreenButton = 0;
        }else if (redState){
          buttonPressed = 3;
          stateRedButton = 0;
        }else if (whiteState){
          buttonPressed = 4;
          stateWhiteButton = 0;
        }
      }
      ledHigh(buttonPressed); 
      delay(timeHigh);  

      if (buttonPressed != randNumbers[t]){
        ledsHigh();
        correct = 0;
        if (highScore < score){
          highScore = score;
        }
        score = 0;
        buttonPressed = -1;
        break;
      }

      ledsLow();
      
    }

    count ++;
    score ++;
    ledsLow();
    delay(100);
    

  }

}

void ledsLow(void){

    digitalWrite(blueLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(whiteLed, LOW);

}

void ledsHigh(void){

  digitalWrite(blueLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
  digitalWrite(whiteLed, HIGH);

}

void ledHigh(int number){
  switch (number){
  case 1:
     digitalWrite(blueLed, HIGH);
    break;
  case 2:
     digitalWrite(greenLed, HIGH);
     break;
  case 3:
     digitalWrite(redLed, HIGH);
     break;
  case 4:
     digitalWrite(whiteLed, HIGH);
     break;
  }
  delay(50);
}