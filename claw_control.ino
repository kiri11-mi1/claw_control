#include <Servo.h>

// длина и ширина окна входного изображения с web-камеры
const int WIDTH = 640;
const int HEIGHT = 240;

// пины для щипцов, серво приводов право-лево и серво приводов вверх вниз
const int PIN_FORCEPS = 5;
const int PIN_HORIZONTAL_CONTROL = 7;
const int PIN_VERTICAL_CONTROL = 6;

String message;
bool isParsing = false;


// сервоприводы для клешни
Servo forceps, horizontalControl, verticalControl;


char parsingInputMessage(char input, bool &isParsing, String &message){
  if (!(input == '\n' || input == '|r')){
 
    if (input == ';')
      isParsing = false;

    if (input == '#')
      isParsing = true;

    if (input != '#' && isParsing)
      message += input;

  }
  return 0;
}

String getNumbersData(String message){
  String result = "";
  for (int i = 1; i < message.length(); i++){
    result += message[i];
  }
  return result;
}

void setup() {
  Serial.begin(9600);
  horizontalControl.attach(PIN_HORIZONTAL_CONTROL);
  forceps.attach(PIN_FORCEPS);
  verticalControl.attach(PIN_VERTICAL_CONTROL);
}

void loop() {
    if (Serial.available()){
      parsingInputMessage(Serial.read(), isParsing, message);
    }
    if (!isParsing){
      if (message[0] == 'C'){
        // клешня
        forceps.write(getNumbersData(message).toInt());
      }
      if (message[0] == 'H'){
        // по горизонтали
        horizontalControl.write(getNumbersData(message).toInt());
      }
      if (message[0] == 'V'){
        // по вертикали
        verticalControl.write(getNumbersData(message).toInt());
      }
      
      isParsing = true;
      message = "";
    }
}
