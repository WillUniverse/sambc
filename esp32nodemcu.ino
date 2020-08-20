
#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.




WiFiUDP udp;//Cria um objeto da classe UDP.
long Signal;//Variavel para ser enviada.
  char ssid[]="The One";
 char pass[]="vh100010";

void setup()
{
   pinMode(D4, OUTPUT);//Habilita o LED onboard como saida.
   digitalWrite(D4, 1);//Desliga o LED.
   digitalWrite(D7, 1);//Desliga o LED.
   connect();//Sub-rotina para conectar-se ao host.
   WiFi.mode(WIFI_STA);//Define o ESP8266 como Station.
   Serial.begin(9600); 
}
 
void loop()
{
   
      // Signal = analogRead(PulseSensorPurplePin);

      //Serial.println(Signal);
   send();//Sub-rotina para enviar os dados ao host.
    
   delay(5000);//Aguarda meio segundo.
}
 
void connect()//Sub-rotina para verificar a conexao com o host.
{
   if (WiFi.status() != WL_CONNECTED)//Caso nao esteja conectado ao host, ira se conectar.
   {
      WiFi.begin(ssid, pass);//Conecta à rede do host.
      delay(2000);//Espera ate que a conexao seja feita.
   }
}
 
void send()//Sub-rotina para enviar dados ao host.
{
   if (WiFi.status() == WL_CONNECTED)//Só ira enviar dados se estiver conectado.
   {
      
      Signal = analogRead(0);//le sinal da porta A0
      udp.beginPacket("192.168.43.182",5000);//Inicializa o pacote de transmissao ao IP e PORTA.
      udp.println(Signal);//Adiciona-se o valor ao pacote.
      udp.endPacket();//Finaliza o pacote e envia.
      Serial.println(Signal);
 
      digitalWrite(D4, 0);//-
      delay(5);//-
      digitalWrite(D4, 1);//Pisca o led rapidamente apos enviar.

      
   }
   else//Caso nao esteja com uma conexao estabelicida ao host, piscara lentamente.
   {
      digitalWrite(D4, 0);
      delay(250);
      digitalWrite(D4, 1);
   }
}
