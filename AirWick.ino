
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//WIFI CREDENTIALS
const char* ssid = "WIFI_SSID"; // wifi ssid name
const char* password = "WIFI_PASSWORD"; // wifi password 

//MQTT CREDENTIALS
const char* mqttServer = "MQTT_SERVER"; 
const int mqttPort = 1883; 
const char* mqttUser = "USERNAME"; 
const char* mqttPassword = "PASSWORD";
#define mqttTopic "cmnd/airwick_one/POWER"
#define mqttSTopic "stat/airwick_one/POWER"



int gpio12Relay = 12; //Sonoff SV Relay pin is 12
int timePinIsHigh = 2000; //amount of time to run motor


WiFiClient espClient;
PubSubClient client(espClient);


void setup() {

  
  pinMode(gpio12Relay, OUTPUT);
  digitalWrite(gpio12Relay, LOW); 
  Serial.begin(115200); //Serial for debugging
  
  
  //Connect to local wifi network
  WiFi.begin(ssid, password);
  while(WiFi.status()!= WL_CONNECTED) {

    delay(500);
    Serial.print("Connecting WiFi...");
    
  }
  //If here WIFI is connected
  Serial.println("Connected to the WiFi network...");
  client.publish(mqttTopic, "OFF");
  client.publish(mqttSTopic, "OFF");

}

void connectToMQTT(){
    //Connect to Mqtt Broker
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while(!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    Serial.println("Connecting to MQTT...");
    if (client.connect(clientId.c_str(), mqttUser, mqttPassword )) {
      Serial.println("connected");
    }else{
      Serial.print("failed state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  Serial.println("Subscribing");
  client.subscribe(mqttTopic);
  client.subscribe(mqttSTopic);
}

void callback(char* topic, byte* payload, unsigned int length)
{

  Serial.print("Message from Topic: ");
  Serial.println(topic);
  for(int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == 'O' && (char)payload[1]== 'N') {     
    Serial.println("New State is ON");
    Serial.println("Turning on");
    digitalWrite(gpio12Relay, HIGH); 
    
    delay(timePinIsHigh);
    
    Serial.println("After Delay...");
    Serial.println("Turning off");
    client.publish(mqttTopic, "OFF");
    digitalWrite(gpio12Relay, LOW);
    client.publish(mqttSTopic, "OFF");
  }
  else{
    digitalWrite(gpio12Relay, LOW);
  }
  
}


void loop() { 
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

}
