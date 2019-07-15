// =============================================================================================================================//
// --- Auxiliary Functions Definitions --- //

void menu_games()
{
	int nPlayersPoker;
	int nPlayersGeneric;
	int nCardsGeneric;

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
			print_msg("Poker");
			print_allSelecButtons();
			
			break;

		case GENERIC_GAME:
			print_msg("Jogo Generico");
			print_allSelecButtons();

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
				distr_truco();
				break;
			
			case POKER:
				nPlayersPoker = menuPoker();
				lcd.clear();
				print_msg("Poker");
				op_poker(nPlayersPoker);
				break;

			case GENERIC_GAME:
				nPlayersGeneric = menuGenericPlayers();
				nCardsGeneric = menuGenericCards(nPlayersGeneric);
				lcd.clear();
				print_msg("Jogo generico");
				generic_game(nCardsGeneric, nPlayersGeneric);
				break;

			case QUIT:
				break;

			default:
				break;
			}

			gamesMenu_open = false;
			onOp = SELECT_GAME;
		}
		delay(500);
	} //end while
} // end menu

void waitForAnyButton(){
	while (!button_right.isPressed() && !button_left.isPressed() && !button_ok.isPressed()){
		//Waiting for a press to end the loop
	}
}

void checkArrowButtons(int firstOp, int lastOp){
	if (button_right.isPressed()){
		if(onOp != lastOp)
			moveOp_right();
		delay(KEY_DELAY);
	}
	if (button_left.isPressed()){
		if(onOp != firstOp)
			moveOp_left();
		delay(KEY_DELAY);
	}
}

void moveOp_left(){
	onOp--;
}

void moveOp_right(){
	onOp++;
}

void distr_truco(){
    //Dispenses 3 cards in 4 positions
    for( int i = 0; i<3; i++){     
		dispenseCards(3);
        delay(500);
		rotate_axe(1.0f/4.0f);
        delay(500);
    }
    dispenseCards(3);
    delay(500);
    
    //Rotates back and dispense the flip
	rotate_axe(-3.0f/8.0f);
    delay(500);
    dispenseCards(1);
    delay(500);
    
    //Rotates back to initial position
	rotate_axe(-3.0f/8.0f);
}

void op_poker(int n_Players){
	//Dispenses 2 cards in nPlayers positions
	for (int i = 0; i < (n_Players - 1); i++){
		dispenseCards(2);
		delay(500);
		rotate_axe(1.0f / n_Players);
		delay(500);
	}
	dispenseCards(2);
	delay(500);

	//Rotates back and dispense the five desk cards
	rotate_axe(-((float)((n_Players - 1) / (float)(2 * n_Players))));
	delay(500);
	dispenseCards(5);
	delay(500);

	//Rotates back to initial position
	rotate_axe(-((float)((n_Players - 1) / (float)(2 * n_Players))));
}

int menuPoker(){
	int nPlayers = MIN_POKER;

	while (!button_ok.isPressed()){
		delay(KEY_DELAY);
		print_nPlayers(nPlayers);
		waitForAnyButton();
		if (button_left.isPressed() && nPlayers != MIN_POKER){
			nPlayers--;
		}

		if (button_right.isPressed() && nPlayers != MAX_POKER){
			nPlayers++;
		}
	}
	delay(KEY_DELAY);

	return nPlayers;
}

int menuGenericPlayers(){
	int players = 1;

	while (!button_ok.isPressed()){
		delay(KEY_DELAY);
		print_nPlayers(players);
		waitForAnyButton();
		if (button_left.isPressed() && players != 1){
			players--;
		}

		if (button_right.isPressed() && players != 10){
			players++;
		}
	}
	delay(KEY_DELAY);

	return players;
}

int menuGenericCards(int players){
	int cards = 1;
	int max_cards = 52 / players;

	while (!button_ok.isPressed()){
		delay(KEY_DELAY);
		print_nCards(cards);
		waitForAnyButton();
		if (button_left.isPressed() && cards != 1){
			cards--;
		}

		if (button_right.isPressed() && cards != max_cards){
			cards++;
		}
	}
	delay(KEY_DELAY);

	return cards;
}

void generic_game(int cards, int n_Players){
	//Dispenses ncards cards in nPlayers positions
	for (int i = 0; i < (n_Players - 1); i++){
		dispenseCards(cards);
		delay(500);
		rotate_axe(1.0f / n_Players);
		delay(500);
	}
	dispenseCards(cards);
	delay(500);

	//Rotates back to initial position
	rotate_axe(-((float)((n_Players - 1) / (float)(n_Players))));
}

void move_elevator(){
	while (!button_ok.isPressed()){
		print_elevator();
		waitForAnyButton();
		if (button_left.isPressed()){
			elevate_cards(-150);
		}

		if (button_right.isPressed()){
			elevate_cards(150);
		}
	}
	delay(KEY_DELAY);
}
