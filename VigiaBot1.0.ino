//Incuindo as bibliotecas nescessarias
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Ultrasonic.h>
os_timer_t mTimer;

//Tempo entre as interrupções por tempo
const int interruptTime = 1000;//millisegundos

//Constantes com dados de conexão do wifi
const char* ssid = "Debiasi";
const char* password = "preta123";

// Inicializa Telegram BOT
#define BOTtoken "1470175447:AAFMTVKv1Fe5lWobulahDMnB5SjNXLhsvps"  //seu Bot Token - Pegue-o no BotFather no Telegram

//ID de endereço que o bot ira encaminhar as mensagens
//Para receber as mensagens, deve procurar o bot pelo UserName e inicializalo no Telegram
#define CHAT_ID "1128822704"

//Conexão com wifi e Telegram
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//Declaração dos pinos
const int sensorMovimento = 2; // PIR Motion Sensor
const int trigger = 16;
const int echo = 5;
Ultrasonic ultrasonic(trigger, echo);

//Declaracao de distancia de ascionamento do "alarme"
const int distanciaTolerada = 30; //cm

//Variaveis de controle para as interrupções
bool timeout = false;
bool movimentoDetecdado = false;
bool verificarSensor = false;

//Funções de uso da interrupção por tempo
void tCallback(void *tCall) {
  timeout = true;
}
void usrInit(void) {
  os_timer_setfn(&mTimer, tCallback, NULL);
  os_timer_arm(&mTimer, interruptTime, true);
}

//Função de uso da interrupção por estado de pinoDigital
void ICACHE_RAM_ATTR detectouMovimento()
{
  movimentoDetecdado = true;
}

void setup()
{
  usrInit(); //Inicia interrupção por tempo

  Serial.begin(9600); //Comunicação com o terminal da IDE
  client.setInsecure();//Função de segurança do wifi

  pinMode(sensorMovimento, INPUT_PULLUP);

  //Inicia interrupção por estado de pinoDigital
  attachInterrupt(digitalPinToInterrupt(sensorMovimento), detectouMovimento, RISING);

  // Inicia processo de conexão com wifi
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Mensagem para o Telegram de confirmação do bot inicializado
  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop()
{
  //timeout sera verdadeiro sempre que houver a interrupção por tempo
  if (timeout) {
    leituraSensor();
    timeout = false;
  }
  //movimentoDetecdado sera verdadeiro sempre que a interrupção por estado de pinoDigital for ascionada
  if (movimentoDetecdado)
  {
   DetectouMovimento();
   motionDetected = false;
  }
}

void DetectouMovimento()
{
  bot.sendMessage(CHAT_ID, "Movimento detectado!!", "");
  Serial.println("Motion Detected");
}

void leituraSensor()
{
  if (ultrasonic.distanceRead() < distanciaTolerada)
  {
    bot.sendMessage(CHAT_ID, "Distancia ultrapassada!", "");
  }
  Serial.print("Distancia: ");
  Serial.print(ultrasonic.distanceRead());
  Serial.println("cm");
}
