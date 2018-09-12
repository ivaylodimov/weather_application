#include <DHT.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define DHTTYPE DHT11
const int DHTPin = 0; 
DHT dht(DHTPin, DHTTYPE);

// Temporary variables
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

//Въведете нужните име на мрежа и парола
char ssid[] = "";                 // Име на WiFi мрежа
char pass[] = "";                 // Парола на мрежата
byte mac[6];

WiFiServer server(80);
IPAddress ip(192, 168, 0, 106); // Предпочитан IP адрес
IPAddress gateway(192, 168, 0, 1); //IP адрес на шлюзът
IPAddress subnet(255, 255, 255, 0); // Маска на мрежата

WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "INSERT INTO weather_db.weather_station ( temperature, hum, rain, presure, dusting, sun) VALUES ( %0.0f, %0.0f, 7, 82, 112, 1500)";
char query[128];

//Въведете вашите нужните данни за вашият сървър база данни
IPAddress server_addr(192, 168 ,0, 109);          // MySQL IP адрес
char user[] = "";           // MySQL user
char password[] = "";       // MySQL password

void setup() {
 dht.begin();
  Serial.begin(115200);

  pinMode(DHTPin, INPUT);
  //pinMode(sensorPin8, INPUT);

  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  Serial.println("Connecting to database");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");  
 
}

void loop() {

  delay(700000);
  float h = dht.readHumidity();
  // Четене на температурата по Целзий (стойност по подразбиране)
  float t = dht.readTemperature();
  // Четене на температурата по Фаренхайт (ако isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

            

  sprintf(query, INSERT_SQL, t, h);
  //sprintf(query, INSERT_SQL);

  Serial.println("Recording data.");
  Serial.println(query);
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  
  cur_mem->execute(query);

  delete cur_mem;
}
