{\rtf1\ansi\ansicpg1252\deff0\nouicompat{\fonttbl{\f0\fnil\fcharset0 Calibri;}}
{\*\generator Riched20 10.0.19041}\viewkind4\uc1 
\pard\sa200\sl276\slmult1\f0\fs22\lang9 #include <EtherCard.h>\par
\par
#include "DHT.h"\par
\par
#define DHTPIN 2     // Digital pin connected to the DHT sensor\par
\par
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321\par
\par
DHT dht(DHTPIN, DHTTYPE);\par
\par
\par
\par
\par
\par
\par
\par
// ethernet interface mac address, must be unique on the LAN\par
static byte mymac[] = \{ 0x74,0x69,0x69,0x2D,0x30,0x31 \};\par
static byte myip[] = \{ 192,168,1,203 \};\par
\par
byte Ethernet::buffer[500];\par
BufferFiller bfill;\par
\par
static word homePage() \{\par
  char * humidity;\par
  char * temperature;\par
\par
  float h = dht.readHumidity();\par
  float t = dht.readTemperature();\par
  \par
  char s1[6]; \par
  char s2[6]; \par
  humidity = dtostrf(h ,2,2,s1);\par
  temperature = dtostrf(t ,2,2,s2);\par
  \par
  \par
  \par
  bfill = ether.tcpOffset();\par
  bfill.emit_p(PSTR(\par
    "HTTP/1.0 200 OK\\r\\n"\par
    "Content-Type: text/html\\r\\n"\par
    "Pragma: no-cache\\r\\n"\par
    "\\r\\n"\par
    "<meta http-equiv='refresh' content='1'/>"\par
    "<title>RBBB server</title>"\par
      "<h1>humidity:$S<br>temperature:$S</h1>"),\par
      humidity, temperature);\par
      Serial.println("h:");\par
      Serial.println(h);\par
      Serial.println("t:");\par
      Serial.println(t);\par
  return bfill.position();\par
\}\par
\par
void setup () \{\par
  \par
  Serial.begin(57600);\par
  dht.begin();\par
  Serial.println(F("\\n[RBBB Server]"));\par
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin\par
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)\par
    Serial.println(F("Failed to access Ethernet controller"));\par
  ether.staticSetup(myip);\par
\}\par
\par
void loop () \{\par
  word len = ether.packetReceive();\par
  word pos = ether.packetLoop(len);\par
\par
  if (pos)  // check if valid tcp data is received\par
    ether.httpServerReply(homePage()); // send web page data\par
\}\par
}
 