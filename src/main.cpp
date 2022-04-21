#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"
#include <ArduinoJson.h>
#include <MQTTClient.h>
// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800   // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#include <Wire.h>
#include <TinyGsmClient.h>
const char *ssid = "Miguel";
const char *password = "miguel997";

String FirmwareVer = {
    "3.3"};

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

// SIM card PIN (leave empty, if not defined)
const char simPIN[] = "";

// Your phone number to send SMS: + (plus sign) and country code, for Portugal +351, followed by phone number
// SMS_TARGET Example for Portugal +351XXXXXXXXX
#define SMS_TARGET "+5534991536120"



// TTGO T-Call pins
#define MODEM_RST 2
#define MODEM_PWKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define I2C_SDA 21
#define I2C_SCL 22

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM800 module)
#define SerialAT Serial1

// Define the serial console for debug prints, if needed
//#define DUMP_AT_COMMANDS

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

#define IP5306_ADDR 0x75
#define IP5306_REG_SYS_CTL0 0x00


WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient();

void connect_wifi();
void connectToAWS();
void lwMQTTErr(lwmqtt_err_t reason);
void sendJsonToAWS();
void firmwareUpdate();
void repeatedCall();
void connectGSM();
int FirmwareVersionCheck();

unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long previousMillis_2 = 0;
const long interval = 60000;
const long mini_interval = 1000;

void setup()
{
  Serial.begin(115200);
  Serial.print("Versao de firmware ativa:");
  Serial.println(FirmwareVer);
  connectGSM();
  connect_wifi();
  connectToAWS();
}

void loop()
{

  repeatedCall();

  if ((WiFi.status() == WL_CONNECTED))
  {
    if (!client.connected())
    {
      connectToAWS();
    }
    else
    {
      sendJsonToAWS();
    }
  }
  else
  {
    Serial.println("Conexão perdida");
    connect_wifi();
  }
  client.loop();
  delay(10000);
}
void connectGSM()
{

  // Mantenha a energia ao funcionar a partir da bateria
  Wire.begin(I2C_SDA, I2C_SCL);

  // Definir redefinição do modem, habilitar, pinos de energia
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(25, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  // Defina a taxa de transmissão do módulo GSM e os pinos UART
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);
  digitalWrite(25, HIGH);
  // Reinicie o módulo SIM800, leva algum tempo
  // Para ignorá-lo, chame init() em vez de restart()
  SerialMon.println("Inicializando modem...");
  modem.restart();
  // use modem.init() se você não precisar da reinicialização completa
  // Desbloqueie seu cartão SIM com um PIN, se necessário
  SerialMon.println(modem.getIMEI());
  // Para enviar um SMS, ligue para modem.sendSMS(SMS_TARGET, smsMessage)
  String smsMessage = "Olá, eu sou o a inteligencia da plaquinha, essa é uma mensagem de teste :D";
  if (modem.sendSMS(SMS_TARGET, smsMessage))
  {
    SerialMon.println(smsMessage);
  }
  else
  {
    SerialMon.println("Erro ao enviar sms");
  }
}
void sendJsonToAWS()
{
  DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
  JsonObject root = jsonBuffer.to<JsonObject>();
  JsonObject state = root.createNestedObject("state");
  JsonObject state_reported = state.createNestedObject("reported");
  state_reported["value"] = random(100);
  state_reported["fw_version"] = FirmwareVer;
  state_reported["imei"] = modem.getIMEI();
  Serial.printf("Sending  [%s]: ", AWS_IOT_TOPIC);
  serializeJson(root, Serial);
  Serial.println();
  char shadow[measureJson(root) + 1];
  serializeJson(root, shadow, sizeof(shadow));
  if (!client.publish(AWS_IOT_TOPIC, shadow, false, 0))
    lwMQTTErr(client.lastError());
}

void lwMQTTErr(lwmqtt_err_t reason)
{
  if (reason == lwmqtt_err_t::LWMQTT_SUCCESS)
    Serial.print("Success");
  else if (reason == lwmqtt_err_t::LWMQTT_BUFFER_TOO_SHORT)
    Serial.print("Buffer too short");
  else if (reason == lwmqtt_err_t::LWMQTT_VARNUM_OVERFLOW)
    Serial.print("Varnum overflow");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_CONNECT)
    Serial.print("Network failed connect");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_TIMEOUT)
    Serial.print("Network timeout");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_READ)
    Serial.print("Network failed read");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_WRITE)
    Serial.print("Network failed write");
  else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_OVERFLOW)
    Serial.print("Remaining length overflow");
  else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_MISMATCH)
    Serial.print("Remaining length mismatch");
  else if (reason == lwmqtt_err_t::LWMQTT_MISSING_OR_WRONG_PACKET)
    Serial.print("Missing or wrong packet");
  else if (reason == lwmqtt_err_t::LWMQTT_CONNECTION_DENIED)
    Serial.print("Connection denied");
  else if (reason == lwmqtt_err_t::LWMQTT_FAILED_SUBSCRIPTION)
    Serial.print("Failed subscription");
  else if (reason == lwmqtt_err_t::LWMQTT_SUBACK_ARRAY_OVERFLOW)
    Serial.print("Suback array overflow");
  else if (reason == lwmqtt_err_t::LWMQTT_PONG_TIMEOUT)
    Serial.print("Pong timeout");
}

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
  while (!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES)
  {
    Serial.print(".");
    delay(100);
    retries++;
  }
  // Certifique-se de que realmente conectamos com sucesso ao broker MQTT
  // Do contrário, apenas encerramos a função e aguardamos o próximo loop.
  if (!client.connected())
  {
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