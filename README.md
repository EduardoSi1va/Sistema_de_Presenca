# Sistema de Presença
Projeto desenvolvido para a disciplina [SSC0180 - Eletrônica para Computação], ministrada pelo Professor Eduardo do Valle Simôes.

# Integrantes do Grupo 13:
| Aluno | Nº USP |
|---|---|
| André Campanholo Paschoalini | 14558061 |
| Eduardo Poltroniere da Silva | 16862892 |
| Felipe Fabiano das Chagas | 16811922 |
| Pedro Hamamoto da Palma | 16818280 |

# Explicação do Projeto
Deve ser desenvolvido o software e o hardware de um projeto à escolha do grupo, que utilize Arduino/ESP32.<br>
Optamos por desenvolver um sistema de controle de presença através de tags e sensores RFID. Seu funcionamento ocorre da seguinte maneira:<br>
À cada tag foi associado um nome e um número USP, de maneira que cada tag representa um aluno. Aproximá-la ao sensor ativa o sinal sonoro (buzzer) e exibe as informações do aluno em questão, conferindo presença a este. No software é possível consultar quais alunos estão presentes, de modo que sejam exibidos na tela seus nomes.

# Lista dos Componentes
| Componente | Quantidade | Preço |
|---|---|---|
| Arduino UNO R3 | 1 | R$ 42,90 |
| Módulo RFID RC522 | 1 | R$ 9,50 |
| Display SSD1306 OLED 128X64 | 1 | R$ 32,90 |
| Buzzer | 1 | R$ 9,40 |
| Tag RFID | 3 | R$ 16,50 |
| Jumper | 10 | R$ 7,00 |
| Total |   | R$ 118,20 |

# Circuito do projeto
Não é possível elaborar o circuito no tinkercad pois este software não conta com alguns dos componentes utilizados. O circuito, porém, está descrito na seguinte abaixo, que contém a ligação de todos os pinos:
| Módulo/Função          | Pino no Módulo | Pino no Arduino Uno | Observações                |
|------------------------|----------------|---------------------|----------------------------|
| **RC522 RFID**         | SDA / SS       | D10                 | `SS_PIN` (SPI SS)          |
|                        | SCK            | D13                 | SPI CLK                    |
|                        | MOSI           | D11                 | SPI MOSI                   |
|                        | MISO           | D12                 | SPI MISO                   |
|                        | RST            | D9                  | `RST_PIN`                  |
|                        | 3 V3           | 3.3 V               | Alimentação 3.3 V          |
|                        | GND            | GND                 | Terra                      |
| **OLED SSD1306 (I²C)** | SDA            | A4                  | Linha de dados I²C         |
|                        | SCL            | A5                  | Clock I²C                  |
|                        | VCC            | 5 V                 | Módulo compatível 5 V      |
|                        | GND            | GND                 | Terra                      |
| **Buzzer passivo**     | +              | D7                  | `BUZZER_PIN`               |
|                        | −              | GND                 | Terra                      |

# Circuito no Protoboard - Vista Superior

# Circuito no Protoboard - Vista Frontal

# Vídeo do funcionamento
Link do youtube: 

# Código Utilizado:


