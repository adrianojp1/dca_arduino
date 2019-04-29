/*
 |-----------------------------------------------|
 | Software for Automatic Card Dealer in Arduino |
 |-----------------------------------------------|
 * Autors: Adriano José Paulichi & Vinicius Coradassi
 * Date: 04/2019
*/
// =============================================================================================================================//
// --- Auxiliary Libraries --- //
#include <Stepper.h> //Step motor library
#include <LiquidCrystal.h> //LCD library

// =============================================================================================================================//
// --- Hardware Mapping --- //
#define in1 8  //ULN2003 input 1
#define in2 9  //ULN2003 input 2
#define in3 10 //ULN2003 input 3
#define in4 11 //ULN2003 input 4

#define transistor_pin 7

// =============================================================================================================================//
// --- Macros --- //
#define STEPS_PER_CYCLE 2048
#define MAX_SPEED 18		//in rpm
#define DELAY_PER_CARD 1000 // in milliseconds

#define ST_IDLE 0
#define ST_TRUCO 1
#define ST_POKER 2

#define OP_TRUCO 1
#define OP_POKER 2

// =============================================================================================================================//
// --- Variables Declaration --- //
int dca_state = -1;
int onOp = -1;
String DisplayMsg = "";

bool onMenu;

bool pbUp_pressed;
bool pbDown_pressed;
bool pbSelect_pressed;

// =============================================================================================================================//
// --- Objects Declaration --- //
//Stepper axeStepper(STEPS_PER_CYCLE, in1, in3, in2, in4); //Principal axe step control

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// =============================================================================================================================//
// --- Auxiliary Functions Declarations --- //

void dispenseCards(int nCards);

void rotatePrincialAxe(float percent);

void changeMsg(String msg); //change display message

void checkButtons(); //test

//Routine functions
void menu();
void distributing();

// =============================================================================================================================//
// --- Initial configs --- //
void setup()
{
  dca_state = ST_IDLE;
  onOp = 0;

  onMenu = false;

  pbUp_pressed = false;
  pbDown_pressed = false;
  pbSelect_pressed = false;
  
	Serial.begin(9600);

  lcd.begin(16,2); //Define number of rows and columns
	/*pinMode(transistor_pin, OUTPUT);

	axeStepper.setSpeed(MAX_SPEED);

	dca_state = ST_IDLE;

	truco = newGame("Truco", 3, 4);*/
} //end setup

// =============================================================================================================================//
// --- Infinite Loop --- //
void loop()
{
  checkButtons(); //test

  if (dca_state == ST_IDLE)
    menu();
  else
    distributing();

  Serial.print(onOp);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(DisplayMsg);
  if(onMenu)
  {
    lcd.setCursor(0,1);
    lcd.print("[<-]");  

    lcd.setCursor(5,1);
    lcd.print("[->]");  

    lcd.setCursor(10,1);
    lcd.print("[x]");  
  }
  
} //end loop

/*
	switch (dca_state)
	{
	case ST_IDLE:

		break;

	case ST_ROT:
		//Rotates principal axe stopping at nPlayers positions
		for (int i = 0; i < selected_game->_nPlayers; i++)
		{
			axeStepper.step(STEPS_PER_CYCLE / selected_game->_nPlayers);

			dispenseCards(selected_game->_nCards);
		}
		//Rotate back to initial position
		axeStepper.step(-STEPS_PER_CYCLE);
		break;

	case ST_DISP:
		digitalWrite(transistor_pin, HIGH);
		delay(4000);
		digitalWrite(transistor_pin, LOW);
		delay(4000);
		break;

	default:
		Serial.print("State invalid!");
	}*/

// =============================================================================================================================//
// --- Auxiliary Functions Definitions --- //

void menu()
{
    if(onOp == 0)
    {
        DisplayMsg = "Selecionar jogo";
        if(pbSelector_pressed)
        {
          onOp++;
        }
    }
    else
    {
        onMenu = true;
        
        if(pbUp_pressed && onOp != 1)
            onOp--;
        if(pbDown_pressed && onOp != 2 /*n_totalOps*/ )
            onOp++;

        switch (onOp)
        {
        case OP_TRUCO:
            DisplayMsg = "Truco";
            if(pbSelect_pressed)
            {
                dca_state = ST_POKER;
                onOp = 0;
                onMenu = false;
            }
            break;

        case OP_POKER:
            DisplayMsg = "Poker";
            if(pbSelect_pressed)
            {
                dca_state = ST_POKER;
                onOp = 0;
                onMenu = false;
            }
            break;

        default:
            DisplayMsg = "Sair";
            if(pbSelect_pressed)
            {
                onOp = 0;
                onMenu = false;
            }
            break;
        }
    }
}

void distributing()
{
    switch (dca_state)
    {
    case ST_TRUCO:
        /* 
        for( 4x )
        {
            girar 90°
            dispensar 3 cartas
        }
            girar -45°
            dispensar 1 carta
        */
        break;
    
    case ST_POKER:
        
        break;

    default:
        dca_state = ST_IDLE;
        break;
    }
}

void checkButtons()
{
  if(Serial.read() == 'a')
    pbUp_pressed = true;
  if(Serial.read() == 'b')
    pbUp_pressed = false;
    
  if(false)
    pbDown_pressed = true;
  else
    pbDown_pressed = false;
    
  if(false)
    pbSelect_pressed = true;
  else
    pbSelect_pressed = false;
}

void dispenseCards(int nCards)
{
  
}

void rotatePrincialAxe(float percent)
{
  
}
