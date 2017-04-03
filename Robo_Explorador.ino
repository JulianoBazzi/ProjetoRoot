#include <Servo.h>    //servo motor cx direcao 
#include <AFMotor.h>  //Ponte H controla os motores

AF_DCMotor motor1(1);  //porta que o motor esta usando

Servo myservo;  // cria objeto servo motor  
int gatilhoFrente1 = 24;        // trigg sensor ultrasonico da frente direita
int gatilhoFrente2 = 22;       // trigg sensor ultrasonico da frente esquerda
int gatilhoLateral1 = 31;        // trigg sensor ultrasonico da lateral direita
int gatilhoLateral2 = 33;       // trigg sensor ultrasonico da lateral esquerda
int valor = 0;
int echoFrente1 = 25;           // echo sensor ultrasonico da frente direita
int echoFrente2 = 23;          // echo sensor ultrasonico da frente esquerda
int echoLateral1 = 30;           // echo sensor ultrasonico da lateral direita
int echoLateral2 = 32;          // echo sensor ultrasonico da lateral esquerda
int count = 0;
int obstaculo = HIGH;    // sem obstaculos
float tempo;
float tempo1;
float tempo2;
float tempo3;
float distancia_frente_dir;     //vai receber a distancia no sensor da frente direita
float distancia_frente_esq;     //vai receber a distancia no sensor da frente esquerda
float distancia_lateral_dir;     //vai receber a distancia no sensor da lateral direita
float distancia_lateral_esq;     //vai receber a distancia no sensor da lateral esquerda
int val;
int veloc = 160; //define velocidade do motor
boolean bObstaculo;
static unsigned long delayTempo; 
static unsigned long delayPisca; 
static unsigned long delayPisca2; 
static unsigned long delayPisca3; 
static unsigned long delayPisca4;

