const int buttonPin = 13;
const int ldrPin = A0;
String lastState = "";

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void buttonPress(int x, int y){
  for (int i=0; i<x; i++){
    digitalWrite(buttonPin, HIGH); 
    delay(y);
    digitalWrite(buttonPin, LOW);
    delay(y);
  }
  if(x == 3){
    delay(5000);
  }
}

void consoleMessage(){
  int ldrStatus = analogRead(ldrPin);
  String statusText = "";
  String formattedLdrStatus = "(" + String(ldrStatus) + ")\n";
  if(lastState == "dark"){
    statusText = ", dimming the lights ";
  }
  else{
    statusText = ", turning up the lights ";
  }
  Serial.print("It's " + lastState + statusText + formattedLdrStatus);
}

void loop() {
  int ldrStatus = analogRead(ldrPin); 
  if (ldrStatus <= 200){
    if(lastState != "dark"){
      lastState = "dark";
      buttonPress(2,175);
      consoleMessage();
    }
  }
  else
  {
    if(ldrStatus >= 250){
      if (lastState != "bright"){
        lastState = "bright";
        buttonPress(3,175);
        consoleMessage();
      }
    }  
  }
}