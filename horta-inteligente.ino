// bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// defines
#define tempCard A1
#define buzzerCard 0
#define endereco 0x27 // Endereços comuns: 0x27, 0x3F
#define colunas 16
#define linhas 2

// variáveis do programa
const int pinoValvula = 1;
const int pinoSensor = A0;
const int limiarSeco = 50;
const int limiarEncharcado = 70;
const int tempoRega = 2;
int umidadeSolo = 0;

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup()
{
  pinMode(pinoValvula, OUTPUT);
  digitalWrite(pinoValvula, LOW);
  pinMode(tempCard, INPUT);
  pinMode(buzzerCard, OUTPUT);
  lcd.init();      // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear();     // LIMPA O DISPLAY
}

void loop()
{
  setTela();

  float temp = float(analogRead(tempCard));
  float temp2 = (temp * 5) / 1023;
  float tempNova = temp2 / 0.01;

  // Mede a umidade a cada segundo. Faz isso durante uma hora (3600 segundos).
  for (int i = 0; i < 60; i++)
  {
    setTela();

    lcd.print("Temp:");
    lcd.print(tempNova);
    lcd.write(0xDF);
    lcd.print("C");

    umidadeSolo = analogRead(pinoSensor);
    umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);

    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(umidadeSolo);
    lcd.print("%");

    Serial.print("Umidade: ");
    int tempoRestante = 60 - i;

    lcd.print(" ");
    lcd.print(tempoRestante);
    lcd.print("s");

    delay(1000);
  }

  if (umidadeSolo < limiarSeco)
  {
    setTela();
    lcd.print("Solo seco");
    lcd.setCursor(0, 1);
    delay(10000);
    rega();
  }
  else if (umidadeSolo >= limiarSeco && umidadeSolo < limiarEncharcado)
  {
    setTela();
    lcd.print("Solo umido");
    delay(10000);
  }
  else if (umidadeSolo >= limiarEncharcado)
  {
    setTela();
    lcd.print("Solo encharcado");
    delay(10000);
  }
}

void setTela()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

void rega()
{
  // Exibe a mensagem no Display LCD:
  lcd.print("Regando");
  // Liga a válvula
  digitalWrite(pinoValvula, HIGH);
  // Espera o tempo estipulado
  delay(tempoRega * 1000);
  // desliga a válvula
  digitalWrite(pinoValvula, LOW);
}