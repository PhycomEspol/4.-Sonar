//librerias importadas
#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>
#include <Servo.h>

Servo servo1;//servo
const int led_roj=2;//leds
const int led_ama=4;
const int led_ver=7;
const int trigPin=9;//sensor
const int ecoPin=10;
long duracion;//variables 
int distancia;
int ult_dist=0;//acumulador
const int buzzer=12;//buzzer

Adafruit_LiquidCrystal lcd(0);//la vdd q no se bien pero me funciono el lcd :'v

void setup(){
  //def pines
  pinMode(led_roj,OUTPUT);
  pinMode(led_ama,OUTPUT);
  pinMode(led_ver,OUTPUT);
  pinMode(trigPin , OUTPUT);
  pinMode(ecoPin, INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  //def pin servo
  servo1.attach(11);
  //iniciar lcd
  lcd.begin(16,2);lcd.setCursor(1,0);
  lcd.print("Hola");
  delay(200);
  lcd.clear();
}

void loop(){
  //imprimir en el lcd
  lcd.setCursor(0,0);
  lcd.print("Distancia:");
  lcd.setCursor(14,0);
  lcd.print("cm");
  //giro servo der- izq
  int i;
  for(i=0;i<90;i++){
  	servo1.write(i);
    delay(5);//esto en teoria seria como la velocidad a la q se mueve
    
    //invoca a las respectivas funciones y lo realiza/calcula
    distancia= calcular_distancia();
    mostrar_distancia(distancia, ult_dist);
  	medir_distancia(distancia);
  }
  
  //giro servo izq-der
  for(i=90;i>0;i--){
  	servo1.write(i);
    delay(5);
  	distancia= calcular_distancia();
    mostrar_distancia(distancia, ult_dist);
	medir_distancia(distancia);
  }
}


//funcion returna el valor de la distancia
int calcular_distancia(){
	//como un reset del sensor para q no de fallos al momento de inciarlo
  	digitalWrite(trigPin, LOW);
  	delayMicroseconds(2); 
  	//envio del pulso 
  	digitalWrite(trigPin, HIGH);
  	delayMicroseconds(10); 
  	digitalWrite(trigPin, LOW);
  	//recibe el pulso y calcula la distancia q recorrio el pulso
  	duracion=pulseIn(ecoPin,HIGH);
  	distancia=(duracion*0.034)/2;
    return distancia;
}


//funcion no returna pero comprueba el rango de distancia y enciede el respectivo led
void medir_distancia(int distancia){
	//en que distancia esta
  	if (distancia<100){
  		tone (buzzer,466,500);//tone(pin, frequency, duration)
    	delay (300);
    	digitalWrite(led_roj,HIGH);
    	digitalWrite(led_ama,LOW);
		digitalWrite(led_ver,LOW);
  	}
  	else if (distancia>99;distancia<200){
  		tone (buzzer,440,500);
    	delay(100);
    	digitalWrite(led_roj,LOW);
    	digitalWrite(led_ama,HIGH);
		digitalWrite(led_ver,LOW);
  	}
  	else{
  		noTone(buzzer);
    	digitalWrite(led_roj,LOW);
    	digitalWrite(led_ama,LOW);
    	digitalWrite(led_ver,HIGH);
  	}	
}  

//funcion comprueba la distancia 
void mostrar_distancia(int distancia,int ult_dist){
	//muestra x pantalla la distancia (como numero entero)
  	if (distancia!=ult_dist){
    	lcd.setCursor(11,0);
      	lcd.print("   ");
  		lcd.setCursor(11,0);
  		lcd.print(distancia);
  		delay(100);
  		ult_dist=distancia;
  	}  
}
