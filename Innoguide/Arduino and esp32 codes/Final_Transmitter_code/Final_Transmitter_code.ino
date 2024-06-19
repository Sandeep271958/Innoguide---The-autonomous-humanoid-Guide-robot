#include <esp_now.h>
#include <WiFi.h>

#define LEDBUILTIN 2
const int pinX = 33;
const int pinY = 32;
const int pinspd = 35;

int XValue = 0;
int YValue = 0;
int spdValue = 0;


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] =  {0xE4, 0x65, 0xB8, 0x27, 0x63, 0x00};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int jystkX;
  int jystkY;
  int spd;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Set sensor pins as input
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinspd, INPUT);
  pinMode(LEDBUILTIN,OUTPUT);
}
 
void loop() {
  // Set values to send
  XValue = analogRead(pinX);
  YValue = analogRead(pinY);
  spdValue = analogRead(pinspd);
  myData.jystkX = XValue;
  myData.jystkY = YValue;
  myData.spd = spdValue;
  Serial.print("analX = ");
  Serial.println(myData.jystkX);
  Serial.print("analY = ");
  Serial.println(myData.jystkY);
  Serial.print("speed = ");
  Serial.println(myData.spd);
  Serial.println();
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
    digitalWrite(LEDBUILTIN,HIGH);

  }
  else {
    Serial.println("Error sending the data");
    digitalWrite(LEDBUILTIN, LOW);

  }
  delay(200);
}