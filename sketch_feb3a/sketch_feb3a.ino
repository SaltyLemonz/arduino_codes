//biblioteca responsável pela comunicação com o Cartão SD
#include <SD.h>
//biblioteca responsável pela comunicação com o sensor DHT22
#include <DHT.h>
 
// pino de dados do DHT será ligado no D6 do esp
#define DHTPIN D2     
// tipo do sensor
#define DHTTYPE DHT22   
 
// construtor do objeto para comunicar com o sensor
DHT dht(DHTPIN, DHTTYPE);
  
//pino ligado ao CS do módulo SD Card
#define CS  D8

void setup()
{
  Serial.begin(9600);
  Serial.print("Inicializando o cartão SD...");
 
  //inicializa o objeto para comunicarmos com o sensor DHT
  dht.begin();
   
  // verifica se o cartão SD está presente e se pode ser inicializado
  if (!SD.begin(CS)) {
    Serial.println("Falha, verifique se o cartão está presente.");
    //programa encerrrado
    return;
  }
   
  //se chegou aqui é porque o cartão foi inicializado corretamente  
  Serial.println("Cartão inicializado.");
 
}

void loop(){
  //faz a leitura da umidade
  float umidade = dht.readHumidity();
  Serial.print("Umidade: ");
  Serial.println(umidade);
  //faz a leitura da temperatura
  float temperatura = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
 
  File dataFile = SD.open("LOG.txt", FILE_WRITE);
  // se o arquivo foi aberto corretamente, escreve os dados nele
  if (dataFile) {
    Serial.println("O arquivo foi aberto com sucesso.");
      //formatação no arquivo: linha a linha >> UMIDADE | TEMPERATURA
      dataFile.print(umidade);
      dataFile.print(" | ");
      dataFile.println(temperatura);
 
      //fecha o arquivo após usá-lo
      dataFile.close();
  }
  // se o arquivo não pôde ser aberto os dados não serão gravados.
  else {
    Serial.println("Falha ao abrir o arquivo LOG.txt");
  }
 
  //intervalo de espera para uma nova leitura dos dados.
  delay(2000);
 
}