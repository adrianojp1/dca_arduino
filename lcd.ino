void print_leftButton()
{
    lcd.setCursor(0, 1);
    lcd.print("[<-]");
}

void print_rightButton()
{
    lcd.setCursor(5, 1);
    lcd.print("[->]");
}

void print_okButton()
{
    lcd.setCursor(10, 1);
    lcd.print("[OK]");
}

void print_minusButton()
{
	lcd.setCursor(0, 1);
	lcd.print("[-]");
}

void print_plusButton()
{
	lcd.setCursor(5, 1);
	lcd.print("[+]");
}

void print_allSelecButtons()
{
	print_leftButton();
	print_rightButton();
	print_okButton();
}

void print_countingButtons() {
	print_minusButton();
	print_plusButton();
	print_okButton();
}

void print_nPlayers(int n_Players)
{
	lcd.clear();
	print_msg("Jogadores: ");
	print_countingButtons();
	print_pokerPlayers(n_Players);
}

void print_nCards(int nCards)
{
	lcd.clear();
	print_msg("Cartas: ");
	print_countingButtons();
	lcd.setCursor(9, 0);
	lcd.print(nCards);
}


void print_pokerPlayers(int n_players)
{
	lcd.setCursor(12, 0);
	lcd.print(n_players);
}

void print_elevator()
{
	lcd.clear();
	lcd.print("Ajustando");
	print_countingButtons();
}

void print_firstOpButtons()
{
	print_rightButton();
	print_okButton();
}

void print_lastOpButtons()
{
	print_leftButton();
	print_okButton();
}

void print_msg(String msg)
{
    lcd.setCursor(0, 0);
    lcd.print(msg);
}
