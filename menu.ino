// =============================================================================================================================//
// --- Auxiliary Functions Definitions --- //

void menu_games()
{
	onOp = TRUCO;
	gamesMenu_open = true;
	while (gamesMenu_open)
	{
		lcd.clear();
		
		switch (onOp)
		{
		case TRUCO:
			print_msg("Truco");
			print_firstOpButtons();
			
			break;
		
		case POKER:
			print_msg("Teste");
			print_allButtons();
			
			break;
		
		case QUIT:
			print_msg("Sair");
			print_lastOpButtons();
			
			break;
		default:
			
			break;
		} //end switch

		waitForAnyButton();
		checkArrowButtons(TRUCO, QUIT);
		if (button_ok.isPressed())
		{
			delay(KEY_DELAY);
			switch (onOp)
			{
			case TRUCO:
				lcd.clear();
				print_msg("Truco");
				op_truco();
				break;
			
			case POKER:
				lcd.clear();
				print_msg("Teste");
				teste_elevador();
				//op_poker();
				break;
			
			case QUIT:
				break;

			default:
				break;
			}

			gamesMenu_open = false;
			onOp = SELECT_GAME;
		}
		Serial.println(onOp);
		delay(10);
	} //end while
} // end menu

void waitForAnyButton()
{
	while (!button_right.isPressed() && !button_left.isPressed() && !button_ok.isPressed())
	{
		//Waiting for a press to end the loop
	}
}

void checkArrowButtons(int firstOp, int lastOp)
{
	Serial.println(onOp);
	Serial.println(lastOp);
	if (button_right.isPressed())
	{
		if(onOp != lastOp)
			moveOp_right();
		delay(KEY_DELAY);
	}
	if (button_left.isPressed())
	{
		if(onOp != firstOp)
			moveOp_left();
		delay(KEY_DELAY);
	}
	
}

void moveOp_left()
{
	onOp--;
}

void moveOp_right()
{
	onOp++;
}

void op_truco()
{
    //Dispenses 3 cards in 4 positions
    for( int i = 0; i<3; i++)
    {
        dispenseCards(3);
        delay(500);
        rotatePrincipalAxe((float)1/4);
        delay(500);
    }
    dispenseCards(3);
    delay(500);
    
    //Rotates back and dispense the flip
    rotatePrincipalAxe((float)-3/8);
    delay(500);
    dispenseCards(1);
    delay(500);
    
    //Rotates back to initial position
    rotatePrincipalAxe((float)-3/8);
}

void teste_elevador()
{
	cardElev_up();
	Serial.println("Up");
	delay(1000);
	cardElev_stop();
	button_ok.waitForButton();
	cardElev_down();
	Serial.println("Down");
	delay(1000);
	cardElev_stop();
	button_ok.waitForButton();
	delay(500);
	Serial.println("Acabou");
}

void teste_dispenser()
{
}
