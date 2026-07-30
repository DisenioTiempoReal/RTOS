#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Pines del RC522
#define SS_PIN   21
#define RST_PIN  22

MFRC522 rfid(SS_PIN, RST_PIN);

void setup()
{
    Serial.begin(115200);

    SPI.begin();             // SCK=18, MISO=19, MOSI=23 (ESP32)
    rfid.PCD_Init();

    Serial.println();
    Serial.println("================================");
    Serial.println("Lector RFID RC522");
    Serial.println("Acerque una tarjeta...");
    Serial.println("================================");
}

void loop()
{
    // ¿Hay una tarjeta presente?
    if (!rfid.PICC_IsNewCardPresent())
        return;

    // ¿Se pudo leer?
    if (!rfid.PICC_ReadCardSerial())
        return;

    Serial.print("UID: ");

    for (byte i = 0; i < rfid.uid.size; i++)
    {
        if (rfid.uid.uidByte[i] < 0x10)
            Serial.print("0");

        Serial.print(rfid.uid.uidByte[i], HEX);
        Serial.print(" ");
    }

    Serial.println();

    // También en decimal
    Serial.print("UID Decimal: ");

    for (byte i = 0; i < rfid.uid.size; i++)
    {
        Serial.print(rfid.uid.uidByte[i]);

        if (i < rfid.uid.size - 1)
            Serial.print("-");
    }

    Serial.println();

    // Tipo de tarjeta
    MFRC522::PICC_Type type = rfid.PICC_GetType(rfid.uid.sak);

    Serial.print("Tipo: ");
    Serial.println(rfid.PICC_GetTypeName(type));

    Serial.println("---------------------------");

    // Finalizar comunicación
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    delay(500);
}