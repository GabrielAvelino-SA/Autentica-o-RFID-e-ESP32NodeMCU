//Autor : FRANCISCO GABRIEL
 
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SS_PIN 14
#define RST_PIN 27

#define TOPICO_SUBSCRIBE "topco-a-ser-assinado";
#define TOPICO_PUBLISH "topico-assinado";
#define MQTT_ID "ip-no-broker";

const char* ssid = "ssid-rede";
const char* password = "senha-da-rede";
const char* mqttServer = "endereço-broker";
int BrokerPort = 1889;//porta

WifiClient espClient; //instancia client esp
PubSubClient MQTT(espClient);//instancia do objeto MQTT
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Instancia MFRC522

//Protipos
void init_WiFi(void);
void init_MQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void verifica_conexoes_wifi_mqtt(void);

void setup() 
{
  Serial.begin(9600);
  SPI.begin();  //inicia o modulo RFID
  mfrc522.PCD_Init();
  init_WiFi();
  init_MQTT();
  Serial.println("Aguardando tag RFID para verificar o id da mesma.");
}
 
void loop() 
{
  String conteudo = "";      // cria uma string
  
  Serial.print("id da tag :");
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;//caso nenhuma teg apresentada
  if ( ! mfrc522.PICC_ReadCardSerial()) return;//caso erro na leitura da teg
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    //usa do monitor serial para apresentar o ip da TEG
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
}

//FUNÇOES
void init_WiFi(){
  WiFi.begin(ssid,password);
  while (WiFi.status()!= WL_CONNECTED){
  Serial.print(".");
  delay(1000);
  }
  Serial.println("\nConeção efetuada com suscessso"); 
}
void init_MQTT(){
  //informa qual broker e porta deve ser conectado
  MQTT.setServer(mqttServer,BrokerPort);
  //atribui função de callback (função chamada quando qualquer informação do tópico subescrito chega
  MQTT.setCallback(mqtt_callback);

}
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }

}
