
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
  // put your setup code here, to run once:

  for(int i = 8; i <= 10; i++){
    pinMode(i, INPUT);
  }

  pinMode(potPin, INPUT);

  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }

Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
sLeft = digitalRead(sensorLeftPos);
sRight = digitalRead(sensorRightPos);
sMid = digitalRead(sensorMidPos);
 potToTime(analogRead(potPin));
 Serial.println(potToTime(analogRead(potPin))); 

  switch (Mode){
   
    case 1: { 
      search();
      if (Mode != 1){
      break;
      }
        }
    
    case 2: { 
      drive();
       if (Mode != 2){
      break;
      }
        }

    case 3: { 
     //chooseroad();
       if (Mode != 3){
      break;
      }
        }
    
  }

}

int potToTime(float reading){
 return(map(reading, 0, 1023, 0 , 80));
}

void search(){

while(sMid == 0){
   sMid = digitalRead(sensorMidPos);
   digitalWrite(5, HIGH);

   digitalWrite(7, HIGH);
   digitalWrite(6, HIGH);
   delay(500);
   digitalWrite(7, LOW);
   digitalWrite(6, LOW);
   sMid = digitalRead(sensorMidPos);
   delay(500);
   digitalWrite(7, HIGH);
   digitalWrite(6, LOW);
   sMid = digitalRead(sensorMidPos);
   delay(500);
  
   
   Serial.println("Letar"); 
}
 
 Mode = 2;


}


void drive(){

  if (sMid == HIGH){
   //Serial.println("Linje mitten"); 
   digitalWrite(7, HIGH);
   digitalWrite(6, HIGH);
   waittime = 0;

   digitalWrite(4, HIGH);
   digitalWrite(5, LOW);
   


  //}else if ((sLeft + sRight) == 2){ 
   // digitalWrite(6, LOW);
    //digitalWrite(7, LOW);
    //digitalWrite(4, HIGH);
    //digitalWrite(5, LOW);
    //Mode = 3;
  }
  else if (sLeft == HIGH){ 
   // Serial.println("Linje Vänster"); 
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    waittime = 0;

    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    
  }else if (sRight == HIGH){ 
    //Serial.println("Linje höger"); 
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    waittime = 0;

    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
 
 }
  else if((sRight + sMid + sLeft) == 0){
    //jag ger bilen lite tid på sig att hitta tillbaka till linjen, utan att gå in i searchMode
    if(waittime > potToTime(analogRead(potPin))){
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    Mode = 1;

   }else{
    waittime = waittime + 0.1;
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
   // Serial.println(waittime); 
    }
 }
}

//void chooseroad(){
  //  Serial.println("Mode 3");

//}



