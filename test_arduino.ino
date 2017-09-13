#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

Servo myservo;

int val;
int botaoCerveja = 3;
char st[20];
bool liberaBotao = false;

void setup() {
  myservo.attach(9);
  pinMode(botaoCerveja, INPUT);
  digitalWrite(botaoCerveja, HIGH);
  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    Serial.print("UID da tag :");
    String conteudo= "";
    byte letra;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Mensagem : ");
    conteudo.toUpperCase();

    if (conteudo.substring(1) == "D8 4B 12 22") {
      Serial.println("Acesso liberado !");
      Serial.println();
      liberaBotao = true;
      delay(3000);
    }


    val = digitalRead(botaoCerveja);
    if (val != 1 && liberaBotao) {
       myservo.write(15);
       liberaBotao = false;
       delay(15);
    }

}