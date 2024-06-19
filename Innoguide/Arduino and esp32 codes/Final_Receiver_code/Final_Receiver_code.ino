#include <esp_now.h>
#include <WiFi.h>
#include "driver/ledc.h"

#define DIR1 15
#define PWM1 2
#define DIR2 0
#define PWM2 4

const int freq = 5000;
const int resolution = 8;
const int PWM1Channel = 2;
const int PWM2Channel = 0;

 

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int jystkX;
  int jystkY;
  int spd;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("analX = ");
  Serial.println(myData.jystkX);
  Serial.print("analY = ");
  Serial.println(myData.jystkY);
  Serial.print("Mspeed = ");
  Serial.println(myData.spd);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  
  
  // configure LED PWM functionalitites
  ledcSetup(PWM1Channel, freq, resolution);
  ledcSetup(PWM2Channel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM1, PWM1Channel);
  ledcAttachPin(PWM2, PWM2Channel);




  
}
 
void loop() {
  int x = myData.jystkX;
  int y = myData.jystkY;
  int w = myData.spd;
  
  int wpwm = map(w, 0, 4095, 50, 150);

  int var = 0 ;

  if((x>1600 && x<2000)&&(y>1700 && y<2000)){
    var = 0;
  }

  else if((x>800 && x<2000)&&(y>=0 && y<50)){
    var = 1;
  }

  else if((x>800 && x<2000)&&(y>3000 && y<=4095)){
    var = 2;
  }

  else if((x>=0 && x<200)&&(y>1000 && y<2500)){
    var = 3;
  }

  else if((x>3000 && x<=4095)&&(y>1000 && y<2500)){
    var = 4;
  }

  else{
    var = 5;
  }

  switch(var){

    case 0:
    motorStop(wpwm);
    Serial.println("motorStop");
    break;

    case 1:
    Forward(wpwm);
    Serial.println("Forward");

    break;

    case 2:
    Backward(wpwm);
    Serial.println("Backward");
    break;

    case 3:
    Leftturn(wpwm);
    Serial.println("LeftTurn");
    break;

    case 4:
    Rightturn(wpwm);
    Serial.println("RightTurn");
    break;

    case 5:
    motorStop1();
    Serial.println("DefalutMotorStop");
    break;

    default:
    motorStop1();
    Serial.println("DefaultMotorStop");
    break;

  }
  
}


void Forward(int k){

  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,LOW);
  
  for(int t = 0; t<k; t++){
  ledcWrite(PWM1Channel, t);
  ledcWrite(PWM2Channel, t);
  delay(10);
	}
}

void Backward(int k){

  digitalWrite(DIR1,HIGH);
  digitalWrite(DIR2,HIGH);
  
  for(int t = 0; t<k; t++){
  ledcWrite(PWM1Channel, t);
  ledcWrite(PWM2Channel, t);
  delay(10);
	}

}

void Rightturn(int k){

  digitalWrite(DIR1,HIGH);
  digitalWrite(DIR2,LOW);
  
  for(int t = 0; t < (k-30); t++){
  ledcWrite(PWM1Channel, t);
  ledcWrite(PWM2Channel, t);
  delay(10);
	}
}

void Leftturn(int k){

  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,HIGH);
  
 for(int t = 0; t < (k-30); t++){
  ledcWrite(PWM1Channel, t);
  ledcWrite(PWM2Channel, t);
  delay(10);
	}

}

void motorStop(int k){

  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,LOW);
  
  for(int t = k; t > 0; t--){
  ledcWrite(PWM1Channel, t);
  ledcWrite(PWM2Channel, t);
  delay(5);
	}

}

void motorStop1(){
  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,LOW);

  ledcWrite(PWM1Channel, 0);
  ledcWrite(PWM2Channel, 0);

}

