#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Preferences.h>

// Instancias de las librerías
BluetoothSerial SerialBT;
Preferences preferences;

// Variable global para almacenar el ID en RAM
String deviceID = "";

void setup() {
  // Inicializamos el monitor serial físico para debug
  Serial.begin(115200);
  
  // Inicializamos el Bluetooth con el nombre visible del dispositivo
  SerialBT.begin("ESP32_TEST"); 
  Serial.println("El dispositivo Bluetooth está listo para emparejar como 'ESP32_Taller'");

  // 1. LEER EL ID GUARDADO AL INICIAR
  // Abrimos el namespace "config" en modo SOLO LECTURA (true) para seguridad
  preferences.begin("config", true);
  
  // Leemos la clave "id_local". Si no existe todavía, por defecto asigna "0000"
  deviceID = preferences.getString("id_local", "0000");
  
  // Cerramos la sesión de preferences
  preferences.end();

  // Mostramos el ID recuperado por el monitor serial de la PC
  Serial.println("----------------------------------------");
  Serial.print("ID del dispositivo recuperado de Flash: ");
  Serial.println(deviceID);
  Serial.println("----------------------------------------");
}

void loop() {
  // Verificamos si llegaron datos desde la App móvil por Bluetooth
  if (SerialBT.available()) {
    
    // Leemos la cadena entrante hasta encontrar un salto de línea
    String mensaje = SerialBT.readStringUntil('\n');
    
    // Limpiamos espacios en blanco o caracteres ocultos como '\r'
    mensaje.trim(); 

    // Validamos si el mensaje empieza con el comando requerido "CMDID:"
    if (mensaje.startsWith("CMDID:")) {
      
      // Extraemos el valor del ID. Cortamos la cadena a partir del caracter 6 
      // (justo después del caracter de dos puntos ':')
      String nuevoID = mensaje.substring(6);
      nuevoID.trim(); // Limpieza extra por las dudas

      // 2. GUARDAR EL NUEVO ID EN MEMORIA PERSISTENTE
      // Abrimos el namespace "config" en modo LECTURA/ESCRITURA (false)
      preferences.begin("config", false);
      
      // Guardamos la cadena en la clave "id_local"
      preferences.putString("id_local", nuevoID);
      
      // Cerramos para asegurar el volcado a la memoria flash NVS
      preferences.end();

      // Actualizamos nuestra variable en RAM
      deviceID = nuevoID;

      // Enviamos una respuesta de éxito de vuelta al celular por Bluetooth
      SerialBT.print("OK: ID actualizado a -> ");
      SerialBT.println(deviceID);

      // Log por el monitor serial de la PC
      Serial.print("Nuevo ID configurado via BT y guardado: ");
      Serial.println(deviceID);
    }
  }
}