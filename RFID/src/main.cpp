#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN   21
#define RST_PIN  22


MFRC522 rfid(SS_PIN, RST_PIN);

// UID autorizado
byte tarjetaPermitida[] = {
    0x04, 0xBD, 0x49, 0xF2, 0x90, 0x5B, 0x80
};

void setup()
{
    Serial.begin(115200);

    SPI.begin();

    rfid.PCD_Init();

    Serial.println("Sistema RFID listo");
}

void loop()
{
    if (!rfid.PICC_IsNewCardPresent())
        return;

    if (!rfid.PICC_ReadCardSerial())
        return;

    bool autorizado = true;

    // Verifico que tengan la misma longitud
    if (rfid.uid.size != sizeof(tarjetaPermitida))
    {
        autorizado = false;
    }
    else
    {
        for (byte i = 0; i < rfid.uid.size; i++)
        {
            if (rfid.uid.uidByte[i] != tarjetaPermitida[i])
            {
                autorizado = false;
                break;
            }
        }
    }

    Serial.print("UID: ");

    for (byte i = 0; i < rfid.uid.size; i++)
    {
        if (rfid.uid.uidByte[i] < 0x10)
            Serial.print("0");

        Serial.print(rfid.uid.uidByte[i], HEX);
        Serial.print(" ");
    }

    if (autorizado)
    {
        Serial.println(" --> ACCESO PERMITIDO");
    }
    else
    {
        Serial.println(" --> ACCESO DENEGADO");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    delay(1000);
}