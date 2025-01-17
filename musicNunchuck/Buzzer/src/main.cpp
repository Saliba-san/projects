#include <Arduino.h>
#include <Wire.h>
#include "nunchuck_funcs.h"
#include <math.h>

struct colors {
  int color[12][3];
  colors() {
    color[0][0] = 0;
    color[0][1] = 255;
    color[0][2] = 0;
    color[1][0] = 0;
    color[1][1] = 255;
    color[1][2] = 170;
    color[2][0] = 0;
    color[2][1] = 85;
    color[2][2] = 255;
    color[3][0] = 0;
    color[3][1] = 0;
    color[3][2] = 255;
    color[4][0] = 100;
    color[4][1] = 0;
    color[4][2] = 255;
    color[5][0] = 255;
    color[5][1] = 0;
    color[5][2] = 255;
    color[6][0] = 255;
    color[6][1] = 0;
    color[6][2] = 80;
    color[7][0] = 255;
    color[7][1] = 0;
    color[7][2] = 0;
    color[8][0] = 255;
    color[8][1] = 42;
    color[8][2] = 0;
    color[9][0] = 255;
    color[9][1] = 100;
    color[9][2] = 0;
    color[10][0] = 255;
    color[10][1] = 180;
    color[10][2] = 0;
    color[11][0] = 128;
    color[11][1] = 255;
    color[11][2] = 0;

  }
} col;

struct keys {
  int note[89];
  keys() {
    note[0] = 31; //B0
    note[1] = 33; //C1
    note[2] = 35;
    note[3] = 37;
    note[4] = 39;
    note[5] = 41;
    note[6] = 44;
    note[7] = 46;
    note[8] = 49;
    note[9] = 52;
    note[10] = 55;
    note[11] = 58;
    note[12] = 62;
    note[13] = 65;//C2
    note[14] = 69;
    note[15] = 73;
    note[16] = 78;
    note[17] = 82;
    note[18] = 87;
    note[19] = 93;
    note[20] = 98;
    note[21] = 104;
    note[22] = 110;
    note[23] = 117;
    note[24] = 123;
    note[25] = 131;//C3
    note[26] = 139;
    note[27] = 147;
    note[28] = 156;
    note[29] = 165;
    note[30] = 175;
    note[31] = 185;
    note[32] = 196;
    note[33] = 208;
    note[34] = 220;
    note[35] = 233;
    note[36] = 247;
    note[37] = 262;//C4
    note[38] = 277;
    note[39] = 294;
    note[40] = 311;
    note[41] = 330;
    note[42] = 349;
    note[43] = 370;
    note[44] = 392;
    note[45] = 415;
    note[46] = 440;
    note[47] = 466;
    note[48] = 494;
    note[49] = 523;//C5
    note[50] = 554;
    note[51] = 587;
    note[52] = 622;
    note[53] = 659;
    note[54] = 698;
    note[55] = 740;
    note[56] = 784;
    note[57] = 831;
    note[58] = 880;
    note[59] = 932;
    note[60] = 988;
    note[61] = 1047;//C6
    note[62] = 1109;
    note[63] = 1175;
    note[64] = 1245;
    note[65] = 1319;
    note[66] = 1397;
    note[67] = 1480;
    note[68] = 1568;
    note[69] = 1661;
    note[70] = 1760;
    note[71] = 1865;
    note[72] = 1976;
    note[73] = 2093;//C7
    note[74] = 2217;
    note[75] = 2349;
    note[76] = 2489;
    note[77] = 2637;
    note[78] = 2794;
    note[79] = 2911;
    note[80] = 3136;
    note[81] = 3322;
    note[82] = 3520;
    note[83] = 3729;
    note[84] = 3951;
    note[85] = 4186;//C8
    note[86] = 4435;
    note[87] = 4699;
    note[88] = 4978;//DS8
  }
} key;




int buzzer = 5;
//int botao1 = 13;
int botao_04 = 2;
int botao_08 = 4;
int botao_12 = 7;
int nota = 0;

//int pot1 = A0;
//int pot2 = A1;
//int pot3 = A2;

//int redPin = 6;
//int greenPin = 9;
//int bluePin = 10;

float normNota = 0;
//float normRange = 0;
//float normOmega = 0;

int t = 1;
int tn = 1;
//int tr = 1;
//int to = 1;

void setup() {

 nunchuck_setpowerpins();
  //Inicializa o controle
 nunchuck_init();
 //define o pino 9 como saída
 pinMode(buzzer,OUTPUT);
 //pinMode(botao1,INPUT);
 pinMode(botao_04,INPUT);
 pinMode(botao_08,INPUT);
 pinMode(botao_12,INPUT);
 //pinMode(pot1,INPUT);
 //pinMode(pot2, INPUT);
 //pinMode(pot3, OUTPUT);

 //pinMode(redPin, OUTPUT);
 //pinMode(greenPin, OUTPUT);
 //pinMode(bluePin, OUTPUT);

 Serial.begin(9600);
}

