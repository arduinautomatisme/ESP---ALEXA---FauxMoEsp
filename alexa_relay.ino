/*
   JLBRUNEAU
   Gestion piscine et arrosage
   Commande de 4 relais via Alexa
*/

/*
   Bibliothèques
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define RELAY_PIN_1 D1
#define RELAY_PIN_2 D2
#define RELAY_PIN_3 D3
#define RELAY_PIN_4 D4



#define SERIAL_BAUDRATE 115200

#define WIFI_SSID "*****************"
#define WIFI_PASS "*****************"

#define RELAY_1 "remplissage piscine"
#define RELAY_2 "arrosage avant"
#define RELAY_3 "arrosage arriere"
#define RELAY_4 "cascade"


fauxmoESP fauxmo;


// Wi-Fi Connection
void wifiSetup() {
  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup() {
  // Init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  // Wi-Fi connection
  wifiSetup();

  // RELAIS
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);

  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2, HIGH);

  pinMode(RELAY_PIN_3, OUTPUT);
  digitalWrite(RELAY_PIN_3, HIGH);


  pinMode(RELAY_PIN_4, OUTPUT);
  digitalWrite(RELAY_PIN_4, HIGH);


  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices

  fauxmo.enable(true);

  // Add virtual devices
  fauxmo.addDevice(RELAY_1);
  fauxmo.addDevice(RELAY_2);
  fauxmo.addDevice(RELAY_3);
  fauxmo.addDevice(RELAY_4);


  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.println("reçu");

    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);



    if ( (strcmp(device_name, RELAY_1) == 0) ) {         // Compare nom appareil envoyé par Alexa et le nom choisi pour le relais x  (renvoie 0 si les deux chaînes sont égales) 
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 1 switched by Alexa");
      Serial.println(state);
      if (state == 1) {                                 // Si state = 1 => fermeture => sortie etat Bas => relais  etat Haut
        Serial.println("RELAY 1 Etat  LOW");
        digitalWrite(RELAY_PIN_1, LOW);
      } else {
        Serial.println("RELAY 1 Etat  HIGHT");
        digitalWrite(RELAY_PIN_1, HIGH);
      }
    }


    
    if ( (strcmp(device_name, RELAY_2) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      Serial.println(state);
      if (state == 1) {
        Serial.println("RELAY 2  Etat  LOW");
        digitalWrite(RELAY_PIN_2, LOW);
      } else {
        Serial.println("RELAY 2 Etat  HIGHT");
        digitalWrite(RELAY_PIN_2, HIGH);
      }
    }

    if ( (strcmp(device_name, RELAY_3) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 3 switched by Alexa");
      Serial.println(state);
      if (state == 1) {
        Serial.println("RELAY 3 Etat  LOW");
        digitalWrite(RELAY_PIN_3, LOW);
      } else {
        Serial.println("RELAY 3  Etat  HIGHT");
        digitalWrite(RELAY_PIN_3, HIGH);
      }
    }


    if ( (strcmp(device_name, RELAY_4) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 4 switched by Alexa");
      Serial.println(state);
      if (state == 1) {
        Serial.println("RELAY 4 Etat  LOW");
        digitalWrite(RELAY_PIN_4, LOW);
      } else {
        Serial.println("RELAY 4  Etat  HIGHT");
        digitalWrite(RELAY_PIN_4, HIGH);
      }
    }
  });

}

void loop() {
  fauxmo.handle();
}
