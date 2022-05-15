/*************************GSM macros******************************/
#define TINY_GSM_MODEM_SIM800
#define MODEM_RST 2
#define MODEM_PWKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define GSM_PIN ""
#define SerialAT Serial1
/*****************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <TinyGsmClient.h>
#include "Credentials.h"
#include "secrets.h"
#include <MQTT.h>
#include <MQTTClient.h>
#include <SSLClient.h>
//#include "cert.h"
//#include <WiFiClientSecure.h>

/*************************Variable decleration********************/
String FirmwareVer = {
    "4.1"};
String ap_mode_ssid_ = "Cybene";
char ap_mode_ssid[35];
char ap_mode_password[] = "Cybene@123";
String macID = "";
char jsonBuffer[512];
String name = "CONF/SN-";
String UUID = "";
String broker_id = "";
String broker_password = "";
char broker_id_char[15];
char broker_password_char[15];

bool connected_to_internet = 0;
const char mqtt_server[] = "a3g40b8390y96b-ats.iot.us-east-1.amazonaws.com";
bool wifi_connected = true;
bool gprs_connected = false;
const char apn[] = "allcom.vivo.com.br";
const char gprsUser[] = "allcom";
const char gprsPass[] = "allcom";
/*****************************************************************/
/************************************AWS parameters***************/
#define DEVICE_NAME "placa-01"
#define AWS_IOT_ENDPOINT "a3g40b8390y96b-ats.iot.us-east-1.amazonaws.com"
#define AWS_IOT_TOPIC "$aws/things/" DEVICE_NAME "/shadow/update"
#define AWS_MAX_RECONNECT_TRIES 50
/**********************************Objects************************/
WiFiClient wifi_client;
TinyGsm modem(SerialAT);
TinyGsmClient gsm_client(modem);
SSLClient modemGSMSSL(&gsm_client);
SSLClient net(&wifi_client);
PubSubClient wifi_mqtt(wifi_client);
PubSubClient gsm_mqtt(gsm_client);
//WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(512);
credentials cred;

void setup_gprs();
void connectToAWS();
void modem_init();
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
String read_uuid();
String read_userid();
String read_password();
void messageReceived(String &topic, String &payload);
void WiFi_client_connect();
void Send_json_to_broker();
bool Gsm_client_connect();
void lwMQTTErr(lwmqtt_err_t reason);

void setup()
{
  Serial.begin(115200);

  modem_init();
  setup_gprs();
  Serial.println(macID = WiFi.macAddress());
  ap_mode_ssid_ += macID;
  Serial.println(ap_mode_ssid_);
  ap_mode_ssid_.toCharArray(ap_mode_ssid, 35);
  Serial.println(ap_mode_ssid);

  name += macID;
  Serial.println(name);
  cred.EEPROM_Config();
  // cred.Erase_eeprom();

  WiFi.onEvent(WiFiStationConnected, ARDUINO_EVENT_WIFI_AP_STACONNECTED);
  WiFi.onEvent(WiFiStationDisconnected, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);
  if (cred.credentials_get())
  {
    connected_to_internet = 1;
  }
  else
  {
    cred.setupAP(ap_mode_ssid, ap_mode_password);
    connected_to_internet = 0;
  }
  if (connected_to_internet == 1)
  {

    Serial.println(UUID = read_uuid());
    Serial.println(broker_id = read_userid());
    Serial.println(broker_password = read_password());
    broker_id.toCharArray(broker_id_char, 15);
    broker_password.toCharArray(broker_password_char, 15);
    connectToAWS();
    //client.subscribe(name);
    //client.onMessage(messageReceived);
  }
}
void loop()
{
    client.loop();
  if(!client.connected()){
    connectToAWS();
  }
  Serial.println("conectado: "+client.connected());
  Serial.println("gprs_connected: "+gprs_connected);
  if (gprs_connected)
  {
   /*  Serial.println("gsm_mqtt: "+gsm_mqtt.connected());
    if (!gsm_mqtt.connected())
    {
      Gsm_client_connect();
    } */

    Send_json_to_broker();
    gsm_mqtt.loop();
  }
  if (connected_to_internet && int(EEPROM.read(250)) == 1)
  {
    if (!wifi_mqtt.connected() && wifi_connected == true)
    {
      WiFi_client_connect();
    }
    // Send_json_to_broker();
    wifi_mqtt.loop();
  }

  cred.server_loops();

  delay(5000);
}
/*****************************************************************/
/*************************WiFi client-broker connect**************/
void WiFi_client_connect()
{
  while (!wifi_mqtt.connected())
  {
    Serial.println("Attempting MQTT connection..");

    boolean stat = wifi_mqtt.connect("ESP32_MQTT_Client", broker_id_char, broker_password_char);
    //    boolean stat;
    if (stat == true)
    {
      Serial.print("connected to mqtt server=");
      Serial.println(mqtt_server);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(wifi_mqtt.state());
      Serial.println("try again in 5 seconds");
      EEPROM.write(250, 0);
      delay(5000);
    }
  }
}

