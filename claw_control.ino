#include <Servo.h>

// длина и ширина окна входного изображения с web-камеры
const int WIDTH = 640;
const int HEIGHT = 240;

// пины для щипцов, серво приводов право-лево и серво приводов вверх вниз
const int PIN_FORCEPS = 8;
const int PIN_RIGHT_LEFT_CONTROL = 7;
const int PIN_DOWN_UP_CONTROL = 6;

String message;
bool isParsing = false;


// сервоприводы для клешни
Servo forceps, rightLeftControl, downUpControl;


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

void setup() {
  Serial.begin(9600);
  rightLeftControl.attach(PIN_RIGHT_LEFT_CONTROL);
}

void loop() {
    if (Serial.available()){
      parsingInputMessage(Serial.read(), isParsing, message);
    }
    if (!isParsing){
      rightLeftControl.write(message.toInt());
      isParsing = true;
      message = "";
    }
}
