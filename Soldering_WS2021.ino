//
//  AOZORA Kyodo Center for 2021/9/23
//   Let's make Robot Badge lightening.
//
//   

bool sw;
uint8_t mode; // 0:off, 1:blink, 2:alternate
int  counter;

void setup() {
  // put your setup code here, to run once:
  pinMode(0,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  sw = false;
  mode = 0;
  counter = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  bool swstate = (digitalRead(0) == LOW);
  if (!swstate && sw){
    sw = false;
  }
  if (swstate && !sw){
    sw = true;
    switch (mode){
      case 0:
        mode = 1;
        break;
      case 1:
        mode = 2;
        break;
      default:
      case 2:
        mode = 0;
        PORTB &= ~(_BV(2)|_BV(3));
        break;
    }
  }

  if (mode == 1){
    if ((counter/25)%2){
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
    }
    else {
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
    }
  }
  else if (mode == 2){
    if ((counter/20)%2){
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
    }
    else {
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);
    } 
  }

  delay(10);
  counter += 1;
  if (counter > 1000){
    counter = 0;
  }
}
