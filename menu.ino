// =============================================================================================================================//
// --- Auxiliary Functions Definitions --- //

void menu()
{
  if (onOp == 0)
  {
    print_SelecionarJogo();
    button_ok.waitForButton();

    onOp++;
  }
  else
  {
    if (button_left.getSingleDebouncedRelease() && onOp != 1)
      onOp--;
    if (button_right.getSingleDebouncedRelease() && onOp != 3 /*n_totalOps*/)
      onOp++;

    switch (onOp)
    {
    case OP_TRUCO:
      print_msg("Truco");
      break;

    case OP_POKER:
      print_msg("Poker");
      break;

    default:
      print_msg("Sair");
      break;
    } //end switch
    
    print_okButton();
    if(onOp != 1)
      print_leftButton();
    if(onOp != 3)
      print_rightButton();
    
    if(button_ok.getSingleDebouncedPress())
    {
      if(onOp == 3)
      {
        DCA_isIdle = true;
        onOp = 0;
        delay(500);
      }
      else
        DCA_isIdle = false;
    }

    delay(10);
  }
} // end menu

void distributing()
{
  switch(onOp)
  {
    case OP_TRUCO:
      print_msg("Truco");
      distr_truco();
      break;

    case OP_POKER:
      print_msg("Poker");
      //distr_poker();
      break;

    default:
      break;
  }
  
  DCA_isIdle = true;
  onOp = 0;
}

void distr_truco()
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

void dispenseCards(int nCards)
{
  digitalWrite(PWM_PIN, 255);
  delay(nCards * DELAY_PER_CARD);
  digitalWrite(PWM_PIN, 0   );
}

void rotatePrincipalAxe(float n_revs)
{
  axeStepper.step(STEPS_PER_CYCLE * n_revs);
}
