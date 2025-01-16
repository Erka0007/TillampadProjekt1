
int sensorLeftPos = 8;
int sensorRightPos = 9;
int sensorMidPos = 10;
int sLeft;
int sRight;
int sMid;
int Mode = 1;
float waittime = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(sensorLeftPos, INPUT);
pinMode(sensorRightPos, INPUT);
pinMode(sensorMidPos, INPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);
Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
sLeft = digitalRead(sensorLeftPos);
sRight = digitalRead(sensorRightPos);
sMid = digitalRead(sensorMidPos);

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
     chooseroad();
       if (Mode != 3){
      break;
      }
        }
    
  }

}

void search(){

while(sMid == 0){
   sMid = digitalRead(sensorMidPos);
   digitalWrite(5, HIGH);

   digitalWrite(7, HIGH);
   digitalWrite(8, LOW);
   delay(1000);
   digitalWrite(7, HIGH);
   digitalWrite(8, HIGH);
   delay(1000);
   
   Serial.println("Letar"); 
}
  if(sMid == HIGH){
   Mode = 2;
 }

}


void drive(){

  if (sMid == HIGH){
   Serial.println("Linje mitten"); 
   digitalWrite(7, HIGH);
   digitalWrite(6, HIGH);
   waittime = 0;

   digitalWrite(4, HIGH);
   digitalWrite(5, LOW);

  }else if ((sLeft + sRight) = 2){ 
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    Mode = 3;
  }
  else if (sLeft == HIGH){ 
    Serial.println("Linje Vänster"); 
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    waittime = 0;

    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);

  }else if (sRight == HIGH){ 
    Serial.println("Linje höger"); 
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    waittime = 0;

    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
 }
  else if((sRight + sMid + sLeft) == 0){
    //jag ger bilen lite tid på sig att hitta tillbaka till linjen, utan att gå in i searchMode
    if(waittime > 20){
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    Mode = 1;

   }else{
    waittime = waittime + 0.1;
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    Serial.println(waittime); 
    }
 }
}

void chooseroad(){
   if

}



