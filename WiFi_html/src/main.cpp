#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "miredwifi";
const char* password = "clavesecreta";

WebServer server(80);

const int led1 = 2;
const int led2 = 4;
const int led3 = 5;
const int led4 = 18;

//-------------------------------------------------

void paginaPrincipal()
{
  String html;

  html += "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";

  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";

  html += "<style>";

  html += "body{font-family:Arial;background:#f2f2f2;text-align:center;}";

  html += "button{";
  html += "width:140px;";
  html += "height:50px;";
  html += "font-size:20px;";
  html += "margin:10px;";
  html += "border:none;";
  html += "border-radius:10px;";
  html += "cursor:pointer;";
  html += "}";

  html += ".on{background:#00cc66;color:white;}";
  html += ".off{background:#ff4444;color:white;}";

  html += "</style>";

  html += "</head>";
  html += "<body>";

  html += "<h1>Servidor Web ESP32</h1>";
  html += "<h2>Control de LEDs</h2>";

  html += "<p>LED 1 (GPIO2)</p>";
  html += "<a href='/L1ON'><button class='on'>ENCENDER</button></a>";
  html += "<a href='/L1OFF'><button class='off'>APAGAR</button></a>";

  html += "<p>LED 2 (GPIO4)</p>";
  html += "<a href='/L2ON'><button class='on'>ENCENDER</button></a>";
  html += "<a href='/L2OFF'><button class='off'>APAGAR</button></a>";

  html += "<p>LED 3 (GPIO5)</p>";
  html += "<a href='/L3ON'><button class='on'>ENCENDER</button></a>";
  html += "<a href='/L3OFF'><button class='off'>APAGAR</button></a>";

  html += "<p>LED 4 (GPIO18)</p>";
  html += "<a href='/L4ON'><button class='on'>ENCENDER</button></a>";
  html += "<a href='/L4OFF'><button class='off'>APAGAR</button></a>";

  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

//-------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", paginaPrincipal);

  server.on("/L1ON", []()
  {
      digitalWrite(led1, HIGH);
      paginaPrincipal();
  });

  server.on("/L1OFF", []()
  {
      digitalWrite(led1, LOW);
      paginaPrincipal();
  });

  server.on("/L2ON", []()
  {
      digitalWrite(led2, HIGH);
      paginaPrincipal();
  });

  server.on("/L2OFF", []()
  {
      digitalWrite(led2, LOW);
      paginaPrincipal();
  });

  server.on("/L3ON", []()
  {
      digitalWrite(led3, HIGH);
      paginaPrincipal();
  });

  server.on("/L3OFF", []()
  {
      digitalWrite(led3, LOW);
      paginaPrincipal();
  });

  server.on("/L4ON", []()
  {
      digitalWrite(led4, HIGH);
      paginaPrincipal();
  });

  server.on("/L4OFF", []()
  {
      digitalWrite(led4, LOW);
      paginaPrincipal();
  });

  server.begin();

  Serial.println("Servidor iniciado");
}

//-------------------------------------------------

void loop()
{
  server.handleClient();
}