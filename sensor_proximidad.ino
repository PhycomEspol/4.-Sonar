//librerias importadas
#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>

const int led_roj=2;//leds
const int led_ama=4;
const int led_ver=7;
const int trigPin=9;//sensor
const int ecoPin=10;
long duracion;//variables 
int distancia;
int max_val=300;int min_val=10;
int ult_dist=0;//acumulador
const int buzzer=12;//buzzer

Adafruit_LiquidCrystal lcd(0);

void setup(){
  //def pines
  pinMode(led_roj,OUTPUT);
  pinMode(led_ama,OUTPUT);
  pinMode(led_ver,OUTPUT);
  pinMode(trigPin , OUTPUT);
  pinMode(ecoPin, INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  //iniciar lcd
  lcd.begin(16,2);
  presenta();
}

void loop(){
  //invoca a las respectivas funciones y lo realiza/calcula
  distancia= calcular_distancia();
  mostrar_distancia(distancia);
  medir_distancia(distancia);
}

//presentacion   
void presenta(){
	lcd.setCursor(0,0);lcd.print("PHYSONIC");
    lcd.setCursor(3,1);lcd.print("PRESENTA:");
    delay(3000);lcd.clear();
    lcd.setCursor(5,0);lcd.print("SENSOR ");
    lcd.setCursor(2,1);lcd.print("ULTRASONICO");
    delay(3000);lcd.clear();
  	//imprimir en el lcd
  	lcd.setCursor(0,0);
  	lcd.print("Cargando...");
  	delay(2000);lcd.clear();
}

//funcion returna el valor de la distancia
int calcular_distancia(){
	//apaga el sensor para q no de fallos al momento de inciarlo
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
  	if (distancia<min_val){
  		tone (buzzer,466,500);//tone(pin, frequency, duration)
    	delay (300);
    	digitalWrite(led_roj,HIGH);
    	digitalWrite(led_ama,LOW);
		digitalWrite(led_ver,LOW);
  	}
  	else if (distancia>min_val;distancia<max_val){
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
void mostrar_distancia(int distancia){
    if (distancia<min_val){
        lcd.clear();
        lcd.setCursor(3,0);
  		lcd.print("CUIDADO!!");
  	}
  	else if (distancia>min_val;distancia<max_val){
      if (distancia!=ult_dist){
        lcd.clear();
      	lcd.setCursor(0,0);
		lcd.print("Distancia:");
        lcd.print(distancia);
  		lcd.print("cm");
        ult_dist=distancia;
      }
    }
  	else{
      	lcd.clear();
      	lcd.setCursor(0,0);
        lcd.print("No Hay Nada");	
  	}	
    
}
