#include "MIDIUSB.h"

int basilanDirenc[4];
int satir=4;
int sutun=8;


boolean BasiliTuslarDizisi[4][8];
boolean BirKereGonderDizisi[4][8];

int baslangicTusu =52;

//nota basışı
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}
//nota kapatma
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {

  //başlangıç değerini ayarlama
  for(int i = 0;i<4;i++){
    for(int t=0;t<8;t++){
      BasiliTuslarDizisi[i][t]=false;
      BirKereGonderDizisi[i][t]=true;
    }
  }
  
  //çıkış
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

  //giriş
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
}


void loop() {
  
  //analog sinyalden gelen değerler
  int tusDegerleri[4][8];

  //tuşlardan gelen verileri burada okuyor
  for(int i=0;i<8;i++){
    //hepsi low yani 0
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);

    //dizenin i+2 . elemanı high yani 1
    pinMode(2+i,OUTPUT);
    digitalWrite(2+i,HIGH);
    delay(1);
    delayMicroseconds(100);

    //tuşlardan gelen veriyi okur
    basilanDirenc[0] = analogRead(A0);
    basilanDirenc[1] = analogRead(A1);
    basilanDirenc[2] = analogRead(A2);
    basilanDirenc[3] = analogRead(A3);
    
    tusDegerleri[0][i]= basilanDirenc[0];
    tusDegerleri[1][i]= basilanDirenc[1];
    tusDegerleri[2][i]= basilanDirenc[2];
    tusDegerleri[3][i]= basilanDirenc[3];
  }

  
  for(int i = 0;i<4;i++){
    
    //tüm tuşlara basılmadığı zaman bütün değerler 1000 in üzerinde oluyor.
    if(tusDegerleri[i][0]>1000&&
      tusDegerleri[i][1]>1000&&
      tusDegerleri[i][2]>1000&&
      tusDegerleri[i][3]>1000&&
      tusDegerleri[i][4]>1000&&
      tusDegerleri[i][5]>1000&&
      tusDegerleri[i][6]>1000&&
      tusDegerleri[i][7]>1000){
        
    }else{

      
      for(int t=0;t<4;t++){
        for(int j=0;j<8;j++){
          // tuşa basıldığı zaman eğer değer 87 den yukarı ise o tuşa basılmıştır
          if(tusDegerleri[t][j]>87){
            
            BasiliTuslarDizisi[t][j]=true;
            
          }else{
            
              BasiliTuslarDizisi[t][j]=false;

              //tuştan parmağımızı çektiğimiz anlamına geliyor
              if(BirKereGonderDizisi[t][j]==false){
                noteOff(0, ((t*sutun)+j+1) + baslangicTusu,128);
                BirKereGonderDizisi[t][j]=true;
              }
          }
          
          //tuşa basili tutuluyorsa veya basıldıysa bu if e girer
          if(BasiliTuslarDizisi[t][j]==true){
            
            if(BirKereGonderDizisi[t][j]==true){
              noteOn(0,((t*sutun)+j+1)+baslangicTusu,128);
              BirKereGonderDizisi[t][j]=false;
            }
            
          }

          
        }
        
        MidiUSB.flush();
        
      }
      
    }
  }
  
}
