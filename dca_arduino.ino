/*
 |-----------------------------------------------|
 | Software for Automatic Card Dealer in Arduino |
 |-----------------------------------------------|
 * Autors: Adriano José Paulichi & Vinicius Coradassi
 * Date: 04/2019
*/
// =============================================================================================================================//
// --- Auxiliary Libraries --- //
#include <Stepper.h>  //Step motor library
#include <string.h>

// =============================================================================================================================//
// --- Hardware Mapping --- //
#define in1 8     //ULN2003 input 1
#define in2 9     //ULN2003 input 2
#define in3 10    //ULN2003 input 3
#define in4 11    //ULN2003 input 4

#define transistor_pin 12 

// =============================================================================================================================//
// --- Macros --- //
#define STEPS_PER_CYCLE 2048
#define MAX_SPEED 18 //in rpm
#define DELAY_PER_CARD 1000 // in milliseconds

// =============================================================================================================================//
// --- Game Type --- //
typedef struct _game{
  int _id;
  int _nCards;
  int _nPlayers;
  String _name;
} Game;

//Game constructor
Game* newGame(String game_name, int nCards, int nPlayers){
  Game* new_game = (Game*)malloc(sizeof(Game));
  new_game->_nCards = nCards;
  new_game->_nPlayers = nPlayers;
  new_game->_name = game_name;
  return new_game;
} //end game constructor

// =============================================================================================================================//
// --- Pointers Declaration --- //
// Games Pointers //
  Game* truco         = NULL;
  Game* poker         = NULL;
  
  Game* selected_game = NULL;
  
// =============================================================================================================================//
// --- Objects Declaration --- //
Stepper axeStepper(STEPS_PER_CYCLE, in1, in3, in2, in4); //Principal axe step control

// =============================================================================================================================//
// --- Auxiliary Functions --- //

void dispenseCards(int nCards){
  //Turn on the DC motor
  digitalWrite(transistor_pin, HIGH);
  //Waits for the cards to be dispensed
  delay(DELAY_PER_CARD * nCards);
}

//void rotatePrincialAxe()

// =============================================================================================================================//
// --- Initial configs --- //
void setup() {
  Serial.begin(9600);

  pinMode(transistor_pin, OUTPUT);

  axeStepper.setSpeed(MAX_SPEED);
 
  truco = newGame("Truco", 3, 4);
} //end setup

// =============================================================================================================================//
// --- Infinite Loop --- //
void loop() {

  /* Fazer algo para selecionar o jogo */
  selected_game = truco; //Exemplo atual
  
  //Rotates principal axe stopping at nPlayers positions
  for ( int i = 0; i < selected_game->_nPlayers ; i++){
    axeStepper.step(STEPS_PER_CYCLE / selected_game->_nPlayers);

    dispenseCards(selected_game->_nCards);
  }
  //Rotate back to initial position
  axeStepper.step(-STEPS_PER_CYCLE);
  
} //end loop
