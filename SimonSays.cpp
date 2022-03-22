#include "SimonSays.h"

const int Buzzer_Pin =3; //Pin which buzzer is attached too
const int Number_of_Buzzer_Frequencies= 5;  //Total Number of Buzzer Frequencies
const int buttons[] = {12,11,10,9,8}; //Button pins
const int Number_of_Pins = 5; //Number of pins
const int Buzzer_Frequencies[] = {100,200,500,600,700}; //Each buzzer frequency
int player_sequence[Number_of_Buzzer_Frequencies]= {};  //Array for storing the sequence of button pushes by the player
int Generated_Sequence[5]={}; //Array for storing the generated buzzer frequencies

Game::Game(bool) //Constructor
{
  
}

long Game::Set_Outputs() //Sets the pins being used to output or input
{  
  for(int Pin_Number=0;Pin_Number<Number_of_Pins;Pin_Number++) //Cycles through each pin to the buttons as outputs
  {
    pinMode(buttons[Pin_Number], INPUT_PULLUP); 
  }
  pinMode(Buzzer_Pin, OUTPUT);
  Serial.print("Outputs and Inputs are set\n");
  delay(500);
}

int Game::TestBuzzer() //Function for testing the Buzzer
{
    
  Serial.print("Buzzer will now Test...\n");
  delay(1000);
  
  for(int i=0; i<Number_of_Buzzer_Frequencies; i++) //For loop that tests each buzzer frequency used by the game.
  {
    Serial.print("Testing buzzer frequency ");
    Serial.println(i);
    delay(2000);
    tone(Buzzer_Pin,Buzzer_Frequencies[i],1000);
    delay(2000);
  }
  Serial.print("Buzzer Test has completed successfully\n");
  delay(2000);
}

int Game::TestButtons() //Function that tests the buttons
{
  int counter = 0; //counter determining if all buttons have been pressed.
  
  Serial.print("Button Testing will now commence\nPlease press each button, individually left to right, once for confirmation tone"); 
  delay(5000);
  while(counter!=Number_of_Pins) //While the counter is less than number of pins being used buttons will be tested.
  {
    for(int i=0; i<Number_of_Pins; i++)
    {
      int buttonstate = digitalRead(buttons[i]);
      if(buttonstate == HIGH)
      {
        Serial.println("Button has not been pressed\n");
      }
      else
      {
        Serial.println("The button is pressed\n");
        tone(Buzzer_Pin,Buzzer_Frequencies[i],1000);
        delay(1000);
        counter = counter+1; //Adds 1 for each button checked
      }
    }
  }
  delay(2000);
  Serial.print("All Buttons are working correctly\n");
  delay(2000);
}

int Game::ShowSequence() //Function that plays the sequence required 
{
  
  
  Serial.print("Random Sequence will now be shown\n");
  delay(1000);

  
  for(int i=0; i<Number_of_Buzzer_Frequencies; i++) //For loop that goes through each 
  {

    int random_value = random(0,4);

    Generated_Sequence[i]= Buzzer_Frequencies[random_value];
    tone(Buzzer_Pin,Buzzer_Frequencies[random_value],1000); 
    delay(2000);
    Serial.println(Generated_Sequence[i]);
  }
}
int Game::ReadSequence()
{
  
  boolean Mistake = false;
  
  Serial.println("Now press the Buttons in that sequence.");
  int counter = 0;
  
  while(counter<Number_of_Pins) //while loop that doesn't exit until the correct number of inputs has been detected.
  {
    
    
      int button_one_pressed = digitalRead(buttons[0]); //used to detect if button one is pressed
      int button_two_pressed = digitalRead(buttons[1]); //used to detect if button two is pressed
      int button_three_pressed = digitalRead(buttons[2]); //used to detect if button three is pressed
      int button_four_pressed = digitalRead(buttons[3]);  //used to detect if button four is pressed
      int button_five_pressed = digitalRead(buttons[4]); //used to detect if button five is pressed
      
      if(button_one_pressed == LOW) //if button one is presseed then frequency 1 is added to player sequence and counter +1.
      {
        tone(Buzzer_Pin,Buzzer_Frequencies[0],1000);  
        player_sequence[counter] = 100;
        counter = counter +1;
        Serial.print("100");
        delay(1000);
      }
    
      if(button_two_pressed == LOW)//if button two is presseed then frequency 2 is added to player sequence and counter +1.
      {
        tone(Buzzer_Pin,Buzzer_Frequencies[1],1000);
        player_sequence[counter] = 200;
        counter=counter+1;
        Serial.print("200");
        delay(1000);
      }
    
      if(button_three_pressed == LOW) //if button one is presseed then frequency 3 is added to player sequence and counter +1.
      {
        tone(Buzzer_Pin,Buzzer_Frequencies[2],1000);
        player_sequence[counter] =500;
        counter=counter+1;
        Serial.print("500");
        delay(1000);
      }
    
      if(button_four_pressed == LOW)  //if button one is presseed then frequency 4 is added to player sequence and counter +1.
      {
        tone(Buzzer_Pin,Buzzer_Frequencies[3],1000);
        player_sequence[counter] =600;
        counter=counter+1;
        Serial.print("600");
        delay(1000);
      }
    
      if(button_five_pressed == LOW)  //if button one is presseed then frequency 5 is added to player sequence and counter +1.
      {
        tone(Buzzer_Pin,Buzzer_Frequencies[4],1000);
        player_sequence[counter] =700;
        counter=counter+1;
        Serial.print("700");
        delay(1000);
      }
      else
      {
        Serial.println("Which Button?");
        counter = counter;
      }
    }
  
  for(int i=0; i<5; i++) //prints the sequence generated by the player
   {
     Serial.println(player_sequence[i]);
   }
   delay(2000);
}

int Game::CheckAnswer() //Checks the array created by the player and the array generated by the computer to see if they are the same.
{
  int Score = 0;
  while(Score<6)    //While score of the player is < score required to win continue checking.
  {
    for(int i = 0; i<Number_of_Pins; i++)
    {
      if(player_sequence[i]!= Generated_Sequence[i]) //if statement that checks if the sequences are equal.
      {
        Serial.print("Try again!");
        Score = Score;
      }
      else
      {
        Serial.print("Correct!");
        Score = Score + 1;
      }
    }
  }
}
