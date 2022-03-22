#include "SimonSays.h"

Game GameOne(true);


void setup() {
Serial.begin(9600);  // put your setup code here, to run once:
}

void loop() {
  
  GameOne.Set_Outputs();//Sets the outputs and inputs for the pins being used
  GameOne.TestBuzzer();//Tests the buzzer frequencies
  GameOne.TestButtons();//Tests the buttons used
  GameOne.ShowSequence(); //Shows the sequence that needs to be repeated by the player
  GameOne.ReadSequence(); //The player creates a sequence and it is stored in the array.
  GameOne.CheckAnswer(); //The generated sequence and the sequence created by the player are compared.
}
