// =============================================================================================================================//
// === Driver Stepper - Elevator === //
void elevate_cards(float n_cards){
	elevator_stepper.step(DISP_DELAY_PER_CARD * n_cards);
}

// =============================================================================================================================//
// === Manual Stepper - Principal Axe === //
void rotate_axe(float n_revs){
	int steps = int(STEPS_PER_REV * abs(n_revs));
	int (*rotate)(int);

	rotate = n_revs > 0.0f ? a_rot_cw : a_rot_ccw;

	while(steps > 0){
		nextStep = rotate(nextStep);
		steps--;
	}
}

void make_step(int step){
	switch (step){
	case 1: a_step1(); break;
	case 2: a_step2(); break;
	case 3: a_step3(); break;
	case 4: a_step4(); break;
	case 5: a_step5(); break;
	case 6: a_step6(); break;
	case 7: a_step7(); break;
	case 8: a_step8(); break;
	}
}


void a_step1(){
	digitalWrite(A_IN1, 1);
	digitalWrite(A_IN2, 0);
	digitalWrite(A_IN3, 1);
	digitalWrite(A_IN4, 0);
	delay(AXE_STEP_DELAY);
}

void a_step2(){
	digitalWrite(A_IN1, 1);
	digitalWrite(A_IN2, 0);
	digitalWrite(A_IN3, 0);
	digitalWrite(A_IN4, 0);
	delay(AXE_STEP_DELAY);
}

void a_step3(){
	digitalWrite(A_IN1, 1);
	digitalWrite(A_IN2, 0);
	digitalWrite(A_IN3, 0);
	digitalWrite(A_IN4, 1);
	delay(AXE_STEP_DELAY);
}

void a_step4(){
	digitalWrite(A_IN1, 0);
	digitalWrite(A_IN2, 0);
	digitalWrite(A_IN3, 0);
	digitalWrite(A_IN4, 1);
	delay(AXE_STEP_DELAY);
}


void a_step5() {
	digitalWrite(A_IN1, 0);
	digitalWrite(A_IN2, 1);
	digitalWrite(A_IN3, 0);
	digitalWrite(A_IN4, 1);
	delay(AXE_STEP_DELAY);
}

void a_step6() {
	digitalWrite(A_IN1, 0);
	digitalWrite(A_IN2, 1);
	digitalWrite(A_IN3, 0);
	digitalWrite(A_IN4, 0);
	delay(AXE_STEP_DELAY);
}

void a_step7() {
	digitalWrite(A_IN1, 0);
	digitalWrite(A_IN2, 1);
	digitalWrite(A_IN3, 1);
	digitalWrite(A_IN4, 0);
	delay(AXE_STEP_DELAY);
}

void a_step8() {
	digitalWrite(A_IN1, 0);
	digitalWrite(A_IN2, 0);
	digitalWrite(A_IN3, 1);
	digitalWrite(A_IN4, 0);
	delay(AXE_STEP_DELAY);
}

int a_rot_cw(int step){
	make_step(step);
	return step == 1? 8 : step - 1; //return the next step
}

int a_rot_ccw(int step){
	make_step(step);
	return step == 8? 1 : step + 1; //return the next step
}

// =============================================================================================================================//
// === DC Motor - Dispenser === //
void dispenseCards(int nCards){
	dispense_out();
	delay(nCards * DISP_DELAY_PER_CARD);
	dispense_in();
	delay(100);
	dispenser_turnOff();
}

void dispenser_turnOff(){
	analogWrite(PWM_PIN_CARDS_OUT, 0);
	analogWrite(PWM_PIN_CARDS_IN, 0);
}

void dispense_in(){
	analogWrite(PWM_PIN_CARDS_IN, 255 /*int(255.0f * DISP_VEL_PERCENT / 100.0f)*/);
	analogWrite(PWM_PIN_CARDS_OUT, 0);
}

void dispense_out(){
	analogWrite(PWM_PIN_CARDS_IN, 0);
	analogWrite(PWM_PIN_CARDS_OUT, int(255.0f * DISP_VEL_PERCENT / 100.0f));
}
