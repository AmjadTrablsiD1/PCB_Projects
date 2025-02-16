/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x94, 0xE6, 0x86, 0x09, 0xD6, 0x34};


int in1 = 12;
int in2 = 14;
int in3 = 26;
int in4 = 27;

int en1 = 5  ;
int en2 = 17 ;



// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char text[32];
    int x;
    int y;
    int p_1;
    int p_2;
    int p_3;
    bool but_1;
    bool but_2;
    bool but_3;
    bool but_4;

} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  Serial.print("Char : ");
  Serial.println(myData.text);
 
  Serial.print("Int X : ");
  Serial.println(myData.x);

  Serial.print("int Y : ");
  Serial.println(myData.y);
  
  Serial.print("Pot_1 : ");
  Serial.println(myData.p_1);
 
  Serial.print("Pot_2 : ");
  Serial.println(myData.p_2);
 
  Serial.print("Pot_3 : ");
  Serial.println(myData.p_3);

  Serial.print("Buttom 1 : ");
  Serial.println(myData.but_1);
  
  Serial.print("Buttom 2 : ");
  Serial.println(myData.but_2);
  Serial.print("Buttom 3 : ");
  Serial.println(myData.but_3);
  Serial.print("Buttom 4 : ");
  Serial.println(myData.but_4);
 
}






 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
pinMode(in1 ,OUTPUT);
pinMode(in2 ,OUTPUT);
pinMode(in3 ,OUTPUT);
pinMode(in4 ,OUTPUT);
pinMode(en1,OUTPUT);

ledcSetup(1,5000,8);
ledcSetup(2,5000,8);

ledcAttachPin(en1,1);
ledcAttachPin(en2,2);



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
}



 
void loop() {

  if(myData.x < 100 ){

    // GO BACK

Serial.println("in b< 100 ");

Serial.println(myData.x);
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);


ledcWrite(1,250);
ledcWrite(2,250);

// ledcWrite(1,255);


}else if(myData.x > 130){
  Serial.println(myData.x);


//LINK OR RIGHT


if(myData.y > 100 && myData.y < 130){
  //GERADE
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
ledcWrite(1,250);
ledcWrite(2,250);

}else if(myData.y >130){
//RIGHT
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
ledcWrite(1,250);
ledcWrite(2,250);

}else if (myData.y < 100 ){
//LEFT
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
ledcWrite(1,250);
ledcWrite(2,250);


}



// ledcWrite(1,0);
 //Stop postion 
}else if(myData.x < 130 && myData.x >100 ){
   if(myData.y>130){
//RIGHT
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
ledcWrite(1,250);
ledcWrite(2,250);

}else if (myData.y < 100 ){
//LEFT
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
ledcWrite(1,250);
ledcWrite(2,250);


}else{

digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
}}


 

//move fowrd







delay(500);

}