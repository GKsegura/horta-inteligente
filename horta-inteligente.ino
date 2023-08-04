#include <LiquidCrystal.h>
#define tempCard A1
#define buzzerCard 0

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int pinoValvula = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// variáveis do programa
const int pinoSensor = A0;
const int limiarSeco = 74;
const int tempoRega = 5; // Tempo de rega em segundos
int umidadeSolo = 0;

void setup()
{
  digitalWrite(pinoValvula, HIGH);
  lcd.begin(16, 2);
  pinMode(tempCard, INPUT);
  pinMode(buzzerCard, OUTPUT);
}

void loop()
{
  // Mede a umidade a cada segundo. Faz isso durante uma hora (3600 segundos).
  for (int i = 0; i < 5; i++)
  {
    // Posiciona o cursor do LCD na coluna 0 linha 1
    // (Obs: linha 1 é a segunda linha, a contagem começa em 0
    lcd.setCursor(0, 1);
    // Exibe a mensagem no Display LCD:
    lcd.print("Umidade: ");
    // Faz a leitura do sensor de umidade do solo
    umidadeSolo = analogRead(pinoSensor);
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
    umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);
    // Exibe a mensagem no Display LCD:
    lcd.print(umidadeSolo);
    lcd.print("%");
    // Espera um segundo
    delay(1000);
  }

  if (umidadeSolo < limiarSeco)
  {
    // Posiciona o cursor do LCD na coluna 0 linha 1
    // (Obs: linha 1 é a segunda linha, a contagem começa em 0
    lcd.setCursor(0, 1);
    // Exibe a mensagem no Display LCD:
    lcd.print("    Regando     ");
    // Liga a válvula
    digitalWrite(pinoValvula, LOW);
    // Espera o tempo estipulado
    delay(tempoRega * 1000);
    digitalWrite(pinoValvula, HIGH);
  }
  else
  {
    // Posiciona o cursor do LCD na coluna 0 linha 1
    // (Obs: linha 1 é a segunda linha, a contagem começa em 0
    lcd.setCursor(0, 1);
    // Exibe a mensagem no Display LCD:
    lcd.print("Solo Encharcado");
    // Espera o tempo estipulado
    delay(3000);
  }

  float temp = float(analogRead(tempCard));
  float temp2 = (temp * 5) / 1023;
  float tempNova = temp2 / 0.01;

  if (tempNova >= 40)
  {
    digitalWrite(buzzerCard, HIGH);
  }
  else
  {
    digitalWrite(buzzerCard, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempNova);
  lcd.write(0xDF);
  lcd.print("C");
}
