#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;


void setup() {
Serial.begin(115200);
SerialBT.begin("ESP32BT"); //Bluetooth device name
Serial.println("BT listo para emparejarse");

}

void loop() {

if(SerialBT.available()){
 
char dato = SerialBT.read();
Serial.write(dato);


if(dato == '1'){
  Serial.println("LED ON");
  digitalWrite(2, HIGH);
}
if(dato == '0'){
  Serial.println("LED OFF");
  digitalWrite(2, LOW);
}
}

if(Serial.available()){
  SerialBT.write(Serial.read());
}

}

