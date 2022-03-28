
// ***************************************************************************************************
// *  CURSO IOT COM LORAWAN - INOVANEX -  INOVANEX.COM.BR                                            *
// *  EXERCÍCIO 1A - AÇÃO DIRETA DO BOTÃO NO LED                                                     *
// *                                                                                                 *
// *  Desenvolvido por David Souza - david.souza@inovanex.com.br                                     *
// *  Versão 1.0 - Março/2021                                                                        *
// *                                                                                                 *
// *  Template padrão para ESP32 como módulo IoT Devkit LoRaWAN / Robocore                           *
// *  Escolha a placa: ESP32 Dev Module                                                              *
// *                                                                                                 *
// ***************************************************************************************************

// ***************************************************************************************************
// *  Checagem do modelo de processador. Válido somente para ESP32                                   *  
// ***************************************************************************************************
#if !defined(ARDUINO_ESP32_DEV) // ESP32
  #error Este exercicio é valido somente para ESP32
#endif
 
// ***************************************************************************************************
// *  Arquivos de include básicos                                                                    *  
// ***************************************************************************************************

// ***************************************************************************************************
// *  Definições auxiliares                                                                          *
// ***************************************************************************************************
#define OFF           0
#define ON            1

// ***************************************************************************************************
// *  Definições de Operação                                                                         *
// ***************************************************************************************************
#define DEBUG         ON        // Imprime mensagens de Debug (OFF não imprime)

// ***************************************************************************************************
// *  Definição da pinagem                                                                           *
// ***************************************************************************************************
// Digitais
#define BT            4         // Pino ligado ao botão
#define LED           2         // Pino ligado ao LED

// Analógicas


// ***************************************************************************************************
// *  Variáveis globais                                                                              *
// ***************************************************************************************************



// ***************************************************************************************************
// *  Função: setup (obrigatória)                                                                    *
// *  Descrição: Função de inicialização do sistema (após energização ou reset)                      *
// *  Argumentos: Nenhum                                                                             *
// *  Retorno: Nenhum                                                                                *
// ***************************************************************************************************
void setup(void)
{
  #if (DEBUG==ON)
    // Configura porta serial para DEBUG
    Serial.begin(115200);
    Serial.println(F("=== Iniciando Setup do sistema ==="));
    Serial.println(F("== EXERCÍCIO 1A  =="));

  #endif

  // Configuração das portas utilizadas
  pinMode(LED, OUTPUT);                  //Habilita porta como saída
  pinMode(BT, INPUT);                    //Habilita porta como entrada

  #if (DEBUG==ON)
    Serial.println(F("=== Entrando em Operação Normal ==="));
  #endif
}

// ***************************************************************************************************
// *  Função: loop (obrigatória)                                                                     *
// *  Descrição: Função de looping principal                                                         *
// *  Argumentos: Nenhum                                                                             *
// *  Retorno: Nenhum                                                                                *
// ***************************************************************************************************
void loop()
{
  if (digitalRead(BT) == 0){        // Leitura do botão (0=pressionado)
    Serial.println(F("Botão pressionado"));
    digitalWrite(LED, HIGH);        // LED=1 (Aceso)
  } else {
    Serial.println(F("Botão liberado"));
    digitalWrite(LED, LOW);         // LED=0 (Apagado)
  }
}
