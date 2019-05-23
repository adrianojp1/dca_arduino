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

//Stepper axeStepper(STEPS_PER_CYCLE, in1, in3, in2, in4);
#define in1 8  //ULN2003 input 1
#define in2 9  //ULN2003 input 2
#define in3 10 //ULN2003 input 3
#define in4 12 //ULN2003 input 4

//LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);
#define DB4 5 //LCD Data Bus Line 4
#define DB5 4 //LCD Data Bus Line 5
#define DB6 3 //LCD Data Bus Line 6
#define DB7 2 //LCD Data Bus Line 7
#define RS 7  //LCD Register Selector (on/off)
#define E 6   //LCD Enable writing signal on the LCD

#define PWM_PIN 11 //PWM pin for the L298N driver (DC motor)
//analogWrite(PWM_PIN, pwm_value) value from 0(0% of duty cycle) to 255 (100% of duty cycle)

//Pushbuttons 14, 15, 16
#define PB1_PIN 14 //Pushbutton Up pin
#define PB2_PIN 15 //Pushbutton Down pin
#define PB3_PIN 16 //Pushbutton Select pin

// =============================================================================================================================//
// --- Macros --- //
#define STEPS_PER_CYCLE 2048
#define MAX_SPEED 15        //in rpm
#define DELAY_PER_CARD 1000 // in milliseconds

#define ST_IDLE 0
#define ST_TRUCO 1
#define ST_POKER 2

#define OP_TRUCO 1
#define OP_POKER 2

// =============================================================================================================================//
// --- Variables Declaration --- //
int onOp = -1;          // Menu option displayed

bool DCA_isIdle; //False: DCA is distributing

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
void menu();
void distributing();

//Games
void distr_truco();
//void distr_poker();

//Distribution
void dispenseCards(int nCards);
void rotatePrincipalAxe(float n_revs); // n_revs < 0: spins counter clockwise

//LCD
void print_SelecionarJogo();
void print_leftButton();
void print_rightButton();
void print_okButton();
void print_msg(String msg);

// =============================================================================================================================//
// --- Initial configs --- //
void setup()
{
  onOp = 0;

  lcd.begin(16, 2); //Define number of rows and columns

  pinMode(PWM_PIN, OUTPUT); //PWM pin

  axeStepper.setSpeed(MAX_SPEED); //Step motor

  Serial.begin(9600); //Starts serial port
} //end setup

// =============================================================================================================================//
// --- Infinite Loop --- //
void loop()
{
  if(DCA_isIdle)
    menu();
  else
    distributing();

  Serial.print(onOp);
  
} //end loop
