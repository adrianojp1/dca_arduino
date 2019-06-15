/*
 |-----------------------------------------------|
 | Software for Automatic Card Dealer in Arduino |
 |-----------------------------------------------|
 * Autors: Adriano José Paulichi & Vinicius Coradassi
 * Date: 04/2019
*/
// =============================================================================================================================//
// --- Auxiliary Libraries --- //
#include <Stepper.h>       //Step motor
#include <LiquidCrystal.h> //LCD
#include <Pushbutton.h>    //Pushbuttons

// =============================================================================================================================//
// --- Hardware Mapping --- //

//LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);
#define DB4 5 //LCD Data Bus Line 4
#define DB5 4 //LCD Data Bus Line 5
#define DB6 8 //LCD Data Bus Line 6
#define DB7 2 //LCD Data Bus Line 7
#define RS 7  //LCD Register Selector (on/off)
#define E 6   //LCD Enable writing signal on the LC

//Pushbuttons 14, 15, 16
#define PB1_PIN 14 //Pushbutton Left pin
#define PB2_PIN 15 //Pushbutton Right pin
#define PB3_PIN 16 //Pushbutton Select pin

//Stepper axeStepper(STEPS_PER_CYCLE, in1, in3, in2, in4);
#define in1 12  //ULN2003 input 1
#define in2 17 //ULN2003 input 2
#define in3 18 //ULN2003 input 3
#define in4 19 //ULN2003 input 4

#define PWM_PIN_CARDS_OUT 3 //PWM pin for the dispenser transistor
#define PWM_PIN_CARDS_IN 9 //

#define PWM_PIN_CARDS_UP 11 //PWM pin cards up (Elevator)
#define PWM_PIN_CARDS_DOWN 10 //PWM pin cards down (Elevator)

//analogWrite(PWM_PIN, pwm_value) value from 0(0% of duty cycle) to 255 (100% of duty cycle)

// =============================================================================================================================//
// --- Macros --- //
#define STEPS_PER_CYCLE 2048
#define P_AXE_MAX_SPEED 15        //in rpm
#define DELAY_PER_CARD 1000 // in milliseconds
#define KEY_DELAY 200
#define ELEV_VEL_PERCENT 30 //Min 5~10
#define DISP_VEL_PERCENT 20 //Min: 10~20

#define SELECT_GAME 0
#define GENERIC_GAME 1

#define TRUCO 2
#define POKER 3
#define QUIT 4//4

// =============================================================================================================================//
// --- Variables Declaration --- //
int onOp; // Menu option displayed
bool mainMenu_open;
bool gamesMenu_open;
bool genericGame_open;

// =============================================================================================================================//
// --- Objects Declaration --- //
Stepper axeStepper(STEPS_PER_CYCLE, in1, in3, in2, in4); //Step motor

LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7); //LCD

Pushbutton button_left(PB1_PIN);   //Pushbutton Left Arrow
Pushbutton button_right(PB2_PIN);  //Pushbutton Right Arrow
Pushbutton button_ok(PB3_PIN);     //Pushbutton Ok Selection

// =============================================================================================================================//
// --- Auxiliary Functions Declarations --- //

//Routines
void menu_games();
void waitForAnyButton();
void checkArrowButtons(int firstOp, int lastOp);
void moveOp_left();
void moveOp_right();

//Games Options
void op_truco();
void teste_elevador();
void teste_dispenser();
//void op_poker();

//Principal Axe
void rotatePrincipalAxe(float n_revs); // n_revs < 0: spins counter clockwise

//Dispenser
void dispenseCards(int nCards);
void cardDisp_stop();
void cardDisp_out();
void cardDisp_in();

//Elevator
void cardElev_stop();
void cardElev_down();
void cardElev_up();

//LCD
void print_leftButton();
void print_rightButton();
void print_okButton();
void print_allButtons();
void print_firstOpButtons();
void print_lastOpButtons();
void print_msg(String msg);

// =============================================================================================================================//
// --- Initial configs --- //
void setup()
{
    onOp = SELECT_GAME;
	bool gamesMenu_open = false;
	bool genericGame_open = false;

    lcd.begin(16, 2); //Define number of rows and columns
    
    axeStepper.setSpeed(P_AXE_MAX_SPEED); //Step motor
    
    Serial.begin(9600); //Starts serial port
} //end setup

// =============================================================================================================================//
// --- Infinite Loop --- //
void loop()
{
	lcd.clear();

	switch (onOp)
	{
	case SELECT_GAME:
		print_msg("Selecionar Jogo");
		print_firstOpButtons();

		break;

	case GENERIC_GAME:
		print_msg("Jogo Generico");
		print_lastOpButtons();

		break;

	default:
		break;
	}
	
	waitForAnyButton();
	checkArrowButtons(SELECT_GAME, GENERIC_GAME);
	if (button_ok.isPressed())
	{
		delay(KEY_DELAY);
		switch (onOp)
		{
		case SELECT_GAME:
			menu_games();
			break;

		case GENERIC_GAME:
			//função de escolher número de cartas e jogadores
			break;

		default:
			break;
		}
	}

	delay(10);
  
} //end loop
