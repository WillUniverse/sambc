#define USE_ARDUINO_INTERRUPTS true    //Inicializa as interrupcoes de baixo nivel para melhor precisao dos BPM
#include <SoftwareSerial.h>
#include <PulseSensorPlayground.h>  // Includes the PulseSensorPlayground Library.
//Porta do Arduino onde o pino TX do Módulo GSM esta conectado
#define TX_PIN 10
 
//Porta do Arduino onde o pino RX do Módulo GSM esta conectado
#define RX_PIN 11
 
//Cria comunicacao serial via software nas portas digitais definidas acima
SoftwareSerial mySerial(TX_PIN, RX_PIN);
PulseSensorPlayground pulseSensor; 
const int PulseWire = 0;       // Conector de detecção do sinal analógico do PulseSensor   ligado ao pino analogico 0
const int LED13 = 13;          // Define o led 13, o da placa.
int Threshold = 550;           // Determina qual sinal conta com uma batida e qual ignorar -- aumentar a sensibilidade do sensor
bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";
bool callStatus = false;
void enviaSMS(String telefone);
void fazLigacao(String telefone);
void configuraGSM();
int cont = 4; 

void setup() {
  Serial.begin(9600);          // Inicializa o monitor serial

  // Configura o objeto pulseSensor de acordo com as variaveis criadas 
  pulseSensor.analogInput(PulseWire);   // recebe os valores analogicos do sensor
  pulseSensor.blinkOnPulse(LED13);       // Led da placa pisca de acordo com as batidas do coracao
  pulseSensor.setThreshold(Threshold);   

  // Verifica se o objeto foi criado e o sinal esta sendo passado pelo sensor 
   if (pulseSensor.begin()) {
    Serial.println("Objeto Criado!");  //Avisa que o objeto criado.  
  }
  mySerial.begin(9600); 

  Serial.println("Sketch Iniciado!");
  configuraGSM();
}

void loop() {
 int myBPM = pulseSensor.getBeatsPerMinute();  // Chama a funcao para retorna os valores dos batimentos e armazena-los em 
                                               // "myBPM" mantem o valor de BPM atual.
                                               
if (pulseSensor.sawStartOfBeat()) {            // Testa constantemente se os batimentos estao ocorrendo. 
    Serial.println("♥  Batimentos Acontecendo! "); // Se verdadeiro, printa esta mensagem.
    Serial.print("BPM: ");                        // Imprimi na tela  "BPM: " 
    Serial.println(myBPM);                        // Imprimi os valores dos batimentos. 
    // Teste lógico que só enviara mensagens quando tiverem valores incorretos de forma constante 
    if(myBPM < 50 || myBPM > 180){  
       cont--;
       Serial.println(cont); 
       if(cont < 2){
          enviaSMS("91998353989");
          cont = 4;    
    } 
     delay(2000);
  }
}


 delay(20); 
 
}



/*
Funções que definem enviarSMS, fazerLigação e configuraGSM.
*/
void enviaSMS(String telefone) {
      mySerial.print("AT+CMGF=1\r");//modo texto
      Serial.println("configurando envio de SMS");
      mySerial.print("AT+CMGS=\""+ telefone+"\"\n");
      mySerial.print("O Paciente em estado grave\r");
      mySerial.print("%");
      mySerial.write(0x1A);
      Serial.println("SMS enviado com sucesso");
      Serial.println(" "); 
}

void fazLigacao(String telefone) {
     mySerial.println("ATH0\n");
     mySerial.print((char)26); 
     mySerial.println("ATD " + telefone + ";\n");
     mySerial.print((char)26); 
}


void configuraGSM() {
     mySerial.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}
