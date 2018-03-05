#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN D3

const char* ssid = "...";
const char* password = "...";
const char* mqtt_server = "<Server IP Address>";  
const char* clientID = "esp8266";
const char* outTopic = "output";


DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp_c; 
 WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
   dht.begin(); 
         
}

 void reconnect() {
  while (!client.connected())
 {
    Serial.print("Attempting MQTT connection...");
     if (client.connect(clientID)) {
      Serial.println("connected");
     //  client.publish(outTopic, clientID);
     
    }
 else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
} 
void loop() {

  if (!client.connected()) {
    reconnect();
  }  
 
         
  
publishtemp();
publishhum();
} 
void publishtemp()
{
    dht.begin();
  String t="";
char te[30];
  temp_c = dht.readTemperature(); 
t=t+"klu temperature "+String(temp_c);
int l=t.length()+1;
t.toCharArray(te,l);
client.publish(outTopic,te);  

  }

void publishhum()
{
    dht.begin();
 String h="";

char hu[30];
 
humidity = dht.readHumidity();
h=h+"klu humidity "+humidity;
int j=h.length()+1;
h.toCharArray(hu,j);
client.publish(outTopic,hu);
delay(2000);

  }

