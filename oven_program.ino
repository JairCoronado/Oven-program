#include <HCSR04.h>

// Initialize sensor that uses digital pins 13 and 12.
const int triggerPin = A2;
const int echoPin = A1;
const int LEDR=9;
const int LEDV=8;
const int Lampara=10;
const int boton=2;
const int selector=3;
int range;
int cont;
int buttonState = 0;
int estadoselector = 0; 

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    pinMode(LEDR, OUTPUT); // se declara la variable LEDR como salida (OUTPUT)
    pinMode(LEDV, OUTPUT);// se declara la variable LEDV como salida (OUTPUT)
    pinMode(Lampara, OUTPUT);// se declara la variable Lamapara como salida (OUTPUT)
    pinMode(boton, INPUT); // se declara la variable boton como entrada (INPUT)
    pinMode(selector, INPUT);// se declara la variable selector como entrada (INPUT)
    range=0;  // se inicialisan los contraodres en 0
    cont=0;   // se inicialisan los contraodres en 0

}

void loop () {
  

  switch (range) {
    case 0: 
    digitalWrite(Lampara, LOW);        // enciende la lampara
      delay(100);
      Serial.println("Horno encendido");
 for (int i = 0; i <= 1248; i++) {  //1248 ciclos de tiempo 45 minutos
      if (distanceSensor.measureDistanceCm()<15) {  // distancia de sensor ultrasonico
Serial.print("i=");
Serial.print(i);
Serial.print("\n");
digitalWrite(Lampara, LOW);        // enciende la lampara
      delay(100);
    digitalWrite(LEDV, LOW);          // Led verde encendido
    delay(10);
    digitalWrite(LEDR, HIGH);        //Led rojo apagado
    i=0;                                     //conteo de ciclos
delay(500);
  }
  else {
    // turn LED on:
Serial.print("i=");
Serial.print(i);
Serial.print("\n");
    digitalWrite(LEDV, LOW);
    delay(10);
    digitalWrite(LEDR, HIGH);
delay(500);
  }}
     range=1;       // cambio a caso 1
      break;
//-----------------------------------------------------------------------alarma
    case 1:   
      Serial.println("pre alarma");
for (int d = 0; d <= 280; d++) { //280 tiempo de ciclo de la pre alarma 5 minutos
      digitalWrite(LEDV, LOW);
    delay(10);
    digitalWrite(LEDR, LOW);
    delay(10);
buttonState = digitalRead(boton);
 if (buttonState == HIGH) {
    // turn LED on:
d=280;
    digitalWrite(LEDV, HIGH);
    delay(10);
    digitalWrite(LEDR, HIGH);
delay(500);
  }
  if (buttonState == LOW) {
    // turn LED on:
Serial.print("d=");
Serial.print(d);
Serial.print("\n");
delay(500);
  }}
if (buttonState == HIGH) {
    // turn LED on:
range=0;
    digitalWrite(LEDV, HIGH);
    delay(10);
    digitalWrite(LEDR, HIGH);
delay(500);
  }
  else{
 range=2;}
       digitalWrite(LEDV, HIGH);
    delay(10);
    digitalWrite(LEDR, LOW);
    delay(10);
      break;
/*-------------------------------------EL horno se apaga en este caso 2, pero hances hace un parpadeo*/
    case 2:    
      Serial.println("Horno apagado");
                    // el contador de restablecer
Serial.println(cont);
      digitalWrite(Lampara, HIGH);   
      delay(10);
      digitalWrite(LEDV, HIGH);
      delay(10);
      digitalWrite(LEDR, LOW);
      delay(10);

      buttonState = digitalRead(boton);
       if(buttonState==HIGH){
      digitalWrite(LEDV, HIGH);
      delay(10);
      digitalWrite(LEDR, LOW);
      delay(10);
      digitalWrite(Lampara, HIGH);   // apaga la lampara del horno
      delay(10);
      cont=cont+1;  
      range=4;}
      if(cont==10){
       range=3; 
       delay(10);
      }

      break;
//-------------------------------------Horno alarmado solo ca,biara a horno encendido mandado una señal HIGH o bien 1 o bien 5v al pin del selector2 
//-------------------------------------y resetea el contador
    case 3:    
      Serial.println("Horno alarmado");
       estadoselector = digitalRead(selector);
       while(estadoselector = HIGH){
      digitalWrite(Lampara, HIGH);
      digitalWrite(LEDR, LOW);            // se prende el led rojo
      delay(100); 
      delay(100); }
      cont=0;
      range=0;       
      break;
//-----------------------------------------El horno esta apagado, y manda a llamar la funcion restablecer, el cual enciende el horno y en la variable cont suma 1 y se guarda si se apaga
//-----------------------------------------el arduino se reiniciara automaticamente el contador, cuando se alarme encendera el led rojo y verde
    case 4:   
      Serial.println("restableciendo");     
      buttonState = digitalRead(boton);   // lee el valor del el pin boton y guarda el estado boleando en la variable estadoboton
      if(buttonState==HIGH){              // lee es valor guardado en la variable estado del boton
      digitalWrite(Lampara, LOW);        // enciende la lampara
      delay(100); 
      digitalWrite(LEDR, HIGH);            // se apaga el led rojo
      delay(100); 
      digitalWrite(LEDV, LOW);           // enciende el led verde
      delay(100);           // tiempo para hacer el cambio de estado en el pin
      
      }range=0;
      break;

  }
  delay(1); 

}
