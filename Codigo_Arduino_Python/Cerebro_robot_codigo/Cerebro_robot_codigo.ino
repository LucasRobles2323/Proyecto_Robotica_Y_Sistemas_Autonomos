#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <SoftwareSerial.h>
SoftwareSerial BT1(2,3); // RX, TX

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

// UltraSonido
int TRIG = 11;
int ECHO = 12;

// Motores
#define INT1 5
#define INT2 6
#define INT3 9
#define INT4 10

void setup() {
  
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  // Bluethoot
  Serial.println("Enter AT commands:");
  BT1.begin(9600);

  // Ultrasonido
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

  // Motor
  pinMode(INT1,OUTPUT);
  pinMode(INT2,OUTPUT);
  pinMode(INT3,OUTPUT);
  pinMode(INT4,OUTPUT);
  motorA('S', 0);
  motorB('S', 0);

  // Wait for initialization and calibration to finish
  delay(500);
}
 
void loop() {
  if (BT1.available()) { 
    String received = GetLine();
    Serial.println("Received command: " + received);

    enviarDatosSensores(); 
    
    received.trim(); // Elimina espacios al inicio y al final
    if (received.equals("L")) { // Gira Left
      BT1.print("Gira Izquierda: \n");
      Detener();
      girarIzquierda90();
      Detener();
    }
    else if(received.equals("R")){// Gira Right
      BT1.print("Gira Derecha: \n");
      Detener();
      girarDerecha90();
      Detener();
    }
    else if(received.equals("F")){ // Front
      BT1.print("Avanzar: \n");
      Detener();
      Avanzar();
      Detener();
    }
    else if(received.equals("B")){ // Back
      BT1.print("Retroceder: \n");
      Detener();
      Retroceder();
      Detener();
    }
    else {
      // Comando no reconocido
      Serial.println("Received command not recognized: " + received);
      BT1.print("Comando no reconocido \n");
    }
  }
}

void enviarDatosSensores() {
  String sensorData = readRGB() + readUltraSonido();
  BT1.println(sensorData);
  Serial.println(sensorData);
}

String readRGB(){
  String output = " R:";
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    output += String(red_light);
    output += "G:";
    output += String(green_light);
    output += "B:";
    output += String(blue_light);
  }

  return output;
}

String readUltraSonido(){
  String dis = "D:";
  double distancia=Ultrasonido(TRIG, ECHO);
  dis += distancia;
  return dis;
}

void Detener(){
  // Detener los motores A y B
  motorA('S', 0);
  motorB('S', 0);
}

void Avanzar(){
  // Definir la velocidad para avanzar recto
  int velA = 225;
  int velB = 150;
  
  // Avanzar
  motorA('A', velA); // Motor A gira hacia adelante
  motorB('A', velB); // Motor B gira hacia adelante
  
  unsigned long tiempoAvance = 700; // Tiempo estimado para avanzar 1 cuadro

  unsigned long startTime = millis();

  // Enviar datos continuamente durante el movimiento
  while (millis() - startTime < tiempoAvance) {
    enviarDatosSensores();
    delay(100); // Esperar un tiempo antes de enviar los siguientes datos
  }
}

void Retroceder(){
  // Definir la velocidad para retroceder recto
  int velA = 225;
  int velB = 150;
  
  // Retroceder
  motorA('R', velA); // Motor A gira hacia atrás
  motorB('R', velB); // Motor B gira hacia atras
  
  unsigned long tiempoRetrocede = 700; // Tiempo estimado para retroceder 1 cuadro.

  unsigned long startTime = millis();

  // Enviar datos continuamente durante el movimiento
  while (millis() - startTime < tiempoRetrocede) {
    enviarDatosSensores();
    delay(100); // Esperar un tiempo antes de enviar los siguientes datos
  }
}

void girarDerecha90() {
  // Definir la velocidad y la dirección para girar hacia la derecha
  int velocidadGiro = 200;
  
  // Girar a la izquierda ajustando la velocidad de los motores
  motorA('R', velocidadGiro); // Motor A gira hacia atrás
  motorB('A', velocidadGiro); // Motor B gira hacia adelante
  
  unsigned long tiempoGiro = 300; // Tiempo estimado para girar 90 grados
  
  unsigned long startTime = millis();

  // Enviar datos continuamente durante el movimiento
  while (millis() - startTime < tiempoGiro) {
    enviarDatosSensores();
    delay(100); // Esperar un tiempo antes de enviar los siguientes datos
  }
}

void girarIzquierda90() {
  // Definir la velocidad y la dirección para girar hacia la izquierda
  int velocidadGiro = 210;
  
  // Girar a la derecha ajustando la velocidad de los motores
  motorA('A', velocidadGiro); // Motor A gira hacia adelante
  motorB('R', velocidadGiro); // Motor B gira hacia atrás
  
  unsigned long tiempoGiro = 300; // Tiempo estimado para girar 90 grados
  
  unsigned long startTime = millis();

  // Enviar datos continuamente durante el movimiento
  while (millis() - startTime < tiempoGiro) {
    enviarDatosSensores();
    delay(100); // Esperar un tiempo antes de enviar los siguientes datos
  }
}

String GetLine(){
  String S = "";
  if (BT1.available())
  {
    char c = BT1.read();
    while (c != '\n') // Hasta que el caracter sea intro
    {
      S += c;
      delay(25);
      if (BT1.available()) {
        c = BT1.read();
      }
    }
    Serial.println("Received from Bluetooth: " + S);
    return S;
  }
  return ""; // Retorna cadena vacía si no hay datos disponibles
}

long Ultrasonido(int trigger, int eco){
  long duration; //timepo que demora en llegar el eco
  long distance; //distancia en centimetros

  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration = pulseIn(eco, HIGH); //obtenemos el ancho del pulso
  distance = (duration*.0343)/2;
  return distance;
}

void motorA(char d, int velocity){
  if(d =='A'){
    analogWrite(INT1,LOW);
    analogWrite(INT2,velocity);
  }else if (d =='R'){
    analogWrite(INT1,velocity);
    analogWrite(INT2,LOW);
  }else{
    digitalWrite(INT1,LOW);
    digitalWrite(INT2,LOW);
  }
}

void motorB(char d,int velocity){
  if(d =='A'){
    analogWrite(INT3,LOW);
    analogWrite(INT4,velocity);
  }else if (d =='R'){
    analogWrite(INT3,velocity);
    analogWrite(INT4,LOW);
  }else{
    analogWrite(INT3,LOW);
    analogWrite(INT4,LOW);
  }
}