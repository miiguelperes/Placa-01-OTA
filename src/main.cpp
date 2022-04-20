#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"
#include "ArduinoJson.h"
#include <Firebase_ESP_Client.h>

const char *ssid = "Miguel";
const char *password = "miguel997";

String FirmwareVer = {
    "3.1"};

#define URL_fw_Version "https://raw.githubusercontent.com/miiguelperes/Placa-01-OTA/main/bin_version.txt"
#define URL_fw_Bin "https://raw.githubusercontent.com/miiguelperes/Placa-01-OTA/main/fw.bin"
#define FIREBASE_HOST "https://camaras-frias-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "VrqFBtuYaHIcH8p2XIPlUjNAtNEqXvuETTtF7MHY"
#define USER_EMAIL "mperes@rastreagro.com";
#define USER_PASSWORD "Rastreagro.123";
FirebaseData fbdo;

FirebaseAuth auth;

/* 5. Define the FirebaseConfig data for config data */
FirebaseConfig config;

//#define URL_fw_Version "http://cade-make.000webhostapp.com/version.txt"
//#define URL_fw_Bin "http://cade-make.000webhostapp.com/firmware.bin"

void connect_wifi();
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

struct Button
{
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button_boot = {
    0,
    0,
    false};
/*void IRAM_ATTR isr(void* arg) {
    Button* s = static_cast<Button*>(arg);
    s->numberKeyPresses += 1;
    s->pressed = true;
}*/

void IRAM_ATTR isr()
{
  button_boot.numberKeyPresses += 1;
  button_boot.pressed = true;
}

void setup()
{
  pinMode(button_boot.PIN, INPUT);
  attachInterrupt(button_boot.PIN, isr, RISING);
  Serial.begin(115200);
  Serial.print("Versao de firmware ativa:");
  Serial.println(FirmwareVer);
  //pinMode(LED_BUILTIN, OUTPUT);
  connect_wifi();




  fbdo.setResponseSize(1024);
}
void loop()
{
  if (button_boot.pressed)
  { //to connect wifi via Android esp touch app
    Serial.println("Iniciando a atualização do firmware..");
    firmwareUpdate();
    button_boot.pressed = false;
  }
  repeatedCall();

  if ((WiFi.status() == WL_CONNECTED))
  {

      config.host = FIREBASE_HOST;
  config.api_key = FIREBASE_AUTH;
   config.max_token_generation_retry = 5000;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
 
  Firebase.reconnectWiFi(true);
  Firebase.RTDB.setReadTimeout(&fbdo, 1000 * 60);
  Firebase.RTDB.setwriteSizeLimit(&fbdo, "tiny");
  Firebase.RTDB.setMaxRetry(&fbdo, 3000);
  Firebase.RTDB.setMaxErrorQueue(&fbdo, 30);
  Firebase.RTDB.enableClassicRequest(&fbdo, true);
  Firebase.begin(&config, &auth);
    
    FirebaseJson json;
    FirebaseJson json2;

    json2.add("child_of_002", 123.456);
    json.add("parent_001", "parent 001 text");
    json.add("parent 002", json2);

    if (Firebase.RTDB.pushJSON(&fbdo, "/test/append", &json)) {

      Serial.println(fbdo.dataPath());

      Serial.println(fbdo.pushName());

      Serial.println(fbdo.dataPath() + "/"+ fbdo.pushName());

    } else {
      Serial.println(fbdo.errorReason());
    }

  }
  else
  {
    Serial.println("Conexão perdida");
  }
  delay(10000);
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
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  //httpUpdate.setLedPin(LED_BUILTIN, LOW);
  t_httpUpdate_return ret = httpUpdate.update(client, URL_fw_Bin);

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
  WiFiClientSecure *client = new WiFiClientSecure;

  if (client)
  {
    client->setCACert(rootCACertificate);

    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is
    HTTPClient https;

    if (https.begin(*client, fwurl))
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
    delete client;
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