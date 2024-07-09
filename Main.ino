#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
const int LedVerde = 19;
const int LedVermelho = 21;

const int relay = 25;
const int buzzer = 5;

#define DHTTYPE DHT11
#define DHTPIN 18
DHT dht(DHTPIN, DHTTYPE);
int temperatura;
int atrasoTemp = 2000;
unsigned long tempoAnteriorTemp = 0;

const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  100
char msg[MSG_BUFFER_SIZE];

void conectarBroker() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  if (!client.connected()) {
    Serial.print("Conectando ao servidor MQTT...");
    digitalWrite(LedVerde, HIGH);
    String clientId = "";
    clientId += String(random(0xffff), HEX);

    //inscrição dos esp32 nos tópicos
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
      client.subscribe("Projeto3/Ventilador");
      client.subscribe("Projeto3/");
    }
  }
}

void reconectarBroker() {
  if (!client.connected()) {
    conectarBroker();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int lenght) {
  //função de liga/desliga led
  if (payload[0] == '0') {
    digitalWrite(relay, LOW);
  }

  if (payload[0] == '1') {
    digitalWrite(relay, HIGH);
  }

  if (payload[0] == 'b') {
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
    }
  }
}

//MEDIR TEMPERATURA E UMIDADE
void medirEnviarGrandezas() {
  long int tempo = millis();
  if (tempo > (tempoAnteriorTemp + atrasoTemp)) {
    tempoAnteriorTemp = tempo;

    temperatura = dht.readTemperature(); //lê temperatura no dht22
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(F("°C"));
    sprintf(msg, "%d", temperatura);
    client.publish("Projeto3/Temperatura", msg);//publica a mensagem no broker mqtt
    int umidade = dht.readHumidity();
    sprintf(msg, "%d", umidade);
    client.publish("Projeto3/Umidade", msg);
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(F("%"));
  }

  if (temperatura >= 20 && temperatura <= 23) {
    digitalWrite(LedVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
  } else if (temperatura >= 24) {
    digitalWrite(LedVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    delay(1000);
    digitalWrite(LedVermelho, LOW);
    digitalWrite(buzzer, LOW);
    delay(1000);
  } else {
    digitalWrite(LedVermelho, LOW);
    digitalWrite(relay, LOW);
  }
}

void piscaLed(int pino) {
  digitalWrite(pino, HIGH);
  delay(125);
  digitalWrite(pino, LOW);
  delay(125);
}

void setup() {
  Serial.begin(9600);
  dht.begin(  );
  Serial.print("Conectando-se ao Wi-Fi");
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);

  WiFi.begin("Wifi", "Senha");

  while (WiFi.status() != WL_CONNECTED) {
    piscaLed(LedVerde);
    Serial.print(".");
  }
  Serial.println(" Conectado!");


  conectarBroker();
}

void loop() {
  reconectarBroker();
  medirEnviarGrandezas();
}