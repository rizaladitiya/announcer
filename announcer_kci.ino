/*
  Program announcer eskalator KCI
  
*/

#include <SoftwareSerial.h> //library yang digunakan

#define RX_Mikro 5  //RX Arduino >> TX Module MP3 player
#define TX_Mikro 6  //TX Arduino >> RX Module MP3 player

SoftwareSerial mp3module(RX_Mikro, TX_Mikro);

static int8_t buff_send[8] = {0}; //buffer untuk pengiriman perintah    

/************ Command byte **************************/
#define lagu_berikutnya     0X01 
#define lagu_sebelumnya    0X02
#define volume_naik     0X04
#define volume_turun   0X05

#define reset_mp3         0X0C
#define mainkan         0X0D
#define pause_mp3         0X0E
#define mainkan_folder 0X0F

#define SEL_DEV        0X09
#define DEV_TF            0X02

//seting pin Digital Input
const int D7 = 7;
const int D8 = 8;
const int D9 = 9;
const int D10 = 10;



void setup() {
  // put your setup code here, to run once:
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);

  //set komunikasi ke modul MP3
  Serial.begin(9600);
  mp3module.begin(9600);
  delay(500);

  kirimperintah(SEL_DEV, DEV_TF);
  delay(500);
}
void sendMP3Command(char c) {
  switch (c) {
    case 'h':
    case '?':
      Serial.println("ini instruksinya!");
      Serial.println(" m = mainkan");
      Serial.println(" b = Pause");
      Serial.println(" n = Lagu selanjutnya");
      Serial.println(" p = Lagu sebelumnya");
      Serial.println(" + = Volume naik");
      Serial.println(" - = Volume turun");
      Serial.println(" 1 = Play folder 1");
      Serial.println(" 2 = Play folder 2");
      Serial.println(" 3 = Play folder 3");
      Serial.println(" 4 = Play folder 4");
      Serial.println(" 5 = Play folder 5");
      Serial.println(" r = Reset_mp3");
      break;

    case 'm':
      Serial.println("Putar Lagu");
      kirimperintah(mainkan, 0);
      break;

    case 'b':
      Serial.println("Lagu Berhenti");
      kirimperintah(pause_mp3, 0);
      break;

    case 'n':
      Serial.println("Lagu berikutnya");
      kirimperintah(lagu_berikutnya, 0);
      break;

    case 'p':
      Serial.println("Lagu sebelumnya");
      kirimperintah(lagu_sebelumnya, 0);
      break;

    case '+':
      Serial.println("Volume Naik");
      kirimperintah(volume_naik, 0);
      break;

    case '-':
      Serial.println("Volume Turun");
      kirimperintah(volume_turun, 0);
      break;

    case '1':
      Serial.println("Masuk ke folder 1");
      kirimperintah(mainkan_folder, 0x0101);
      break;
      
    case '2':
      Serial.println("Masuk ke folder 2");
      kirimperintah(mainkan_folder, 0x0201);
      break;

    case '3':
      Serial.println("Masuk ke folder 3");
      kirimperintah(mainkan_folder, 0x0301);
      break;

    case '4':
      Serial.println("Masuk ke folder 4");
      kirimperintah(mainkan_folder, 0x0401);
      break;

    case '5':
      Serial.println("Masuk ke folder 5");
      kirimperintah(mainkan_folder, 0x0501);
      break;

    case 'r':
      Serial.println("Reset settingan");
      kirimperintah(reset_mp3, 0x00);
      break;
      
  }
}

void kirimperintah(int8_t command, int16_t dat)
{
  delay(20);
  buff_send[0] = 0x7e;
  buff_send[1] = 0xff;
  buff_send[2] = 0x06;
  buff_send[3] = command;
  buff_send[4] = 0x00;   // 0x00 NO, 0x01 feedback
  buff_send[5] = (int8_t)(dat >> 8);
  buff_send[6] = (int8_t)(dat);
  buff_send[7] = 0xef;
  
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3module.write(buff_send[i]) ;
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  int D7State = digitalRead(D7);
  int D8State = digitalRead(D8);
  int D9State = digitalRead(D9);
  int D10State = digitalRead(D10);

  char c = ' ';

  if ( Serial.available() )
  {
    c = Serial.read();
    sendMP3Command(c);
  }


  if (D7State == HIGH) {
    // normal condition
    //sendMP3Command(1);
    Serial.println("Kondisi 1");
    delay(5);
    return;
  }

  if (D8State == HIGH) {
    // normal condition
    //sendMP3Command(2);
    Serial.println("Kondisi 2");
    delay(5);
    return;
  }

  if (D9State == HIGH) {
    // normal condition
    //sendMP3Command(3);
    Serial.println("Kondisi 3");
    delay(5);
    return;
  }

  if (D10State == HIGH) {
    // normal condition
    //sendMP3Command(4);
    Serial.println("Kondisi 4");
    delay(5);
    return;
  }
  
  //normal condition
  //sendMP3Command(5);
  delay(500); // untuk kestabilan

}
