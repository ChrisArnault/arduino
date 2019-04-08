#include <SoftwareSerial.h>

/*
 * Define constants for identification of the digital pins for the LED matrix
 */
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

// general counter to be incremented at each loop execution
long timeCount = 0;
long speed = 9600;
//long speed = 115200;

char buffer[256];
int pos = 0;



void setup() 
{
    // Open serial port
    Serial.begin(speed);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

/*
  while (Serial.available() > 0) {
    Serial.println("data");
    char data = Serial.read();
    if (data == '#')
    {
      Serial.println("read data");
      Serial.println(buffer);
      pos += 1;
    }
    else
    {
      Serial.println("data");
      buffer[pos] = data;
      buffer[pos+1] = 0;
      pos += 1;
    }
  }  
*/

}

/*
 * Conversion function:
 *  data in   [min ... max[
 *  output in [0 .. 8[
 */
byte coord2row(long data, long data_min, long data_max)
{
  byte led = byte((float(data - data_min) / float(data_max - data_min)) * 8.0);
  return led;
}

bool started = false;
long number = 0;

/*
 * the current Led (row, column) to be set in the LED matrix
 */
byte c = 0;
byte r = 0;

int command()
{
  if(Serial.available() > 0) {
    char data = Serial.read();
    if (data == '#')
    {
      Serial.println(buffer);

      if (strcmp(buffer, "start") == 0)
      {
        pos = 0;
        return 1;
      }
      if (strcmp(buffer, "stop") == 0)
      {
        pos = 0;
        return 2;
      }
      if (strcmp(buffer, "running") == 0)
      {
        pos = 0;
        return 3;
      }

      // Serial.flush();

      pos = 0;
    }
    else
    {
      buffer[pos] = data;
      buffer[pos+1] = 0;
      pos += 1;
    }
  }  
}

void get_coords(int* x, int* y)
{
  if(Serial.available() > 0) {
    char data = Serial.read();
    if (data == '#')
    {
      number += 1;

      /*
      Serial.print('(');
      Serial.print(number);
      Serial.print(')');
      Serial.print(buffer);
      */

      char delims[] = "|";
      char* ptr = strtok(buffer, delims);

      int var = 0;

      while(ptr != NULL) {
          // create next part
          int value = atoi(ptr);
          if (value < 0) value = 0;
          if (value >= 256) value = 255;
          if (var == 0)
          {
            *x = value;
          }
          if (var == 1)
          {
            *y = value;
          }
          //Serial.print(" - ");
          //Serial.print(value);
          ptr = strtok(NULL, delims);
          var += 1;
      }

      //Serial.println("");

      pos = 0;
    }
    else
    {
      buffer[pos] = data;
      buffer[pos+1] = 0;
      pos += 1;
    }
  }
}

void loop() {
    timeCount += 1;
    // A visit rate of 30000 roughly corresponds to one second
    // ie. the minimal loop occurs at the maximal frequence of 1/30000 seconds = 33 µs

    long change_point = 1;
    if (timeCount % change_point == 0)
    {
      //int x = random(256);
      //int y = random(256);

      int x = -1;
      int y = -1;

      get_coords(&x, &y);

      if (x > -1 && y > -1)
      {
        number += 1;
        // Serial.println(timeCount);

        /*
        Serial.print("<");
        Serial.print("(");
        Serial.print(number);
        Serial.print(")");
        Serial.print("x = ");
        */
        c = coord2row(x, 0, 256);
        r = coord2row(y, 0, 256);
        /*
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.print(c);
        Serial.print(",");
        Serial.print(r);
        Serial.println("");
        */
      }
    }

    // bright [0.0 .. 1.0] = brillance of LEDS
    // 
    float bright = 0.5;
    if (timeCount % int(1.0 / bright) == 0)
    {
      drawPoint(c, r);
    }
}

void drawPoint(byte column, byte row) {
    byte LEDS[] = {
      B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
    };

    for (int r = 0; r < 8; r++)
    {
      LEDS[r] = 0;
    }

    for (int r = 0; r < 8; r++)
    {
      if (r == row)
      {
         byte d = 1 << column;
         LEDS[r] |= d;
      }
    }

    // Turn on each row in series
    for (byte r = 0; r < 8; r++)
    {
        digitalWrite(rows[r], HIGH); // initiate whole row
        for (byte c = 0; c < 8; c++) // count next col
        {
            digitalWrite(col[c], (~LEDS[r] >> c) & 0x01); // initiate whole column
            digitalWrite(col[c], 1); // reset whole column
        }
        digitalWrite(rows[r], LOW); // reset whole row
        // otherwise last row will intersect with next row
    }
}
