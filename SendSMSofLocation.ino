#include <SoftwareSerial.h>
#include <TinyGPS++.h>

const String PHONE = "+91123456789";
#define MQ3pin A0
#define rxGSM 14
#define txGSM 12
#define rxGPS 2
#define txGPS 3

SoftwareSerial sim800(rxGSM, txGSM);
SoftwareSerial neogps(rxGPS, txGPS);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino serial initialized");
  
  sim800.begin(9600);
  Serial.println("SIM800L serial initialized");

  neogps.begin(9600);
  Serial.println("NeoGPS serial initialized");

  sim800.listen();
  neogps.listen();
  
  sim800.print("AT+CMGF=1\r");
  delay(1000);
  
  pinMode(MQ3pin, INPUT);
}

void loop() {
  float sensorValue = analogRead(MQ3pin);

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > 600.00) {
    Serial.println("Accident detected");
    delay(200);
    SendSMS();
  } else {
    Serial.println("Accident not detected");
  }

  if (sim800.available()) {
    Serial.write(sim800.read());
  } else {
    Serial.println("SIM not available");
  }
}

void SendSMS() {
  Serial.println("Sending SMS...");

  sim800.print("AT+CMGS=\"");
  sim800.print(PHONE);
  sim800.println("\"");
  delay(500);
  sim800.print("Accident occurred");
  delay(500);
  sim800.write(26); // Ctrl-Z
  delay(1000);

  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;) {
    while (neogps.available()) {
      if (gps.encode(neogps.read())) {
        newData = true;
      }
    }
  }

  if (newData) {
    Serial.print("Latitude= ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Longitude= ");
    Serial.println(gps.location.lng(), 6);
    
    delay(300);
    sim800.print("AT+CMGF=1\r");
    delay(1000);
    sim800.print("AT+CMGS=\"");
    sim800.print(PHONE);
    sim800.println("\"");
    delay(1000);
    sim800.print("http://maps.google.com/maps?q=loc:");
    sim800.print(gps.location.lat(), 6);
    sim800.print(",");
    sim800.print(gps.location.lng(), 6);
    delay(100);
    sim800.write(0x1A); // Ctrl-Z
    delay(1000);
    Serial.println("GPS Location SMS Sent Successfully.");
  } else {
    Serial.println("Invalid GPS data");
  }

  delay(500);
  sim800.println();
  Serial.println("Text Sent.");
  delay(500);
}
