// =============================================================================================================================//
// === Step motor - Principal Axe === //
void rotatePrincipalAxe(float n_revs)
{
	axeStepper.step(STEPS_PER_CYCLE * n_revs);
}

// =============================================================================================================================//
// === DC Motor - Dispenser === //
void dispenseCards(int nCards)
{
	cardDisp_out();
	delay(nCards * DELAY_PER_CARD);
	cardDisp_stop();
}

void cardDisp_stop()
{
	analogWrite(PWM_PIN_CARDS_OUT, 0);
	analogWrite(PWM_PIN_CARDS_IN, 0);
}

void cardDisp_out()
{
	analogWrite(PWM_PIN_CARDS_OUT, int(255.0f * DISP_VEL_PERCENT / 100.0f));
	analogWrite(PWM_PIN_CARDS_IN, 0);
}

void cardDisp_in()
{
	analogWrite(PWM_PIN_CARDS_IN, int(255.0f * DISP_VEL_PERCENT / 100.0f));
	analogWrite(PWM_PIN_CARDS_OUT, 0);
}

// =============================================================================================================================//
// === DC Motor - Elevator === //
void cardElev_stop()
{
	analogWrite(PWM_PIN_CARDS_UP, 0);
	analogWrite(PWM_PIN_CARDS_DOWN, 0);
}

void cardElev_down()
{
	analogWrite(PWM_PIN_CARDS_DOWN, int(255.0f * ELEV_VEL_PERCENT / 100.0f));
	analogWrite(PWM_PIN_CARDS_UP, 0);
}

void cardElev_up()
{
	analogWrite(PWM_PIN_CARDS_DOWN, 0);
	analogWrite(PWM_PIN_CARDS_UP, int(255.0f * ELEV_VEL_PERCENT / 100.0f));
}
