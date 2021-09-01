#include <BTLE.h>

#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";


void setup() {
Serial.begin(9600);


radio.begin();
radio.openReadingPipe(0, address);   //Configurar o endereço que vai receber os dados
radio.setPALevel(RF24_PA_MIN);       //MIN ou MAX dependendo da distância entre o transmitter e o receiver
radio.startListening();              //Seta o módulo como receiver
}
void loop(){
  if (radio.available()){   //procura por dado
    char text[32] = "";     //salvar dados
    radio.read(&text, sizeof(text));
    radio.read(&count, sizeof(count));

    if(sensorValue>averageValue + 4){
      digitalWrite(6, HIGH);
      Serial.println(text);
      Serial.println(count);
    }else{
      digitalWrite(6, LOW);
    }
  }
  delay(1000);
}
