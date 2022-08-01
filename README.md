# Autenticão-RFID-e-ESP32NodeMCU

## Em fase de Desenvolvimento
<p>

## Resumo
Algoritimo desenvolvido para a gravação e obtenção de dados apartir de TEGs do tipo RFID 13,56Mhz e visando tando a obtenção quanto a publicação destes dados em brokers sejam publicos ou privados.
## DESCRIÇÃO
Foi utilizado como ferramente par auxiliar no desenvolvimento o [Arduino IDE 1.8.19](https://www.arduino.cc/en/software) para a escrita do codigo, tambem como o broker publico [HiveMQ](broker.hivemq.com) permitido o uso apartir do protocolo [MQTT](https://mqtt.org/).

 ### Dispositivos utilizados
  <br> 1 - Modulo Leitor RFID-Mfrc522
  <br> 1 - Catão(TAG) RFID 13,56Mhz
  <br> 1 - ESP32S NodeMcu ESP-12

### Bibliotecas Utilizadas
[WiFi.h](https://github.com/arduino-libraries/WiFi)
[PubSubClient.h](https://github.com/knolleary/pubsubclient)