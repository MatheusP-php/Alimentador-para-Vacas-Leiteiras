#include <SoftwareSerial.h>

SoftwareSerial bluetooth(3,2);
String command = "";
char b1;

int rele = 9; // rele no pino 8
int rele2 = 10; // rele no pino 8

int conta;
int voltas;
int botao = 7; // botão no pino 7
int funcaoa = 1; // valor instantaneo enviado pelo botão
int funcaob = 1; // valor guardado
int estado=0; // guarda o valor 0 ou 1 (HIGH ou LOW)

bool s_high = 0;
unsigned long counter = 0;
float peso;

void setup(){
 Serial.begin(9600);
 Serial.println(" inciando ");
 bluetooth.begin(9600);
 pinMode(rele,OUTPUT); //Define o rele como saida
 pinMode(rele2,OUTPUT);
 digitalWrite(rele,HIGH);
 digitalWrite(rele2,HIGH);
 pinMode(botao,INPUT); //Define o botão como entrada
 pinMode(6,INPUT);
}
void loop(){
  if (bluetooth.available()> 0){
      b1 = bluetooth.read();
      Serial.print(b1);
      command += b1;
      if(b1 == '\n'){
          Serial.print(command);
          command.trim();
          peso = command.toInt();
          Serial.println(peso);
          command =  "";
      }
  }

  if(digitalRead(6)) s_high = 1;
  funcaoa=digitalRead(botao); 
   if ((funcaoa == HIGH) && (funcaob == LOW) && (peso > 0) ) {
   estado = 1 - estado;
   }
   funcaob=funcaoa;
   if (estado == 1) {
   digitalWrite(rele, LOW); 
   if(!digitalRead(6) && s_high)
          {
            s_high = 0;
            counter += 1;
            Serial.print("volta:");
            Serial.println(counter);
            Serial.print("peso:");
            Serial.println(peso);
            if(counter == peso)
            {
              counter = 0;
              estado = !estado;  
              digitalWrite(rele, HIGH);
              delay(1000);
              digitalWrite(rele2, LOW);
              delay(13000); 
              }
           }               
   } 
            else {
               digitalWrite(rele, HIGH); 
               digitalWrite(rele2, HIGH);
              }
}