void setup()
{
  myservo.attach(10);
  pinMode(gatilhoFrente1,OUTPUT);
  pinMode(gatilhoFrente2,OUTPUT);
  pinMode(gatilhoLateral1,OUTPUT);
  pinMode(gatilhoLateral2,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(echoFrente1,INPUT);  
  pinMode(echoFrente2,INPUT);
  pinMode(echoLateral1,INPUT);  
  pinMode(echoLateral2,INPUT);
  pinMode(11,OUTPUT);
  delayMicroseconds(5);
  pinMode(21,OUTPUT);
  pinMode(20,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(17,OUTPUT);
  Serial.begin(9600); 
  motor1.setSpeed(veloc); //Define a Velocidade do Motor com a bateria nova deve ser 46

}
void sensorFrenteDireita() {
  digitalWrite(gatilhoFrente1,HIGH);
  delayMicroseconds(5);
  digitalWrite(gatilhoFrente1, LOW);
  tempo=pulseIn(echoFrente1, HIGH);
  distancia_frente_dir = tempo/29.4/2;     //ate aqui calcula a distancia no sensor da frente direita
  Serial.print("Distancia da Frente Direita: ");
  Serial.println(distancia_frente_dir);

}
void sensorFrenteEsquerda(){
  digitalWrite(gatilhoFrente2,HIGH);
  delayMicroseconds(5);
  digitalWrite(gatilhoFrente2, LOW);
  tempo1=pulseIn(echoFrente2, HIGH);
  distancia_frente_esq = tempo1/29.4/2;     // ate aqui calcula a distancia no sensor da frente esquerda
  Serial.print("Distancia da Frente Esquerda: ");
  Serial.println(distancia_frente_esq);
}

void sensorLateralDireita(){
  digitalWrite(gatilhoLateral1,HIGH);
  delayMicroseconds(5);
  digitalWrite(gatilhoLateral1, LOW);
  tempo2=pulseIn(echoLateral1, HIGH);
  distancia_lateral_dir = tempo2/29.4/2;     //ate aqui calcula a distancia no sensor da lateral direita
  Serial.print("Distancia da Lateral Direita: ");
  Serial.println(distancia_lateral_dir);
}

void sensorLateralEsquerda(){
  digitalWrite(gatilhoLateral2,HIGH);
  delayMicroseconds(5);
  digitalWrite(gatilhoLateral2, LOW);
  tempo3=pulseIn(echoLateral2, HIGH);
  distancia_lateral_esq = tempo3/29.4/2;     // ate aqui calcula a distancia no sensor da lateral esquerda
  Serial.print("Distancia da Lateral Esquerda: ");
  Serial.println(distancia_lateral_esq);  
}


void reto(){
  myservo.write(100);  //40 graus vai reto
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
  motor1.run(BACKWARD);  //aciona para traz
  Serial.println("Marcha Re Velocidade Atual: ");
  Serial.print(veloc);
}


void viraEsq() {
  myservo.write(40);  //Move o servo para o angulo de 15 graus
  Serial.println("Virando Esquerda... ");   
  led1();
}

void viraDir() {
  myservo.write(160);  //Move o servo para o angulo de 70 graus
  Serial.println("Virando Direita... ");
  led2();
}

void procuraObstaculo() {
   obstaculo = digitalRead(17);
   if (obstaculo == LOW) {
     Serial.println("Obstaculo encontrado!!!");
   }
}


void led1() { 
       digitalWrite(21,HIGH);
       delay(200);
       digitalWrite(21,LOW);
       delay(200);
 } 

void led2() {
       digitalWrite(20,HIGH);
       delay(200);
       digitalWrite(20,LOW);
       delay(200);
} 

void led3() {
       digitalWrite(19,HIGH);
       delay(200);
       digitalWrite(19,LOW);
       delay(200);
} 

void led4() {
       digitalWrite(18,HIGH);
       delay(200);
       digitalWrite(18,LOW);
       delay(200);
} 


void loop(){
  procuraObstaculo(); //procura por um obstaculo
  sensorFrenteEsquerda(); // pega a distancia sensor da frente esquerda
  sensorFrenteDireita(); // pega a distancia sensor da frete direita
  sensorLateralEsquerda(); // pega a distancia sensor da lateral esquerda
  sensorLateralDireita(); // pega a distancia sensor da lateral direita
  reto();
//  if (distancia_esq == 0) {
//      distancia_esq = 65;
//  }
//  if (distancia_dir == 0) {
//     distancia_dir = 65;
//  } 
   
  if (distancia_frente_esq < 45 || distancia_frente_dir < 45) {    //Aqui tambem tem que ser OR
    parar();
    if ((distancia_frente_esq < 5 || distancia_frente_dir < 5) && obstaculo == LOW){
      Serial.println("Distancia da Frente Esquerda ou Frente Direita e MENOR que 20cm");        
      led4();
      if (distancia_frente_esq > distancia_frente_dir) { 
            Serial.println("Re para a Direita");
            led1();
            viraDir();
            traz();
            delay(600);
            parar();
            viraEsq();
            frente();
            delay(25);
            
      }
      else { 
            Serial.println("Re para a Direita");
            led1();
            viraEsq();
            traz();
            delay(600);
            parar();
            viraDir();
            frente();
            delay(25);
      }
    }  
   
    else if (distancia_frente_esq > distancia_frente_dir && distancia_lateral_esq > distancia_lateral_dir) {
      Serial.println("Distancia da Frente Esquerda MAIOR que a da Frente Direita"); 
      Serial.println("Distancia da Lateral Esquerda MAIOR que a da Lateral Direita");
      led1();
      viraEsq();
      frente();
      delay(250);      
    }
    else if (distancia_frente_esq < distancia_frente_dir && distancia_lateral_esq < distancia_lateral_dir) {
      Serial.println("Distancia da Frente Direita MAIOR que a da Frente Esquerda");
      Serial.println("Distancia da Lateral Direita MAIOR que a da Lateral Esquerda");
      led2();
      viraDir();
      frente();
      delay(250);         
    }
    else if(distancia_lateral_esq <= 8) {
      viraEsq();
      traz();
      delay(300);
      parar();
      viraDir();
      frente();
      delay(25);
    } 
    else if ( distancia_lateral_dir <= 8) {
      viraDir();
      traz();
      delay(300);
      parar();
      viraEsq();
      frente();
      delay(25);  
    }
    else {
      led3();
      Serial.println("Tudo Limpo! Segue em frente!");   
      frente();
    }
  }
  else {
    led3();
    Serial.println("Tudo Limpo! Segue em frente!");   
    frente();
  }
}





