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
#define DB7 9 //LCD Data Bus Line 7
#define RS 7  //LCD Register Selector (on/off)
#define E 6   //LCD Enable writing signal on the LC

//Pushbuttons 14, 15, 16
#define PB1_PIN 14 //Pushbutton Left pin
#define PB2_PIN 15 //Pushbutton Right pin
#define PB3_PIN 16 //Pushbutton Select pin

//Stepper elevator_stepper(STEPS_PER_CYCLE, E_IN1, E_IN3, E_IN2, E_IN4);
#define E_IN1 12 //ULN2003 input 1
#define E_IN2 17 //ULN2003 input 2
#define E_IN3 18 //ULN2003 input 3
#define E_IN4 19 //ULN2003 input 4

#define A_IN1 0 //Axe input 1
#define A_IN2 1 //Axe input 2
#define A_IN3 2 //Axe input 3
#define A_IN4 3 //Axe input 4

/* Stepper to Axe L298N wiring
Red - 2
Orange - 13
Yellow - 3
Brown - 14
Green/Black - GND
*/

#define PWM_PIN_CARDS_OUT 11 //PWM pin cards up (Elevator)
#define PWM_PIN_CARDS_IN 10 //PWM pin cards down (Elevator)

//analogWrite(PWM_PIN, pwm_value) value from 0(0% of duty cycle) to 255 (100% of duty cycle)

// =============================================================================================================================//
// --- Macros --- //
//Elevator Driver Stepper
#define STEPS_PER_CYCLE 2048
#define STEPS_PER_CARD 500
#define ELEVATOR_MAX_SPEED 15 //in rpm

//Dispenser
#define DISP_VEL_PERCENT 20 //PWM duty cycle / Min 5~10
#define DISP_DELAY_PER_CARD 400 //Dispenser delay per card

//Axe Manual Stepper
#define AXE_STEP_DELAY 50
#define STEPS_PER_REV 48

//Options
#define SELECT_GAME 0
#define GENERIC_GAME 1
#define TRUCO 2
#define POKER 3 //test
#define QUIT 4

#define KEY_DELAY 300

// =============================================================================================================================//
// --- Variables Declaration --- //
int onOp; // Menu option displayed
bool gamesMenu_open;
bool genericGame_open;

// =============================================================================================================================//
// --- Objects Declaration --- //
Stepper elevator_stepper(STEPS_PER_CYCLE, E_IN1, E_IN3, E_IN2, E_IN4); //Step motor

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
void distr_truco();
void teste();
void teste_dispenser();
//void op_poker();

//Elevator
void elevate_cards(float n_cards); // n_cards < 0: goes down

//Principal Axe
/* The only function to be called for routines
1.0f - full revolution
0.5f - half rev
...
n_revs < 0.0f rotates counter clockwise*/
void rotate_axe(float n_revs);

void a_step1();
void a_step2();
void a_step3();
void a_step4();
void make_step(int step);
/* Rotate axe clockwise
return: next step*/
int a_rot_cw(int step);
/* Rotate axe counterclockwise
return: next step*/
int a_rot_ccw(int step);

//Dispenser
void dispenseCards(int nCards);
void dispenser_turnOff();
void dispense_out();
void dispense_out();

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
	gamesMenu_open = false;
	genericGame_open = false;

	//LCD
    lcd.begin(16, 2); //Define number of rows and columns
    
	//Elevator driver
    elevator_stepper.setSpeed(ELEVATOR_MAX_SPEED); //Step motor

	//Axe
	pinMode(A_IN1, OUTPUT);
	pinMode(A_IN2, OUTPUT);
	pinMode(A_IN3, OUTPUT);
	pinMode(A_IN4, OUTPUT);
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
