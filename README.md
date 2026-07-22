# Horta Inteligente

Projeto de automação com Arduino para monitoramento e irrigação automática de uma horta.

## Funcionalidades

- Leitura em tempo real da **umidade do solo** via sensor analógico
- Leitura de **temperatura**
- Exibição dos dados em **display LCD** (umidade, temperatura e contagem regressiva da medição)
- **Irrigação automática**: aciona uma válvula/bomba d'água quando o solo está seco, e para automaticamente após o tempo de rega configurado
- Classificação do solo em três estados: seco, úmido ou encharcado

## Como funciona

O sensor de umidade é lido a cada segundo, ao longo de um ciclo de leitura. Ao final do ciclo, o sistema decide se precisa regar com base em limiares configuráveis (`limiarSeco` e `limiarEncharcado`). Se o solo estiver seco, a válvula é acionada por um tempo determinado (`tempoRega`) e depois desligada automaticamente.

## Hardware utilizado

- Arduino (Uno ou compatível)
- Sensor de umidade do solo (entrada analógica)
- Sensor de temperatura (entrada analógica)
- Display LCD 16x2 com módulo I2C
- Válvula solenoide / relé para acionamento da irrigação

## Tecnologias

- C++ (Arduino/.ino)
- Biblioteca `LiquidCrystal_I2C` para controle do display
