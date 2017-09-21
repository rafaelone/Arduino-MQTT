#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

const int LDR = A0;

byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x08};
IPAddress server(192,168,0,105);
EthernetClient ethClient;
PubSubClient client(ethClient);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LDR, INPUT);

  client.setServer(server, 1883);
  Ethernet.begin(mac);

  delay(1500);
  Serial.println(Ethernet.localIP());
}

void reconnect(){
  while( !client.connected()){
    Serial.println("Tentando se conectar");
      if(client.connect("Arduino 08")){
        Serial.println("Conectado com sucesso");
      }else{
        Serial.println("Erro ao tentar se conectar");
        delay(5000);
      }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()){
    reconnect();
  }
  client.loop();
  
  float entrada = analogRead(LDR);
  char txtValorDoSensor[4];
  dtostrf(entrada, 4, 0, txtValorDoSensor);
  client.publish("massao",txtValorDoSensor);
  

  Serial.println(entrada);
  delay(500);
  
}
