#include <Servo.h>    //servo motor cx direcao 
#include <AFMotor.h>  //Ponte H controla os motores

AF_DCMotor motor1(1);  //porta que o motor esta usando

Servo myservo;  // cria objeto servo motor  
int gatilho = 29;        // trigg sensor ultrasonico direita
int gatilho1 = 31;       // trigg sensor ultrasonico esquerda
int valor = 0;
int echo = 30;           // echo sensor ultrasonico direita
int echo1 = 32;          // echo sensor utrasonico esquerda
int count = 0;
float tempo;
float tempo1;
float distancia_dir;      //vai receber a distancia no sensor da direita
float distancia_esq;      //vai receber a distancia no sensor da esquerda
int val;
int veloc = 254; //define velocidade do motor
float distesq_ant = 0;
float distdir_ant = 0;

void setup(){
  myservo.attach(10);
  pinMode(gatilho1,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(11,OUTPUT);
  delayMicroseconds(10);
  pinMode(echo, INPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  Serial.begin(9600); 
  motor1.setSpeed(veloc); //Define a Velocidade do Motor com a bateria nova deve ser 46

}

void led1(){
  static unsigned long delayPisca; 
  if ( (millis() - delayPisca) < 500) {
       digitalWrite(21,HIGH);
  } else {  
       digitalWrite(21,LOW);
  }
  if ( (millis() - delayPisca) >= 1000){
    delayPisca = millis();
  }
} 

void led2(){
  static unsigned long delayPisca2; 
  if ( (millis() - delayPisca) < 500) {
       digitalWrite(20,HIGH);
  } else {  
       digitalWrite(20,LOW);
  }
  if ( (millis() - delayPisca2) >= 1000){
    delayPisca2 = millis();
  }
} 

void led3(){
  static unsigned long delayPisca3; 
  if ( (millis() - delayPisca) < 500) {
       digitalWrite(19,HIGH);
  } else {  
       digitalWrite(19,LOW);
  }
    if ( (millis() - delayPisca3) >= 1000){
    delayPisca3 = millis();
  }
} 

void led4(){
  static unsigned long delayPisca4; 
  if ( (millis() - delayPisca) < 500) {
       digitalWrite(18,HIGH);
  } else {  
       digitalWrite(18,LOW);
  }
    if ( (millis() - delayPisca4) >= 1000){
    delayPisca4 = millis();
  }
} 

void sensorEsq(){
  digitalWrite(gatilho,HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);
  tempo=pulseIn(echo, HIGH);
  distancia_esq = tempo/29.4/2;     //ate aqui calcula a distancia no sensor da direita
  Serial.print("Distancia Esquerda: ");
  Serial.println(distancia_esq);

}
void sensorDir(){
  digitalWrite(gatilho1,HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho1, LOW);
  tempo1=pulseIn(echo1, HIGH);
  distancia_dir = tempo1/29.4/2;     // ate aqui calcula a distancia no sensor da esquerda
  Serial.print("Distancia Direita: ");
  Serial.println(distancia_dir);
}


void reto(){
  myservo.write(35);  //40 graus vai reto
}

void parar(){
  motor1.run(RELEASE);  //para o motor
  Serial.println("Parando e Olhando!");
}  

void frente(){
  motor1.run(FORWARD); //aciona para frente
  Serial.print("Frente Velocidade Atual:");
  Serial.println(veloc);
}

void traz(){
  led4();
  if ((millis() - delayTempo) < 1500)
  {
     motor1.run(BACKWARD);  //aciona para traz
     Serial.print("Marcha Re Velocidade Atual:");
     Serial.println(veloc);
  } else {
    parar();
  }
}


void viraEsq(){
  myservo.write(15);  //Move o servo para o angulo de 15 graus
  Serial.println("Virando Esquerda... ");   
  led1();
}

void viraDir(){
  myservo.write(70);  //Move o servo para o angulo de 70 graus
  Serial.println("Virando Direita... ");
  led2();
}

void loop(){
  sensorEsq(); // pega a distancia sensor esquerda
  sensorDir(); // pega a distancia sensor direita
  reto();
  if (distancia_esq < 60 || distancia_dir < 60) {
    parar();
    if (distancia_esq < 20 || distancia_dir < 20){
      Serial.println("Distancia da Esquerda e Direita é MENOR que 20cm");        
      led1();
      led2();
      traz();
      delay(1500);
    }
    if (distancia_esq > distancia_dir) { 
      Serial.println("Distancia da Esquerda MAIOR que a da Direita");
      led1();
      viraEsq();
      frente();
      delay(1000);
    }
    if (distancia_esq < distancia_dir) {
      Serial.println("Distancia da Esquerda MENOR que a da Direita");
      led2();
      viraDir();
      frente();
      delay(1000);
    }
  } else {
    led3();
    Serial.println("Tudo Limpo! Segue em frente!");   
    frente();
  }
}