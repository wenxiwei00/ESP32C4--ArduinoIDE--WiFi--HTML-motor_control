
#include <WiFi.h>
#include <WebServer.h>
#include "MyHTML.h"

WebServer server(80); // 使用 WebServer 对象

// 定义硬件引脚
#define LEDPIN 4
#define Dir1_1A 7
#define Dir2_2A 6

const char* ssid = "xiwei"; // 你的WiFi SSID
const char* password = "123456789"; // 你的WiFi密码

const int ledChannel = 0;
const int ledFrequency = 30;
const int ledResolution = 14; //0-16383


void handleRoot() {
  server.send(200, "text/html", body);
}

// void handleF() {
//   String direction = server.arg("dir");
//   if (direction == "forward") {
//     digitalWrite(Dir1_1A, LOW);
//     digitalWrite(Dir2_2A, HIGH);
//   }
//   server.send(200, "text/html", body);
// }

// void handleB() {
//   String direction = server.arg("dir");
//   if (direction == "backward") {
//     digitalWrite(Dir1_1A, HIGH);
//     digitalWrite(Dir2_2A, LOW);
//   }
//   server.send(200, "text/html", body);
// }

void handleDirection() {
  String direction = server.arg("dir");
  if (direction == "forward") {
    digitalWrite(Dir1_1A, LOW);
    digitalWrite(Dir2_2A, HIGH);
  } else if (direction == "backward") {
    digitalWrite(Dir1_1A, HIGH);
    digitalWrite(Dir2_2A, LOW);
  }
  server.send(200, "text/html", body);
}

void handleSpeed() {
  int speed = server.arg("speed").toInt();

  int duty = map(speed, 0, 100, 0, 16383);

  ledcWrite(ledChannel, duty);
  server.send(200, "text/html", body);
  Serial.print(speed);
}

void setup() {
  Serial.begin(115200);

  // 设置硬件引脚模式
  pinMode(Dir1_1A, OUTPUT);
  pinMode(Dir2_2A, OUTPUT);
  pinMode(LEDPIN, OUTPUT);

  // 设置 LEDC PWM 控制
  ledcSetup(ledChannel, ledFrequency, ledResolution);
  ledcAttachPin(LEDPIN, ledChannel);

  // 设置软AP并启动服务器
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  // server.on("/set_direction", HTTP_GET, handleB);
  // server.on("/set_direction", HTTP_GET, handleF);
  server.on("/set_direction", HTTP_GET, handleDirection);
  server.on("/set_speed", HTTP_GET, handleSpeed);

  server.begin();
}

void loop() {
  server.handleClient();
}


