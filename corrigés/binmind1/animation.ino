void animation_winner(void){
  PORTB = 0x3F; delay(500); // 00111111 tout allumer 
  PORTB = 0x15; delay(500); // 00010101 
  PORTB = 0x2A; delay(500); // 00101010 
  PORTB = 0x3F; delay(500); // 00111111
  PORTB = 0x00; delay(500); // 00000000
}

void animation_looser(void){
  byte i,k;
  for(k=0; k<=4; k++){
    for(i=0; i<6; i++){ PORTB = 1<<i; delay(50); }
    for(i=4; i>1; i--){ PORTB = 1<<i; delay(50); }
  }
}

/*  Explication des 1<<i 
 *   
 *  1 = 00000001 en binaire
 *  1<<i donne 1 poussé i fois
 *  1<<0 donne 00000001 (un 1 poussé  zéro fois vers la gauche)
 *  1<<3 donne 00001000 (un 1 poussé trois fois vers la gauche)
 */
