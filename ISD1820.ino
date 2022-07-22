#define saidaSensor 5
#define led 13
#define ativaPlayL 3
#define ativaREC 4
#define tempoReproducao 10000

int leituraSensor = 0;  
   
void setup()  
{  
  pinMode(saidaSensor,INPUT);
  pinMode(ativaPlayL,OUTPUT);
  pinMode(ativaREC,OUTPUT);
  pinMode(led,OUTPUT);//Pino para ativar o led
  pinMode(saidaSensor,INPUT);//Pino ler o sinal no coletor do fototransistor  
  Serial.begin(9600);//inicializa a porta serial com baud rate de 9600
  MainMenu();
}  
   
void loop()  
{ 
  leituraSensor = digitalRead(saidaSensor); 
  
  if (leituraSensor == 0 ) 
  {  
    digitalWrite(led,HIGH);
    digitalWrite(ativaPlayL,HIGH);
    delay(tempoReproducao);
    digitalWrite(ativaPlayL,LOW);
  }
  else 
    digitalWrite(led,LOW);
  
    
  delay(1000);
} 

void MainMenu()
{
  
  int controlLoop = true;
  char byteRead;
  Serial.println("Digita a para gravar ou b para rodar a reproducao");
  
  while(controlLoop)
  {
   
      if (Serial.available())  //verifica se tem dados diponível para leitura
      {
        byteRead = Serial.read(); //le bytwe mais recente no buffer da serial
        Serial.write(byteRead);   //reenvia para o computador o dado recebido
      }
      
      if( byteRead == 'a') 
      { 
        Serial.println("Gravação começa no 3");
        contador(3);
        digitalWrite(ativaREC,HIGH);
        Serial.println("Gravando por 10 segundos!");    
        contador(10);      
        digitalWrite(ativaREC,LOW);
        Serial.print("Pronto!");
        Serial.println("Digite b para comecar a reproducao");
        byteRead = ' ';
      }
      
      if(byteRead == 'b' )
      { 
        controlLoop = false;
        byteRead = ' ';
      }
  }
 }

void contador(int quantasVezes)
{
  for(int i=0; i<quantasVezes; i++)
  {
    Serial.print(i+1);
    Serial.println("...");
    delay(1000);
  }
}