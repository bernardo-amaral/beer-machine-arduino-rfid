#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

Servo myservo;

int SEGUNDOS_CERVEJA = 9; //tempo da torneira ativa

int val;
int buttonState = 0;  
char st[20];
bool liberaBotao = false;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(6);
  pinMode(3, INPUT);
  myservo.write(0);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() {
    //Serial.print("botao ");
    //Serial.println(buttonState);
    //Serial.print("acesso ");
    //Serial.println(liberaBotao);
    
    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }
buttonState = digitalRead(3);
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

    if (conteudo.substring(1) == "ED A4 DF 2B") {
      Serial.println("Acesso liberado !");
      Serial.println();
      liberaBotao = true;
    }
 
    if (buttonState == HIGH || liberaBotao) {
      Serial.println("Liberando cerveja...");
       myservo.write(25);
       liberaBotao = false;
       buttonState = false;
       delay(SEGUNDOS_CERVEJA * 1000);
       myservo.write(0);
       Serial.println("Liberando cerveja...OK");
    }

}
