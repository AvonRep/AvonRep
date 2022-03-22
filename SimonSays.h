#ifndef Ss
#define Ss


#include <Arduino.h>

class Game
{
  public:
    Game(bool initialised=false); //constructor
    
    long Set_Outputs(); //Function that sets the outputs and inputs of each pin
    int TestBuzzer(); //Function that tests the buzzer frequencies
    int TestButtons(); //Function that tests the Buttons
    int ShowSequence(); //Function that generates a sequence that the player has to repeat
    int ReadSequence(); //Function that takes the player input.
    int CheckAnswer(); //Function that Checks the answer of the player and updates the score.
  private:
  
};


#endif
