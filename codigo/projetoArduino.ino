#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ----------- Pinos e periféricos ----------- */
#define SS_PIN       10
#define RST_PIN       9
#define BUZZER_PIN    7

/* ----------- OLED ----------- */
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_ADDR    0x3C          // Endereço I2C padrão
// -1 porque o módulo de 4 pinos não possui pino RST dedicado
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ----------- RFID ----------- */
MFRC522 rfid(SS_PIN, RST_PIN);

/* ----------- Estrutura do aluno ----------- */
struct Student {
  byte uid[4];
  const char* name;
  const char* section;
  bool present;
};

Student students[] = {    //editar essa parte conforme for necessário para cadastrar os alunos. deve-se escanear o UID das tags em outro programa e colocar os valores em hexadecimal no campo correspondente 
  {{0x36, 0xED, 0x49, 0x5C}, "PEDRO HAMAMOTO DA PALMA", "1", false},
  {{0xD9, 0x58, 0xD0, 0xC2}, "ANDRE PASCOALINI", "2", false},
  {{0x39, 0x17, 0xF5, 0xB9}, "EDUARDO BIUSP", "TURMA 1", false},
};

const int studentCount = sizeof(students) / sizeof(Student);

String inputCommand;

/* ====================================================== */
void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.PCD_Init();

  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED não encontrado. Verifique a fiação."));
    while (true);                           // trava se falhar
  }

  display.setTextSize(1.00);                   // Fonte 6×8 px
  display.setTextColor(SSD1306_WHITE);
  showWelcome();

  Serial.println(F("Sistema pronto. Passe o cartão RFID ou digite 'Quantos alunos presentes'"));
}

void loop() {
  checkRFID();
  checkSerialInput();
 // dumpNewUID();
}

/* ------------------- RFID ------------------- */
void checkRFID() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  beepBuzzer();

  for (int i = 0; i < studentCount; i++) {
    if (compareUID(rfid.uid.uidByte, students[i].uid)) {
      if (!students[i].present) {
        students[i].present = true;
        showOnOLED(students[i].name, students[i].section, true);
        Serial.print(F("Marcado Presente: "));
      } else {
        showOnOLED(students[i].name, students[i].section, false);
        Serial.print(F("Já marcado: "));
      }
      Serial.println(students[i].name);
      delay(5000);                // mantém mensagem 3 s
      showWelcome();
      break;
    }
  }
  rfid.PICC_HaltA();
}

bool compareUID(byte* a, byte* b) {
  for (int i = 0; i < 4; i++)
    if (a[i] != b[i]) return false;
  return true;
}

/* ------------------- OLED ------------------- */
void showOnOLED(const char* name, const char* section, bool firstTime) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Nome: "));
  display.println(name);
  display.print(F("Turma: "));
  display.println(section);
  display.print(F("Status: "));
  display.println(firstTime ? F("Presente") : F("Ja escaneado"));
  display.display();
}

void showWelcome() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Sistema de Presenca"));
//  display.println(F("      System"));
  display.display();
}

/* ------------------- Serial ------------------- */
void checkSerialInput() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputCommand.trim();
      if (inputCommand.equalsIgnoreCase("Quantos alunos presentes")) {
        showAttendance();
      }
      inputCommand = "";
    } else {
      inputCommand += c;
    }
  }
}

void showAttendance() {
  Serial.println(F("---- Relatório de presença ----"));
  for (int i = 0; i < studentCount; i++) {
    Serial.print(students[i].name);
    Serial.print(" - ");
    Serial.println(students[i].present ? "Presente" : "Ausente");
  }
  Serial.println(F("---------------------------"));
}

/* ------------------- Buzzer ------------------- */
void beepBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
}


void dumpNewUID() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print(F("{"));
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(F("0x"));
      if (rfid.uid.uidByte[i] < 0x10) Serial.print('0'); // zero à esquerda
      Serial.print(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) Serial.print(F(", "));
    }
    Serial.println(F("},"));
    rfid.PICC_HaltA();
  }
}
