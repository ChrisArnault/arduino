#include <SoftwareSerial.h>

#ifndef ARDPRINTF
#define ARDPRINTF
#define ARDBUFFER 16
#include <stdarg.h>
#include <Arduino.h>

void int2bin(int d, char temp[8])
{
  for (int i = 0; i < 8; i++)
  {
    int b = (d >> i) & 0x01;
    temp[i] = b == 0 ? '0' : '1';
  }
}

int ardprintf(char *str, ...)
{
  int i, count=0, j=0, flag=0;
  char temp[ARDBUFFER+1];
  for(i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++;

  va_list argv;
  va_start(argv, count);
  for(i=0,j=0; str[i]!='\0';i++)
  {
    if(str[i]=='%')
    {
      temp[j] = '\0';
      Serial.print(temp);
      j=0;
      temp[0] = '\0';

      switch(str[++i])
      {
        case 'd': Serial.print(va_arg(argv, int));
                  break;
        case 'l': Serial.print(va_arg(argv, long));
                  break;
        case 'f': Serial.print(va_arg(argv, double));
                  break;
        case 'c': Serial.print((char)va_arg(argv, int));
                  break;
        case 's': Serial.print(va_arg(argv, char *));
                  break;
        default:  ;
      };
    }
    else 
    {
      temp[j] = str[i];
      j = (j+1)%ARDBUFFER;
      if(j==0) 
      {
        temp[ARDBUFFER] = '\0';
        Serial.print(temp);
        temp[0]='\0';
      }
    }
  };
  Serial.println();
  return count + 1;
}
#undef ARDBUFFER
#endif

//update from SAnwandter
#define ROW_1 2
#define ROW_2 3
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

// The display buffer
// It's prefilled with a smiling face (1 = ON, 0 = OFF)
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
byte EX[]  = {B00000000,B00010000,B00010000,B00010000,B00010000,B00000000,B00010000,B00000000};
byte A[]   = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
byte B[]   = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
byte C[]   = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
byte D[]   = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
byte E[]   = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
byte F[]   = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
byte G[]   = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
byte H[]   = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
byte I[]   = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
byte J[]   = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
byte K[]   = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
byte L[]   = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
byte M[]   = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
byte N[]   = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
byte O[]   = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
byte P[]   = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
byte Q[]   = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
byte R[]   = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
byte S[]   = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
byte T[]   = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte U[]   = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
byte V[]   = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
byte W[]   = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
byte X[]   = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
byte Y[]   = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte Z[]   = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000}; 

byte LETTERS[]   = {
  B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110,
  B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100,
  B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110,
  B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000,
  B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000,
  B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000,
  B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000,
  B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000,
  B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000,
  B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000,
  B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000,
  B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000,
  B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000,
  B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000,
  B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000,
  B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000,
  B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001,
  B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000,
  B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000,
  B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000,
  B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000,
  B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000,
  B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000,
  B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000,
  B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000,
  B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000,
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111}; 

int timeCount = 0;

void setup() 
{
    // Open serial port
    Serial.begin(9600);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
#define ROW_1 2
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

void loop() {
  // This could be rewritten to not use a delay, which would make it appear brighter
  delay(5);
  timeCount += 1;
  
  int delta = 200;
  int letters = 0;

  if (letters == 1)
  {
    int letter_index = int(timeCount / delta);
    if (letter_index < 26)
    {
      Serial.println(letter_index);
      Serial.println(timeCount);
      drawScreen(letter_index * 8);
      delay(1);
    } 
    else {
    // back to the start
      timeCount = 0;
    }
  }
  else
  {
    int letter_index = int(timeCount / delta);
    int N = 10;
    if (letter_index < 1)
    {
      byte c[N];
      byte r[N];
      for (int i = 0; i < N; i++)
      {
          c[i] = random(8);
          r[i] = random(8);
      
          drawPoints(N, c, r);
      }
    } 
    else {
    // back to the start
      timeCount = 0;
    }
  }
}

void drawScreen(int index)
{ 
   // Turn on each row in series
    for (byte r = 0; r < 8; r++)        // count next row
     {
        digitalWrite(rows[r], HIGH);    //initiate whole row
        for (byte c = 0; c < 8; c++)    // count next row
        {
          // if You set (~buffer2[r] >> c) then You will have positive
          digitalWrite(col[c], (~LETTERS[index + r] >> c) & 0x01); // initiate whole column
          delayMicroseconds(1000000);       // uncoment deley for diferent speed of display
          //delayMicroseconds(1000);
          //delay(10);
          //delay(100);
          
          digitalWrite(col[c], 1);      // reset whole column
        }
        digitalWrite(rows[r], LOW);     // reset whole row
        // otherwise last row will intersect with next row
    }
}


byte coord2row(int data, int data_min, int data_max)
{
  // peut s'appliquer à une donnée x => column ou y = row 
  byte led = ((data - data_min) / (data_max - data_min)) * 8;
  return led;
}


void drawPoints(int N, byte* column, byte* row) {
    byte LEDS[] = {
      B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
    };

    for (int r = 0; r < 8; r++)
    {
      LEDS[r] = 0;
    }

    for (int r = 0; r < 8; r++)
    {
       for (int i = 0; i < N; i++)
       {
          if (r == row[i])
          {
             byte d = 1 << column[i];
             LEDS[r] |= d;
          }
       }
    }

    // Turn on each row in series
    for (byte r = 0; r < 8; r++)
    {
        digitalWrite(rows[r], HIGH); // initiate whole row
        for (byte c = 0; c < 8; c++) // count next col
        {
            digitalWrite(col[c], (~LEDS[r] >> c) & 0x01); // initiate whole column

            delayMicroseconds(1000); // uncoment deley for diferent speed of display
            // delayMicroseconds(30000);
            // delayMicroseconds(10); // uncoment deley for diferent speed of display
            digitalWrite(col[c], 1); // reset whole column
        }
        digitalWrite(rows[r], LOW); // reset whole row
        // otherwise last row will intersect with next row
    }
}
