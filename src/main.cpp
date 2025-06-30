#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";
String ID = "";
String ID2 = "";

#define RELE_PIN 26

void setup() {
  Serial.begin(9600);
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);
}

void loop() {

  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WiFi!");
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    tentativas++;
    if (tentativas > 40) {
      Serial.println("Conexão falhou");
      WiFi.disconnect();
      WiFi.begin(ssid, password);
      tentativas = 0;
    }
  }

  Serial.println(" Conectado!!!!  ");

  

  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + ID + "/exec?read";
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  } else  {
    Serial.println("Erro HTTP");
  }

  if (payload == "ON") {
    digitalWrite(RELE_PIN, HIGH);
    Serial.println("LIGADO");
    String url2 = "https://script.google.com/macros/s/" + ID2 + "/exec?read";
    delay(100);
    http.begin(url2.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode2 = http.GET();
    String payload2;
    if (httpCode2 > 0) {
      payload2 = http.getString();
      Serial.println(httpCode2);
      Serial.println(payload2);
    } else {
      Serial.println("Erro HTTP");
    }
    http.end();


    float horas = payload2.toFloat();
    unsigned long delay_ms = horas * 3600 * 1000;

    Serial.print("Próxima  leitura em: ");
    Serial.print(delay_ms/1000);
    Serial.print("segundos.");

    delay(delay_ms);

  } else {
    digitalWrite(RELE_PIN, LOW);
    Serial.println("DESLIGADO");
    delay(300);
  }

}