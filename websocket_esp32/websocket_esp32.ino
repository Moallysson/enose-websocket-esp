#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "<id-rede>";
const char* password = "<senha-da-rede>";
const char* websocket_server = ""; // IP do servidor Python
const int websocket_port = 8765;

WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected!");
  webSocket.begin(websocket_server, websocket_port, "/");
}

void loop() {
  webSocket.loop();
  
  int sensor_value = analogRead(34);
  String message = String(sensor_value);

  webSocket.sendTXT(message);
  delay(1000); // Enviar dados a cada 1 segundo
}