void color(unsigned char red, unsigned char green, unsigned char blue) {
//analogWrite(redPin, 255-red);
//analogWrite(greenPin, 255-green);
//analogWrite(bluePin, 255-blue);
}

int buttonPress(bool p1, bool p2, bool p3, bool p4, bool p5, int notaAnterior, int valNota, float valRange, float valOmega) {
 int a;
 float lfo = 1;
 a = p1*1 + p2*2 + p3*4 + p4*8 + p5*12;
 if (a != notaAnterior && notaAnterior != 1000 && notaAnterior && a) {
   delay(20);
   a = 0;
 }
 if (!notaAnterior && a)  {
   delay(20);
   return 1000;
 }
 if (a) {
   //lfo = pow(1.0594, valRange*sin(valOmega*t));
   tone(5, key.note[47+a + valNota]*lfo, 20);
   color(col.color[(a-1+valNota)%12][0],col.color[(a-1+valNota)%12][1], col.color[(a-1+valNota)%12][2]);
 }
 else color(0, 0, 0);
 return a;
}

int normalize(float i) {
  float r = i - (int)i;
  if (r > 0.5) return i + 1;
  return i;
}

void loop() {
nunchuck_get_data();
int leitNota = nunchuck_joyx();
//int leitRange = analogRead(pot2);
//int leitOmega = analogRead(pot3);

if (tn < 5) normNota = normalize((1 - (1/(float)tn))*normNota+(1/(float)tn)*leitNota);
if (abs(normNota - leitNota) > 3 || leitNota < 2) tn = 1;

//if (tr < 5) normRange = normalize((1 - (1/(float)tr))*normRange+(1/(float)tr)*leitRange);
//if (abs(normRange - leitRange) > 3 || leitRange < 2) tr = 1;

//if (to < 5) normOmega = normalize((1 - (1/(float)to))*normOmega+(1/(float)to)*leitOmega);
//if (abs(normOmega - leitOmega) > 3 || leitOmega < 2) to = 1;



int p1 = nunchuck_cbutton();
int p2 = nunchuck_zbutton();// = digitalRead(botao_04);
//int p1 = 0; int p2 = 0;
int p3 = digitalRead(botao_04);
//int p4 = 0; int p5 = 0;
int p4 = digitalRead(botao_08);
int p5 = digitalRead(botao_12);
//int valNota = 16;
int valRange = 0;
int valOmega = 0;
int valNota = (4*normNota-520)/160;/* + normNota/1016*/;
//float valRange = normRange/(float)512;
//float valOmega = normOmega/(float)200;
nota = buttonPress(p1, p2, p3, p4, p5, nota, valNota, valRange, valOmega);
Serial.print(leitNota);
Serial.print("\t");
Serial.print(valNota);
Serial.print("\n");
/*
Serial.print(leitNota);
Serial.print("\t");
Serial.print(normNota);
Serial.print("\t");
Serial.print(valNota);
Serial.print("\t");
Serial.print(tr);
Serial.print("\t");
Serial.print(leitRange);
Serial.print("\t");
Serial.print(normRange);
Serial.print("\t");
Serial.print(valRange);
Serial.print("\t");
Serial.print(to);
Serial.print("\t");
Serial.print(leitOmega);
Serial.print("\t");;
    color[7][0] = 255;
    color[7][1] = 0;
    color[7][2] = 0;
    color[8][0] = 255;
    color[8][1] = 42;
    color[8][2] = 0;
    color[9][0] = 255;
    color[9][1] = 100;
    color[9][2] = 0;
    color[10][0] = 255;
    color[10][1] = 180;
    color[10][2] = 0;
    color[11][0] = 128;
    color[11][1] = 255;
    color[11][2] = 0;

  }
} col;

struct keys {
  int note[89];
  keys() {
    note[0] = 31; //B0
    note[1] = 33; //C1
    note[2] = 35;
    note[3] = 37;
    note[4] = 39;
    note[5] = 41;
    note[6] = 44;
    note[7] = 46;
    note[8] = 49;
    note[9] = 52;
    note[10] = 55;
    note[11] = 58;
    note[12] = 62;
    note[13] = 65;//C2
    note[14] = 69;
Serial.print(normOmega);
Serial.print("\t");
Serial.print(valOmega);
Serial.print("\n");*/

//t++;
tn++;
//tr++;
//to++;
}
