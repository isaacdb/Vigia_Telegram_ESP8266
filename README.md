
# Esp8266
<p align="center">
<img width="60%" alt="LOGO" title="#LOGO" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/vigia.png">
</p>

<p align="center">Projeto livre utilizando ESP8266 para aula de IOT2</p>

<p align="center">
 <a href="#-sobre-o-projeto">Sobre o Projeto</a> •
 <a href="#funcionalidades">Funcionalidades</a> • 
 <a href="#materiais-utilizados">Materiais Utilizados</a> • 
 <a href="#tecnologias">Tecnologias</a> • 
 <a href="#como-executar">Como Executar</a> • 
 <a href="consideracoes">Considerações</a> • 
 <a href="#autor">Autor</a>
</p>

---
## 💻 Sobre o projeto
<p>Esse projeto entra no tema de IOT e SmartHome, tornaremos nosso ambiante particular mais seguro e confortável,</p>
<p>vamos utilizar a placa WemosD1 para criar um assistente virtual que cuidara de nossa casa, ele monitorará nosso ambiente</p>
<p> e casa houver alguma movimentação,vamos receber em nosso smartphone uma mensagem de alerta.</p>
<p>O ideal para o projeto seria utilizar um sensor de movimentação/presença, mas como não tenho um a disposição no momento, será utilizado um push button para replicar o sinal digital do sensor de presença, e também como bônus, um sensor de distância, que terá uma peculiaridade no modo de ser lido, já que o sinal será análogico e não digital como o push button.</p>

---
## Materiais Utilizados

- Placa Wemos D1
- Smartphone
- Telegram APP
- Sensor Ultrassônico HC-SR04
- PushButton
- Jumpers

---

---
## Funcionalidades

- [x] Detecção de movimento
- [x] Mensagem de alerta via app

---
## Tecnologias

As seguintes tecnologias foram usadas na construção do projeto:

- [C++]
- [Arduino IDE]

---
## Como executar
<h4>Pré requisitos</h4>
<p>Com a IDE do <a href="https://www.arduino.cc/en/software">Arduino</a> devidamente instalada, será nescessário também a instalação de algumas bibliotecas para o projeto, <a href="https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/">ESP8266 p/ Arduino</a>, <a href="https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/archive/master.zip">Biblioteca Telegram</a> (adicione como biblioteca local), <a href="https://github.com/bblanchon/ArduinoJson">ArduinoJson</a> (busque pelo gerenciador de bibliotecas)</p>

<p>Faça o download do código via <a href="https://github.com/isaacdb/Vigia_Telegram_ESP8266">GitHub/isaacdb</a></p>

<p>Faça o download do APP <a href="https://play.google.com/store/apps/details?id=org.telegram.messenger&hl=pt_BR&gl=US">Telegram</a> em seu smartphone.</p>

<h4>Circuito</h4>
<p>Monte o protótipo seguindo o circuito a seguir.</p>
<p>Confira se as pinagens estão correspondentes as do código, e cheque se todos os jumpers estão bem conectados.</p>
<img width="80%" alt="TinkerCad" title="#TinkerCad" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/circuitoVigia.PNG">
<img width="80%" alt="CircuitoReal" title="#CircuitoReal" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/Circuitofisico.jpeg">

<h4>Configurações</h4>
<p>Em seu Telegram procure por BotFather, será com este bot que vamos criar nosso próprio bot vigia. Inicie com "/start", em seguida "/newbot", defina um Nome e um Username para seu bot, guarde o username, e o código TOKEN que você receberá, vai ser nescessário para a aplicação ter controle do bot a seguir.</p>
<p>Será preciso ter em mãos o ID da sua conta no Telegram para o bot enviar os alertas. No Telegram pesquise pot IDBot, insira "/getid", você receberá a resposta com seu ID</p>
<p>Abra a IDE com o código do projeto, e define as variáveis de conexão de Wifi</p>
 <img width="80%" alt="wifi" title="#wifi" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/configwifi.PNG"> 
<p>Defina a conexão com o bot, e o seu ID do Telegram para receber os alertas</p>
 <img width="80%" alt="configbot" title="#configbot" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/configbot.PNG"> 
 
 <h4>Código</h4>
 <p>Para a leitura do sinal digital (pushButton ou sensor de movimentação), podemos usar uma ferramenta muito útil e eficiente, que seria a interrupção por sinal digital, o programa inicia a interrupção, definimos um pino de orientação, e uma função para executar quanto este mudar de estado, logo não desperdiçamos processamento verificando constantemente o pino sem nescessidades.</p>
 <p>Inicia interrupção digital</p>
 <img width="80%" alt="wifi" title="#wifi" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/intterruptDigital.PNG"> 
<p>Método chamado quando houver mudança de estado no pino, mais específicamente quando o pino for setado para LOW, definimos isso no parametro RISING</p>
 <img width="80%" alt="wifi" title="#wifi" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/MetodoInterruptDigital.PNG"> 

 <p>Já para utilizar o sensor de distância vamos utilizar uma abordagem diferente, por ser um sensor de sinal análogico, não temos como utilizar a interrupção por mudança de estado, então vamos utilizar uma interrupção por tempo, um TIMER, não terá um desempenho tão bom quanto a interrupção digital porque estará sempre execução, mas com um TIMER podemos garantir que o sensor será sempre monitorado mesmo enquanto a aplicação estiver em alguma outra funcionalidade, e podemos definir um tempo específico entre as leituras, para não pesar tanto no processamento.</p>
 <p>Inicia o Timer</p>
 <img width="80%" alt="wifi" title="#wifi" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/interruptTimer.PNG"> 
<p>Método de configuração do timer, e método que será chamado sempre que houver batido o tempo de cada ciclo.</p>
 <img width="80%" alt="wifi" title="#wifi" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/MetodoInterruptTimer.PNG"> 
  
<h4>Execução</h4>
<p>Abra seu App Telegram, procure pelo Username do bot criado, e inicie o via com /start</p>
<p>A partir desse momento, você possui um vigia em tempo integral do seu ambiante <s>desde que possua internet claro</s>.</p>
<img width="40%" alt="Conectado" title="#Conectado" src="https://github.com/isaacdb/Vigia_Telegram_ESP8266/blob/main/ScreenShots/bot.jpeg"> 

 <a href="https://youtu.be/nb96Aw5H10o">Video</a>

## Considerações
<p>Com esse pequeno protótipo em mãos, fica fácil imaginar várias maneiras de expandir esse projeto e criar outras funcionalidades para compor sua SmartHome, podemos implementar um sensor por cômodo, definir alertas distintos para cada sensor, adicionar sensores distintos, criar lógicas para o bot também receber mensagens e tomar algumas ações que facilitem nossa vida, as opções são inúmeras!</p>

---
### Autor
Isaac Debiasi
