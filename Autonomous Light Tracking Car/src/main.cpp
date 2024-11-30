#include <DHT.h>
const int den_trai = A0;
const int den_phai = A1;
const int den_giua = A2;
const int nguong = 500;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int soil_pin = A3;
const int nguong_soil = 500;
const int motor1Pin1 = 3;
const int motor1Pin2 = 4;
const int motor2Pin1 = 5;
const int motor2Pin2 = 6;
void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  int giatri_trai = analogRead(den_trai);
  int giatri_phai = analogRead(den_phai);
  int giatri_giua = analogRead(den_giua);
  int bin_trai = (giatri_trai > nguong) ? 1 : 0;
  int bin_phai = (giatri_phai > nguong) ? 1 : 0;
  int bin_giua = (giatri_giua > nguong) ? 1 : 0;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int giatri_soil = analogRead(soil_pin);
  int bin_soil = (giatri_soil > nguong_soil) ? 1 : 0;
  Serial.print("Light Sensors - Trái: ");
  Serial.print(bin_trai);
  Serial.print(", Giữa: ");
  Serial.print(bin_giua);
  Serial.print(", Phải: ");
  Serial.println(bin_phai);
  Serial.print("Nhiệt độ không khí: ");
  Serial.print(temperature);
  Serial.print(" °C | Độ ẩm không khí: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Độ ẩm đất: ");
  Serial.print(giatri_soil);
  Serial.print(" (");
  Serial.print(bin_soil ? "Ướt" : "Khô");
  Serial.println(")");
  if (bin_giua == 1 && bin_trai == 1 && bin_phai == 1) {
    Dung();
  } else if (bin_giua == 0 && bin_trai == 0 && bin_phai == 0) {
    Dung();
  } else if (bin_giua == 0 && bin_phai == 0) {
    Phai();
    delay(2000);
    Thang();
  } else if (bin_giua == 0 && bin_trai == 0) {
    Trai();
    delay(2000);
    Thang();
  } else if (bin_giua == 1) {
    Thang();
  } else if (bin_trai == 1) {
    Trai();
  } else if (bin_phai == 1) {
    Phai();
  } else {
    Dung();
  }
  delay(1000);
}
void Thang() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}
void Dung() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
void Trai() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}
void Phai() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}