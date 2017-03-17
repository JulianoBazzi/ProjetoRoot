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

void setup()
{
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
void sensoresq() {
  digitalWrite(gatilho,HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho, LOW);
  tempo=pulseIn(echo, HIGH);
  distancia_esq = tempo/29.4/2;     //ate aqui calcula a distancia no sensor da direita
  Serial.print("Distancia Esqueda: ");
  Serial.println(distancia_esq);

}
void sensordir(){
  digitalWrite(gatilho1,HIGH);
  delayMicroseconds(10);
  digitalWrite(gatilho1, LOW);
  tempo1=pulseIn(echo1, HIGH);
  distancia_dir = tempo1/29.4/2;     // ate aqui calcula a distancia no sensor da esquerda
  Serial.print("Distancia Direita: ");
  Serial.println(distancia_dir);
}


void reto(){
  myservo.write(40);  //40 graus vai reto
}

void parar(){
  motor1.run(RELEASE);  //para o motor
}  

void frente(){
  motor1.run(FORWARD); //aciona para frente
  Serial.print("Frente Velocidade Atual:");
  Serial.println(veloc);
}

void traz(){
  motor1.run(BACKWARD);  //aciona para traz
  Serial.print("Marcha Re Velocidade Atual:");
  Serial.println(veloc);
}


void viraesq() {
  myservo.write(15);  //Move o servo para o angulo de 15 graus
  Serial.println("Virando Esquerda... ");   
  led1();
}

void viradir() {
  myservo.write(70);  //Move o servo para o angulo de 70 graus
  Serial.println("Virando Direita... ");
  led2();
}


void led1() {
  digitalWrite(34,HIGH);
  delay(100);
  digitalWrite(34,LOW);
  delay(100);
} 

void led2() {
  digitalWrite(35,HIGH);
  delay(500);
  digitalWrite(35,LOW);
  delay(500);
} 


void loop()
{
  reto();
  frente();
  distesq_ant = distancia_esq;
  distdir_ant = distancia_dir;
  sensoresq(); // pega a distancia sensor esquerda
  sensordir(); // pega a distancia sensor direita
  if (distancia_esq < 60 && distancia_dir < 60) {
//    while (distancia_esq < 50 && distancia_dir < 50){
      parar();
      delay(200);
      Serial.println("Entrou no While!");
      if (distancia_esq < 20 || distancia_dir < 20){
        Serial.println("distancia_esq < 20 || distancia_dir < 20");        
        parar();   
        led2();
        led1();
        if (distancia_esq > distancia_dir) { 
          viradir();
          traz();
          delay(1000);
        }
        else if (distancia_esq < distancia_dir) {
          viraesq();
          traz();
          delay(1000);          
        }
      }
      else if (distancia_esq > distancia_dir) { 
        viraesq();
        Serial.println("distancia_esq > distancia_dir");
        frente();
        delay(1000);
//        sensoresq();
//        sensordir();
      }
      else if (distancia_esq < distancia_dir) {
        Serial.println("distancia_dir > distancia_esq");
        viradir();
        frente();
        delay(1000);
//        sensoresq();
//        sensordir();
      }
//    }
  }
}




