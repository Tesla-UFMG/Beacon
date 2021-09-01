#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9); // CE, CSN         

const byte address[6] = "00001";     //Endereço para onde vai ser enviado o dado. Deve ser o mesmo no receiver.
int sensorPin = 11;    
//int ledPin = 11;      
int sensorValue = 0;  
float averageValue = 0;
int count=1;

int ne555 = 10;
unsigned long duration;
unsigned long duration1;
float ciclo;

int x=0;

void setup() {
Serial.begin(9600);

pinMode(10, INPUT);
//pinMode(ledPin, OUTPUT);

digitalWrite(sensorPin, HIGH);
radio.begin();                  //Começar a comunicação wireless
radio.openWritingPipe(address); //Configurar o endereço que vai receber os dados
radio.setPALevel(RF24_PA_MIN);  //MIN ou MAX depende da distância entre o transmitter e o receiver
radio.stopListening();          //Seta esse módulo como o transmitter
}
void loop(){
  sensorValue = analogRead(sensorPin);
  
  if(millis()<2000){
    averageValue += ((float)sensorValue);
    
    //Serial.println(x);
    x++;
    //Serial.println(count);
    count++;
    //Serial.println(sensorValue);
    //Serial.println(averageValue);
    digitalWrite(11, HIGH); 
    
    delay(500);
    
  } // configurar pressão padrão para acionamento do sensor a partir de 2 segundos que o código está funcionando
  else{
    if(sensorValue>=(averageValue/x)){
      count++;
      //Serial.println(averageValue/x);
      //Serial.println("volta numero: ");
      //Serial.println(count);
 
      const char text[] = "Volta completada";
    
      digitalWrite(11, HIGH);
      radio.write(&text, sizeof(text));
      radio.write(&count, sizeof(count));
    
      /*digitalWrite(10, HIGH);
      Serial.println("Ciclo: ");
      Serial.println(ciclo);
      Serial.println();
     */
      delay(2000);
    }else{
      digitalWrite(11, LOW); 
      //averageValue +=((float)sensorValue - averageValue)/x;
      Serial.println("acabou");
      delay(5000);
      }
    }
  }
