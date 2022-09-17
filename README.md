# 4.-Sonar
  
*El proyecto consiste en la elaboración de un sonar para detectar la proximidad de objetos  y prevenir colisiones, siendo una gran iniciativa  que se puede  implementar en los autos  al momento de estacionarse en lugares estrechos. Para ello, se necesitan **leds** y **buzzers** que fucnionan como advertencia a medida que dos objetos se acerquen entre sí, además, un dispositivo LCD que brinde la informacion de la distancia al usuario del vehiculo para que tenga en cuenta al momento de realizar cualquier maniobra.*  
  
> Materiales y precios:  
* 1 Sensor ultrasonido:            $3,50
* 17 Cables:                       $1,00
* 3 Resistencias de 220 ohmios:    $0,50
* 1 Buzzer:                        $0,25
* 3 Leds:                          $0,30
* 1 LCD 16x2:                      $7,00
* 1 arduino mega 2560:             $19,00


Dentro del Codigo Progamado encontramos diferentes secciones las cuales decidimoes separar en 4 funciones:   
*Funcion 1: Presentación*  
>void presenta(){  
 >>lcd.setCursor(0,0);  
  lcd.print("PHYSONIC");  
  lcd.setCursor(3,1);  
  lcd.print("PRESENTA:");  
  delay(3000);  
  lcd.clear();  
  lcd.setCursor(5,0);  
  lcd.print("SENSOR ");  
  lcd.setCursor(2,1);  
  lcd.print("ULTRASONICO");  
  delay(3000);  
  lcd.clear();  
  lcd.setCursor(0,0);  
  lcd.print("Cargando...");  
  delay(2000);  
  lcd.clear();}  
   
esat primera función la realizamos una sola vez al momento de inciar el dispositivo, en las primeras lineas del codigo muestra por pantalla(en el LCD) el nombre del grupo mediante lcd.print en la posicion indicada,cosa que logramos con lcd.setCursor, luego realiza una limpieza de la pantalla con lcd.clear y seuido de eso presenta el trabajo a realizar(en este caso sensor ultrasonico), nuevamente realiza otra limpieza de la pantalla e imprime la palabra "cargando".  
  
*Funcion 2: Cálculo de la distancia a la que se encuentra un objeto* 
>int calcular_distancia(){  
   >>digitalWrite(trigPin, LOW);  
  	delayMicroseconds(2);   
  	digitalWrite(trigPin, HIGH);  
  	delayMicroseconds(10);   
  	digitalWrite(trigPin, LOW);  
  	duracion=pulseIn(ecoPin,HIGH);  
	distancia=(duracion*0.034)/2;      
  	return distancia;}  

esta función la vamos a utilizar de manera repetida y nos ayudará a cálcular la distancia a la que se encuentre un objeto dentro del rango de visión del sensor ultrasonico en cada momento. Primeramente indicamos con digitalWrite que el pin trigger (del sensor) se encuentre apagado(LOW), esto con el objetivo de que no nos de un mal calculo por la detección de alguna señal previa,seguido encedemos el ping trigger(HIGH) para que emita una señal y nuevamente volvemos a apagar el ping trigger. Luego calculamos la duración (el tiempo) que tarda el sensor en recibir la señal previamente enviada, para ello usamos PulseIn y la almacenamos en una variable que se llam duracion; entonces para calcular la distancia usamos la formula distancia=velocidad x tiempo,siendo 0.034 aproximadamente la velocidad del sonido en microsegundos y duracion/2 el tiempo que tardo hasta llegar al objeto (notese que no usamos duracion  debido a quee esta representa el tiempo que tardo en llegar ahsta el objeto y regresar).  
  
*Funcion 3: Activacion de leds y buzzer*  
>void medir_distancia(int distancia){  
   >>if (distancia<min_val){  
  		tone (buzzer,466,500);  
    	delay (300);  
    	digitalWrite(led_roj,HIGH);  
    	digitalWrite(led_ama,LOW);  
		digitalWrite(led_ver,LOW);}  
  	else if (distancia>min_val;distancia<max_val){  
    	digitalWrite(led_roj,LOW);  
    	digitalWrite(led_ama,HIGH);  
		digitalWrite(led_ver,LOW);}  
  	else{    
    	digitalWrite(led_roj,LOW);  
    	digitalWrite(led_ama,LOW);  
    	digitalWrite(led_ver,HIGH);}	  
}  
  
Aquí verificamos si la distancia calculada en la funcion anterior se encuentra por debajo o encima de un valor maximo o minimo correspondientemente o si se encuentra dentro de dicho rango. Para ello la podemos separar en 3 casos: la primera "if" verifica si encuentra por debajo del valor minimo en caso de ser asi activa un buzzer a una frecuencua de 466 durante 500 microsegundos seguido de ello enciende el led rojo y apaga los leds amarillo y verde; el segundo "else if" verifica si se encuentra en medio del rango y en caso de ser asi encuende un led amarilo y apaga los leds rojo y verde; el tercero "else" el cual se realizara en caso de que no sucedan los 2 casos anteriores y enciende el led verde y apaga los leds amarillo y rojo.  
  
*Funcion 4: Mostrar mensaje*  
>void mostrar_distancia(int distancia){  
 >>if (distancia<min_val){  
        lcd.clear();  
        lcd.setCursor(3,0);  
  		lcd.print("CUIDADO!!");}  
  	else if (distancia>min_val;distancia<max_val){  
      if (distancia!=ult_dist){  
        lcd.clear();  
      	lcd.setCursor(0,0);  
		lcd.print("Distancia:");  
        lcd.print(distancia);  
  		lcd.print("cm");  
        ult_dist=distancia;}  
  	else{  
      	lcd.clear();  
      	lcd.setCursor(0,0);  
        lcd.print("No Hay Nada");}  
}  
  
Similarmente a la funcion anterior esta se subdivide en 3 casos iguales, para "if" verifica si la distancia es menor a la minima y en caso de serlo imprime en el sensor lcd Cuidado; para "else if" verifica que se encuentre dentro del rango minimo y maximo y en caso de ocurrir muestra a que distancia se encuentra mediante el lcd; y para  "else" unicamente muestra un mensaje "No hay nada".  
  
**Fallos y Consideraciones a tener el cuenta**  
* En primer lugar al iniciar una simulación en Arduino fijarse si la placa es original o genérica para descargar los respectivos paquetes y que la computadora reconozca el puerto del mismo para correr el programa.
* Por otro lado, fijarse en el modelo de la pantalla LCD sea 16x02 y que tenga incorporado con el interfaz 12C, el cuál funciona perfectamente con la librería LiquidCrystal_I2C.h pero también puede ser como la que se presenta en el código principal. 
* Al momento de llamar a la librería fijarse en la dirección de trabajo porque puede funcionar ya sea con 0x27 o 0X3f.  
* Otro punto importante es que el display LCD tiene conecciones específicas para el Arduino Uno (que en este caso el SDA y SCL corresponden a los pines A4 y A5 respectivamente) o para el Arduino Mega (cuyos pines ya vienen incorporados en un apartado de las entradas y salidas digitales)
