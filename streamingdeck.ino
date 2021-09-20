#include <Keyboard.h>

#define encoder_1_OutA  2
#define encoder_1_OutB  3
#define encoder_1_key   15

#define encoder_2_OutA  A2
#define encoder_2_OutB  A1
#define encoder_2_key   A0

#define encoder_3_OutA  14 
#define encoder_3_OutB  16
#define encoder_3_key   10

#define ROWS            3
#define COLLUMNS        3

int state;
int old_State_1;
int old_State_2;
int old_State_3;

int row_pins[ROWS]={4,5,6};
int collumn_pins[COLLUMNS]={9,8,7};

char keys[ROWS][COLLUMNS]={
                    {KEY_F13,KEY_F14,KEY_F15},
                    {KEY_F16,KEY_F17,KEY_F18},
                    {KEY_F19,KEY_F20,KEY_F21}
                 };
                 
char r1u = KEY_F22;
char r1d = KEY_F23;
char r1k = KEY_F24;

void setup() {

//initiate matrix pins for use
//Zeilen werden als Input configuriert und dann auf high gesetzte um beim scannen der Matrix auf low gesetzte werden zu können
//Spalten configuriert als PullUpInput um beim scann zu erkennen, welcher pin auf Ground gezogen wird
  for(int i= 0; i < ROWS; i++)
  {
    pinMode(row_pins[i], OUTPUT);
    digitalWrite(row_pins[i], HIGH);
  }
  for(int j= 0; j < COLLUMNS; j++)
  {
    pinMode(collumn_pins[j], INPUT_PULLUP);
  }
  
  //intit pins for the rotary encoder Input
  pinMode(encoder_1_OutA, INPUT);
  pinMode(encoder_1_OutB, INPUT);
  pinMode(encoder_1_key, INPUT);

  pinMode(encoder_2_OutA, INPUT);
  pinMode(encoder_2_OutB, INPUT);
  pinMode(encoder_2_key,INPUT);
  
  pinMode(encoder_3_OutA, INPUT);
  pinMode(encoder_3_OutB, INPUT);
  pinMode(encoder_3_key,INPUT);
  
  
  Serial.begin (9600);
  
  //Read First Position of Channel A
  old_State_1 = digitalRead(encoder_1_OutA);
  old_State_2 = digitalRead(encoder_2_OutA);
  old_State_3 = digitalRead(encoder_3_OutA);
  

  Keyboard.begin();
}

//----------------------------------------------------------------

void loop() {

//----------------------------------------------------------------
//------------------Rotary encoder 1------------------------------
//----------------------------------------------------------------
    state = digitalRead(encoder_1_OutA);
    if (state != old_State_1 && state % 2 == 0)
    {
      if (digitalRead(encoder_1_OutB) != state)
      {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.print(r1d);
        Keyboard.releaseAll();
      }
      else {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.print(r1u);
        Keyboard.releaseAll();
      }
    }
    old_State_1 = state; // the first position was changed

    if(!digitalRead(encoder_1_key))
    {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.print(r1k);
        Keyboard.releaseAll();
        delay(200);
    }


//----------------------------------------------------------------
//------------------Rotary encoder 2------------------------------
//----------------------------------------------------------------

    state = digitalRead(encoder_2_OutA);
    if (state != old_State_2 && state % 2 == 0)
    {
      if (digitalRead(encoder_2_OutB) != state)
      {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.print(r1d);
        Keyboard.releaseAll();
      }
      else {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.print(r1u);
        Keyboard.releaseAll();
      }
    }
    old_State_2 = state; // the first position was changed

    if(!digitalRead(encoder_2_key))
    {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.print(r1k);
        Keyboard.releaseAll();
        delay(200);
    }

//----------------------------------------------------------------
//------------------Rotary encoder 3------------------------------
//----------------------------------------------------------------
    state = digitalRead(encoder_3_OutA);
    if (state != old_State_3 && state % 2 == 0)
    {
      if (digitalRead(encoder_3_OutB) != state)
     {
        Keyboard.print(r1d);
      }
      else {
        Keyboard.print(r1u);
      }
    }
    old_State_3 = state; // the first position was changed
    
    if(!digitalRead(encoder_3_key))
    {
        Keyboard.print(r1k);
        delay(200);
    }
    
//----------------------------------------------------------------
//------------------Keyboard Matrix-------------------------------
//----------------------------------------------------------------

    for(int i= 0; i < ROWS; i++)
    {
    digitalWrite(row_pins[i], LOW);
    
    for(int j= 0; j < COLLUMNS; j++)
    {
      if(!digitalRead(collumn_pins[j]))
      {
        Keyboard.print(keys[i][j]);
        delay(100);
      }
      
    }
    
    digitalWrite(row_pins[i], HIGH);
  }

}
