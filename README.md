# Simulação de Cenários - Monitoramento e Controle IoT de Ambiente de Servidores
## Descrição do Projeto

Este projeto simula o monitoramento e controle de temperatura e umidade em um Data Center. Utilizando um sensor DHT11, os dados são enviados pela internet via protocolo MQTT. Uma aplicação em Node-RED recebe os dados e mostra tanto os valores instantâneos quanto o histórico de medições.  
Se os níveis de temperatura ou umidade ficarem elevados, um exaustor é acionado para circular o ar e reduzir a Temperatura umidade.

## Funcionalidades

- **Monitoramento de temperatura e umidade:**   Uso de um sensor DHT11 para medir as condições do ambiente.
- **Envio de dados via MQTT:**   Os dados são enviados pela internet usando o protocolo MQTT.
- **Visualização em Node-RED:**   Aplicação em Node-RED para visualizar valores instantâneos e históricos das medições.
- **Controle de exaustor:**   Acionamento de um exaustor caso os níveis de temperatura ou umidade excedam os limites definidos.
- **Comunicação visual e sonora:**   LEDs e buzzer para alertas visuais e sonoros.

## Requisitos do Projeto

 **Hardware:**
 - ESP32 conectado a uma rede Wi-Fi.
 - Sensor de temperatura e umidade DHT11.
 - LEDs (verde e vermelho) para comunicação visual.
 - Buzzer para comunicação sonora.
 - Ventilador de 12V.
 - Fonte de 12V para o ventilador.
 - Relé para acionamento do ventilador.

 
 **Software Ultilizados:**
  - MQTT broker.
  - Node-RED.
  - Arduino IDE.
