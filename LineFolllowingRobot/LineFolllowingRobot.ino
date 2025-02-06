/*
  File:
  Auther:Erik Karlen
  Date: 2025-02-06
  Description: A robot that follows a line using line tracking sensors.

*/
//Initialize global variables
int sensorLeftPos = 8;
int sensorRightPos = 9;
int sensorMidPos = 10;
int potPin = A0;
int sLeft;
int sRight;
int sMid;
int Mode = 1;
float waittime = 0;


void setup() {
  //Assagins all pins
  for (int i = 8; i <= 10; i++) {
    pinMode(i, INPUT);
  }
  for (int i = 3; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(potPin, INPUT);

  // Initialize communications
  Serial.begin(9600);
  
}

void loop() {
  // assaings the different sensor to easily accessible variables
  sLeft = digitalRead(sensorLeftPos);
  sRight = digitalRead(sensorRightPos);
  sMid = digitalRead(sensorMidPos);

  //the switchcase that swithces between the cars differnet modes, search and drive
  switch (Mode) {

    case 1:
      {
        search();
        if (Mode != 1) {
          break;
        }
      }

    case 2:
      {
        drive();
        if (Mode != 2) {
          break;
        }
      }
  }
}

/*
  Takes an input from a potentiometer
  parameters:
  - reading: an analog input from the potentiometer
  Returns: the analog input mapped to 0-80, to easily be used as a waittime
*/
int potToTime(float reading) {
  return (map(reading, 0, 1023, 0, 80));
}
/*
  Controls the motors
  parameters:
  - m1: takes an high or low input and activates the left motor accordingly
  - m2: takes an high or low input and activates the right motor accordingly
  Returns: void
*/
void motorControl(int m1, int m2) {
  digitalWrite(6, m1);
  digitalWrite(7, m2);
}

/*
  Controls the lights
  parameters:
  - l1: takes an high or low input and activates the green light accordingly
  - l2: takes an high or low input and activates the blue light accordingly
  Returns: void
*/
void lightControl(int l1, int l2) {
  digitalWrite(4, l1);
  digitalWrite(5, l2);
}

/*
  Drives the car around while looking for a value from the middle sensor
  parameters: void 
  Returns: void
*/
void search() {

  while (sMid == 0) {
    sMid = digitalRead(sensorMidPos);
    lightControl(0, 1);

    //the car drives forward for 50 for-loop rotations
    for (int i = 0; i <= 50; i++) {
      motorControl(1, 1);
      if (digitalRead(sensorMidPos) == HIGH) {
        break;
      }
    }
    //the car stands still for 50 for-loop rotations
    for (int i = 0; i <= 50; i++) {
      motorControl(0, 0);
      if (digitalRead(sensorMidPos) == HIGH) {
        break;
      }
    }
    //the car drives left for 50 for-loop rotations
    for (int i = 0; i <= 50; i++) {
      motorControl(0, 1);
      if (digitalRead(sensorMidPos) == HIGH) {
        break;
      }
    }
  }
  //switches to drive mode if the middle sensor gets a value
  Mode = 2;
}

/*
  Activates the motors accoridng to which sensor is reading a high value, to make the car follow the line
  parameters:none
  Returns: none
*/
void drive() {

  if (sMid == HIGH) {
    motorControl(1, 1);
    lightControl(1, 0);
    waittime = 0;
  } else if (sLeft == HIGH) {
    motorControl(1, 0);
    lightControl(1, 0);
    waittime = 0;
  } else if (sRight == HIGH) {
    motorControl(0, 1);
    lightControl(1, 0);
    waittime = 0;
  } else if ((sRight + sMid + sLeft) == 0) {

    //if none of the sensors are activated, the program starts a countdown, if none of the sensors are activeted before it finishes, the car switches over to search-mode. The waittime for this coundown is decided by the potentiometer
    if (waittime > potToTime(analogRead(potPin))) {
      motorControl(0, 0);
      Mode = 1;
    
    } else {
    waittime = waittime + 0.1 //the waittime is increased
      lightControl(0, 0);
    }
  }
}

