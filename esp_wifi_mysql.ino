#include <DHT.h> //Включване библиотеката за сензорът
#include <MySQL_Connection.h> //Включване библиотеката за връзка с MySQL
#include <MySQL_Cursor.h> //Включване библиотеката за работа с MySQL
#include <ESP8266WiFi.h> //Включване библиотеката за работа с WiFi
#include <WiFiClient.h> //Включване библиотеката за WiFi клиент

#define DHTTYPE DHT11 //Дефиниране на тип данни DHTTYPE
const int DHTPin = 0;  //Инициализиране на пин на който ще бъде свързан сензорът
DHT dht(DHTPin, DHTTYPE);

// Временни променливи
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];


//Въведете нужните име на мрежа и парола
char ssid[] = "";                 // Име на WiFi мрежа
char pass[] = "";                 // Парола на мрежата
byte mac[6];

WiFiServer server(80);
IPAddress ip(192, 168, 0, 106); // Предпочитан IP адрес за ESP8266
IPAddress gateway(192, 168, 0, 1); //IP адрес на шлюзът
IPAddress subnet(255, 255, 255, 0); // Маска на мрежата

WiFiClient client;
MySQL_Connection conn((Client *)&client);//Осъшествяване на връка с MySQL

char INSERT_SQL[] = "INSERT INTO weather_db.weather_station ( temperature, temperature_f, hum, temp_index_c, temp_index_f, rain, presure, dusting, sun) VALUES ( %0.0f, %0.0f, %0.0f, %0.0f , %0.0f)"; //SQL заявка към базата данни
char query[128];

//Въведете вашите нужните данни за вашият сървър база данни
IPAddress server_addr(192, 168 ,0, 109);          // MySQL IP адрес
char user[] = "";           // MySQL user
char password[] = "";       // MySQL password

void setup() {
 dht.begin(); //Стартиране на връзка със сензорът
  Serial.begin(115200); //Стартиране на връзка със серийният монитор

  pinMode(DHTPin, INPUT); 
  
// Изписване на съобщения в серийният монитор
  Serial.println("Initialising connection"); 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); // Конфигуриране на връзката към WiFi
  WiFi.begin(ssid, pass);  //Стартиране на връзка с WiFi

// Принтиране на символ „ . “ по време на финалното свързване с WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

// Принтиране в серийният монитор статусът на връзката
  Serial.println("");
  Serial.println("WiFi Connected");

// Принтиране в серийният монитор МАС адресът на ESP8266
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

//Изписване на съобщение при стартиране на връзка с MySQL
  Serial.println("Connecting to database");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to MySQL Server!");  //Изписване в серийния монитор при успешна връзка с MySQL
 
}

void loop() {

  delay(1800000); //Изчакване от 1800000 мс / 30 мин
  float h = dht.readHumidity();
  // Четене на температурата по Целзий (стойност по подразбиране)
  float t = dht.readTemperature();
  // Четене на температурата по Фаренхайт (ако isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Проверка за наличие на стойностите узмерени от сензорът (ако не са налични, опитва отново).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Изчисляване на топлинния индекс по Фаренхайт
  float hif = dht.computeHeatIndex(f, h);
  // Изчисляване на топлинния индекс по Целзий( ако isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

//Принтиране на измерените и изчислени стойноти в серийният монитор
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

            

  sprintf(query, INSERT_SQL, t, f, hic, hif, h); //принтиране на SQL заявката 

  Serial.println("Recording data.");
  Serial.println(query); принтиране на SQL заявката в серийния монитор
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  
  cur_mem->execute(query); // Изпълняване на заявката към MySQL 

  delete cur_mem; // изтриване на променливата
}
