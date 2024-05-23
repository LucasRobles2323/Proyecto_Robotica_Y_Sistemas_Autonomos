#define TRIGGER_PIN 12
#define ECHO_PIN 11

long distancia;

void setup(){
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}
void loop(){
  distancia=Ultrasonido(TRIGGER_PIN, ECHO_PIN);
  Serial.println((distancia));
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