/***********************GSM client-broker connect******************/
bool Gsm_client_connect()
{
  Serial.print("Connecting to:");
  Serial.print(mqtt_server);

  boolean status = gsm_mqtt.connect(AWS_IOT_TOPIC);

  if (status == false)
  {
    Serial.println("fail");
    EEPROM.write(250, 0);
    return false;
  }
  Serial.println("Success");
  return true;
}

void Send_json_to_broker()
{
  DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(6) + 100);
  JsonObject root = jsonBuffer.to<JsonObject>();
  JsonObject state = root.createNestedObject("state");
  JsonObject state_reported = state.createNestedObject("reported");
  state_reported["value"] = random(100);
  state_reported["fw_version"] = FirmwareVer;
  state_reported["imei"] = modem.getIMEI();
  state_reported["ip_local_wifi"] = WiFi.localIP();
  state_reported["gprs_connected"] = gprs_connected ? 1 : 0;
  state_reported["ip_local_gprs"] = modem.getLocalIP();

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
/***********WiFi on connect handler*************************/
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("WiFi connected handler invoked");
  wifi_mqtt.setServer(mqtt_server, 1883);
  wifi_connected = true;
}
/**********WiFi on disconnect handler************************/
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("WiFi disconnected handler invoked");
  setup_gprs();
  gsm_mqtt.setServer(mqtt_server, 1883);
  wifi_connected = false;
}
/****************************AWS callback*******************/
void messageReceived(String &topic, String &payload)
{
  Serial.println("ïncoming: " + topic + "-" + payload);
  client.publish(topic + "/STATUS", "SUCCESS");
  DynamicJsonDocument jsonDoc(1024);
  DeserializationError error = deserializeJson(jsonDoc, payload);
  String uuid = jsonDoc["uuid"];
  String userID = jsonDoc["userid"];
  String password = jsonDoc["password"];
  EEPROM.write(250, 1);
  for (int i = 0; i < 100; i++)
  {
    EEPROM.write(i + 100, 0);
  }

  for (int i = 0; i < 36; i++)
  {
    EEPROM.write(i + 100, uuid[i]);
  }

  for (int i = 0; i < 15; i++)
  {
    EEPROM.write(i + 140, userID[i]);
  }

  for (int i = 0; i < 15; i++)
  {
    EEPROM.write(i + 160, password[i]);
  }
  EEPROM.commit();
  delay(500);
  ESP.restart();
}
void modem_init()
{
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(25, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);
}

void setup_gprs()
{

  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(6000);
  digitalWrite(25, HIGH);
  Serial.println("initalizing modem..");
  modem.restart();
  String modemInfo = modem.getModemInfo();
  Serial.print("modem info:");
  Serial.println(modemInfo);
  if (GSM_PIN && modem.getSimStatus() != 3)
  {
    modem.simUnlock(GSM_PIN);
  }
  Serial.print("Waiting for network...");
  if (!modem.waitForNetwork(240000l))
  {
    delay(10000);
    return;
  }
  Serial.println("Success");
  if (modem.isNetworkConnected())
  {
    Serial.println("Network connected");
  }
  Serial.print(F("Connecting to APN"));
  Serial.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass))
  {
    Serial.println("fail");
    delay(1000);
    return;
  }
  Serial.println("Success");
  if (modem.isGprsConnected())
  {
    Serial.println("GPRS connected");
    gprs_connected = true;
    gsm_mqtt.setServer(mqtt_server, 1883);
  }
}

String read_uuid()
{
  String uuid_in_eeprom = "";
  for (int i = 0; i < 36; ++i)
  {
    uuid_in_eeprom += char(EEPROM.read(i + 100));
  }
  return uuid_in_eeprom;
}

String read_userid()
{
  String userid_in_eeprom = "";
  for (int i = 0; i < 15; ++i)
  {
    userid_in_eeprom += char(EEPROM.read(i + 140));
  }
  return userid_in_eeprom;
}

String read_password()
{
  String password_in_eeprom = "";
  for (int i = 0; i < 15; ++i)
  {
    password_in_eeprom += char(EEPROM.read(i + 160));
  }
  return password_in_eeprom;
}

void connectToAWS()
{
  
  modemGSMSSL.setCACert(AWS_CERT_CA);
  modemGSMSSL.setCertificate(AWS_CERT_CRT);
  modemGSMSSL.setPrivateKey(AWS_CERT_PRIVATE);
  client.begin(AWS_IOT_ENDPOINT, 8883, modemGSMSSL);
  
  int retries = 0;
  Serial.print("Connecting to AWS IOT");

  while (!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES){

  Serial.print(".");
  delay(100);
  retries++;
  }

  if (!client.connected())
  {
    Serial.println("Timeout");
    return;
  }
  Serial.println("Connected");
}
