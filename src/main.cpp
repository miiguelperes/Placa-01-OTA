#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"
#include <ArduinoJson.h>
#include <MQTTClient.h>

const char *ssid = "Miguel";
const char *password = "miguel997";

String FirmwareVer = {
    "3.1"};

#define URL_fw_Version "https://raw.githubusercontent.com/miiguelperes/Placa-01-OTA/main/bin_version.txt"
#define URL_fw_Bin "https://raw.githubusercontent.com/miiguelperes/Placa-01-OTA/main/fw.bin"
// O nome do dispositivo. Isso DEVE corresponder ao nome definido no console AWS
#define DEVICE_NAME "placa-01"

// O endpoint MQTTT para o dispositivo (exclusivo para cada conta AWS, mas compartilhado entre os dispositivos dentro da conta)
#define AWS_IOT_ENDPOINT "a3g40b8390y96b-ats.iot.us-east-1.amazonaws.com"

// O tópico MQTT em que este dispositivo deve publicar
#define AWS_IOT_TOPIC "$aws/things/" DEVICE_NAME "/shadow/update"

// Quantas vezes devemos tentar nos conectar ao AWS
#define AWS_MAX_RECONNECT_TRIES 50

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(512);

void connect_wifi();
void connectToAWS();
void sendJsonToAWS();
void firmwareUpdate();
int FirmwareVersionCheck();

unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long previousMillis_2 = 0;
const long interval = 60000;
const long mini_interval = 1000;
void repeatedCall()
{
  static int num = 0;
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (FirmwareVersionCheck())
    {
      firmwareUpdate();
    }
  }
  if ((currentMillis - previousMillis_2) >= mini_interval)
  {
    previousMillis_2 = currentMillis;
    Serial.print("Loop IOT...");
    Serial.print(num++);
    Serial.print(" Versao de firmware ativa:");
    Serial.println(FirmwareVer);
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("wifi connectado");
    }
    else
    {
      connect_wifi();
    }
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.print("Versao de firmware ativa:");
  Serial.println(FirmwareVer);
  connect_wifi();
  connectToAWS();
}

void loop()
{
 
  repeatedCall();

  if ((WiFi.status() == WL_CONNECTED))
  {
  sendJsonToAWS();
    client.loop();
  }
  else
  {
    Serial.println("Conexão perdida");
  }
  delay(10000);
}

void sendJsonToAWS()
{
  StaticJsonDocument<256> jsonDoc;
  JsonObject stateObj = jsonDoc.createNestedObject("state");
  JsonObject reportedObj = stateObj.createNestedObject("reported");
  
  // Escreva a temperatura e umidade. Aqui você pode usar qualquer tipo C ++ (e pode se referir a variáveis)
  reportedObj["temperature"] = 23.76;
  reportedObj["humidity"] = 78.12;
  reportedObj["wifi_strength"] = WiFi.RSSI();
  
  // Cria um objeto aninhado "local"
  JsonObject locationObj = reportedObj.createNestedObject("location");
  locationObj["name"] = "Garden";
  char jsonBuffer[512];
  Serial.println(jsonDoc.size());
  serializeJson(jsonDoc, jsonBuffer);
  // Publique a mensagem para AWS
  client.publish(AWS_IOT_TOPIC, jsonBuffer);
  
  Serial.println("Json Enviado!");
  Serial.println(client.lastError());
}

void connectToAWS()
{
    // Configure WiFiClientSecure para usar os certificados AWS que geramos
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);
    // Conecte-se ao corretor MQTT no endpoint AWS que definimos anteriormente
    client.begin(AWS_IOT_ENDPOINT, 8883, net);
    // Tente se conectar ao AWS e conte quantas vezes tentamos novamente.
    int retries = 0;
    Serial.print("Connecting to AWS IOT");
    while (!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES) {
        Serial.print(".");
        delay(100);
        retries++;
    }
    // Certifique-se de que realmente conectamos com sucesso ao broker MQTT
        // Do contrário, apenas encerramos a função e aguardamos o próximo loop.
    if(!client.connected()){
        Serial.println(" Tempo esgotado!");
        return;
    }
    // Se pousarmos aqui, nos conectamos com sucesso ao AWS!
        // E podemos assinar tópicos e enviar mensagens.
    Serial.println("Conectado!");
}

void connect_wifi()
{
  Serial.println("Aguardando Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  
}

void firmwareUpdate(void)
{
  WiFiClientSecure client2;
  client2.setCACert(rootCACertificate);
  //httpUpdate.setLedPin(LED_BUILTIN, LOW);
  t_httpUpdate_return ret = httpUpdate.update(client2, URL_fw_Bin);

  switch (ret)
  {
  case HTTP_UPDATE_FAILED:
    Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
    break;

  case HTTP_UPDATE_NO_UPDATES:
    Serial.println("HTTP_UPDATE_NO_UPDATES");
    break;

  case HTTP_UPDATE_OK:
    Serial.println("HTTP_UPDATE_OK");
    break;
  }
}
int FirmwareVersionCheck(void)
{
  String payload;
  int httpCode;
  String fwurl = "";
  fwurl += URL_fw_Version;
  fwurl += "?";
  fwurl += String(rand());
  Serial.println(fwurl);
  WiFiClientSecure *client2 = new WiFiClientSecure;

  if (client2)
  {
    client2->setCACert(rootCACertificate);

    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is
    HTTPClient https;

    if (https.begin(*client2, fwurl))
    { // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      delay(100);
      httpCode = https.GET();
      delay(100);
      if (httpCode == HTTP_CODE_OK) // if version received
      {
        payload = https.getString(); // save received version
      }
      else
      {
        Serial.print("Erro ao baixar arquivo de versão:");
        Serial.println(httpCode);
      }
      https.end();
    }
    delete client2;
  }

  if (httpCode == HTTP_CODE_OK) // if version received
  {
    payload.trim();
    if (payload.equals(FirmwareVer))
    {
      Serial.printf("\nDispositivo já na versão de firmware mais recente:%s\n", FirmwareVer);
      return 0;
    }
    else
    {
      Serial.println(payload);
      Serial.println("Novo firmware detectado");
      return 1;
    }
  }
  return 0;
}