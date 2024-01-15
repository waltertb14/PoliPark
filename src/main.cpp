#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>


#define WIFI_SSID "NETLIFE-TAMAYO"
#define WIFI_PASSWORD "samantha1"
#define FIREBASE_HOST "poliparkesp32-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyD4BT_5hyXZca3WuIKjwWyEno9q-ucWs68"

FirebaseData firebaseData;
int DISTANCIA=0;
int DISTANCIA1=0;
int LedRojo=2;
int LedVerde= 0;
int pinEco=12;
int pinGatillo=13;

int LedRojo1=25;
int LedVerde1= 26;
int pinEco1=36;
int pinGatillo1=39;


void setup() {
  Serial.begin(115200);
  //Configuramos el pin del led como salida
  Serial.println("Punto1");
  pinMode(LedRojo, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedRojo1, OUTPUT);
  pinMode(LedVerde1, OUTPUT);
  Serial.println("Punto2");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a la red WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Escribir un valor en la base de datos
  
  
}
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  //Iniciamos el pin del emisor de reuido en salida
  pinMode(triggerPin, OUTPUT);
  
  //Apagamos el emisor de sonido
  digitalWrite(triggerPin, LOW);
  //Retrasamos la emision de sonido por 2 milesismas de segundo
  delayMicroseconds(2);
  // Comenzamos a emitir sonido
  digitalWrite(triggerPin, HIGH);
  //Retrasamos la emision de sonido por 2 milesismas de segundo
  delayMicroseconds(10);
  //Apagamos el emisor de sonido
  digitalWrite(triggerPin, LOW);
  //Comenzamos a escuchar el sonido
  pinMode(echoPin, INPUT);
  // Calculamos el tiempo que tardo en regresar el sonido
  return pulseIn(echoPin, HIGH);
}

void disponible(String referencia, int ledrojo, int ledverde, int trigger, int echo){
  //calcula la distancia
  int distancia = 0.01723 * readUltrasonicDistance(trigger, echo);
  if (distancia < 10 ) {
    digitalWrite(ledverde, LOW);
    Firebase.set(firebaseData,referencia,false);
    digitalWrite(ledrojo,HIGH);
  }
  else{
    digitalWrite(ledverde, HIGH);
    digitalWrite(ledrojo,LOW);
    Firebase.set(firebaseData,referencia,true);
  }


}

void loop() {
  disponible("Parqueos/FIEC/1",LedRojo,LedVerde, pinGatillo,pinEco);
  disponible("Parqueos/FIEC/2",LedRojo1,LedVerde1,pinGatillo1,pinEco1);
  delay(10);

}