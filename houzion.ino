//conections
//const int LM35 = 0;
//const int TEMPERATURE_VALIDATION[2] = {2, 3};

//statements
const int LED = 1;
const int T_LM35 = 2;
const int LED_ON = 1;
const int LED_OFF = 0;

//locals
const int KITCHEN_LIGHT = 3;
const int TV_LIGHT = 4;
const int EAT_LIGHT = 5;

//var
int _operation = 0;
int _value_status = 0;

//flags
bool KITCHEN_LIGHT_STATUS = false;
bool TV_LIGHT_STATUS = false;
bool EAT_LIGHT_STATUS = false;

void setup() {
  Serial.begin(9600);
  //pinMode(TEMPERATURE_VALIDATION[0], OUTPUT);
  //pinMode(TEMPERATURE_VALIDATION[1], OUTPUT);
}

/*void checkTemperature(){
  float value = (analogRead(LM35) * 0.48828125);
  if(value < 25){
    digitalWrite(TEMPERATURE_VALIDATION[1], HIGH);
    digitalWrite(TEMPERATURE_VALIDATION[0], LOW);
  }
  else{
    digitalWrite(TEMPERATURE_VALIDATION[0], HIGH);
    digitalWrite(TEMPERATURE_VALIDATION[1], LOW);
  }
  Serial.println(value);
}*/

void checkSerial(){
  if(Serial.available()){
    int flag = 0;
    String serial_text = readSerial();
    switch(_operation){
      case 1:
        turnKitchenLights(_value_status);
        flag = 1;
        delay(200);
        break;
      case 2:
        turnTVLights(_value_status);
        flag = 1;
        delay(200);
        break;
      case 3:
        turnEatLights(_value_status);
        flag = 1;
        delay(200);
        break;
    }
    Serial.println(serial_text);
    Serial.println(flag);
    Serial.println();
  }
}

void turnKitchenLights(int value){
  value = map(value, 0, 255, 0, 100);
  analogWrite(KITCHEN_LIGHT, value);  
  if(value > 0){
    KITCHEN_LIGHT_STATUS = true;
  }
  else{
    KITCHEN_LIGHT_STATUS = false;
  }
}

void turnTVLights(int value){
  value = map(value, 0, 255, 0, 100);
  analogWrite(TV_LIGHT, value);
  if(value > 0){
    TV_LIGHT_STATUS = true;
  }
  else{
    TV_LIGHT_STATUS = false;
  }
}

void turnEatLights(int value){
  value = map(value, 0, 255, 0, 100);
  analogWrite(EAT_LIGHT, value);
  if(value > 0){
    EAT_LIGHT_STATUS = true;
  }
  else{
    EAT_LIGHT_STATUS = false;
  }
}

String readSerial(){
  String text = "";
  String value = "";
  String operation = "";
  char character;
  bool flag = false;
  bool flag_first = true;
  while(Serial.available() > 0){
    character = Serial.read();
    if(character != '\n'){
      if(flag == true){
        value.concat(character);
      }
      if(character == ':'){
        flag = true;
        flag_first = false;
      }
      if(flag_first == true){
        operation.concat(character);
      }
      text.concat(character);
    }
    delay(10);
  }
  _operation = operation.toInt();
  _value_status = value.toInt();
  return text;
}

void loop() {
  _operation = 0;
  _value_status = 0;
  //checkTemperature();
  checkSerial();
}