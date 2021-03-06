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

#define PWM_PIN_CARDS_OUT 11 //PWM pin cards out (Dispenser)
#define PWM_PIN_CARDS_IN 10 //PWM pin cards in (Dispenser)

//analogWrite(PWM_PIN, pwm_value) value from 0(0% of duty cycle) to 255 (100% of duty cycle)

// =============================================================================================================================//
// --- Macros --- //
//Elevator Driver Stepper
#define STEPS_PER_CYCLE 2048
#define STEPS_PER_CARD 152
#define ELEVATOR_MAX_SPEED 17 //in rpm

//Dispenser
#define DISP_VEL_PERCENT 100 //%  PWM duty cycle / Min 5~10
#define DISP_DELAY_PER_CARD 150 //Dispenser delay per card
#define DISP_DELAY_STOP 200

//Axe Manual Stepper
#define AXE_STEP_DELAY 60
#define STEPS_PER_REV 96

//Options
#define SELECT_GAME 0
#define MV_ELEVATOR 1
#define TRUCO 2
#define POKER 3
#define GENERIC_GAME 4
#define QUIT 5
#define MIN_POKER 2
#define MAX_POKER 8

#define KEY_DELAY 250

// =============================================================================================================================//
// --- Variables Declaration --- //
int onOp; // Menu option displayed
int curr_step;
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
int menuGenericPlayers();
int menuGenericCards(int players);
void generic_game(int cards, int n_Players);
void waitForAnyButton();
void checkArrowButtons(int firstOp, int lastOp);
void moveOp_left();
void moveOp_right();
void move_elevator();

//Games Options
void distr_truco();
void op_poker(int n_Players);

//Elevator
void elevate_cards(int steps); // n_cards < 0: goes down

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
void a_step5();
void a_step6();
void a_step7();
void a_step8();
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
void dispense_in();
void dispense_out();

//LCD
void print_leftButton();
void print_rightButton();
void print_okButton();
void print_allSelecButtons();
void print_countingButtons();
void print_nPlayers(int n_Players);
void print_pokerPlayers(int n_players);
void print_elevator();
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
	curr_step = 1;

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

	case MV_ELEVATOR:
		print_msg("Mover Elevador");
		print_lastOpButtons();
		break;
	}

	waitForAnyButton();
	checkArrowButtons(SELECT_GAME, MV_ELEVATOR);
	if (button_ok.isPressed()){
		delay(KEY_DELAY);
		switch (onOp)
		{
		case SELECT_GAME:
			menu_games();
			break;

		case MV_ELEVATOR:
			move_elevator();
			break;
		}
	}
	delay(KEY_DELAY);

	delay(10);
  
} //end loop
