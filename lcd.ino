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

void print_allButtons()
{
	print_leftButton();
	print_rightButton();
	print_okButton();
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
