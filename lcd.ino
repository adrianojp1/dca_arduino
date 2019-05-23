
void print_SelecionarJogo()
{
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Selecionar jogo");
  //lcd.setCursor(0, 1);
  //lcd.print("Jogo");

  print_okButton();
}

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

void print_msg(String msg)
{
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(msg);
}
