// Auteur DaK nov 2018
// pour le montage => voir montage.h

void setup(){
    //--------- initialisation du barre LED sur le port B ----------
    DDRB  = 0x__; // 0011 1111 6 bits en sortie car 6 LEDs
    PORTB = 0x3F; // 0011 1111 on allume les 6 LEDs
    //---------- Initialisation de l'USART --------------------------
    UCSR0A = 0x00; // reset status + vitesse non doublée
    UCSR0C = ____; // 00001110 8 bits de données, 1 start, 2 stop, pas de parité, mode asynchrone.
    UBRR0L = ____; // 9600Bds poid faible de (SysClock / (16 * bauds)) -1
    UBRR0H = ____; // 9600Bds poid fort de (SysClock / (16 * bauds)) -1
    UCSR0B = 0x18; // 00011000 Autoriser Réception + Emission
    //---- petite danse des LEDs avant de commencer un nouveau jeu
    animation_winner();
}//setup()


void loop(){
  byte nombre=0, reponse=0;
  boolean win=false;

  //---- Tirer un nombre en lisant le registre de comptage du timer zéro ----
  nombre = TCNT0;         // choisir un nombre au hasard (dans le compteur du timer0)
  nombre = nombre & 0x0F; // ne garder que les 4 bits de poid faible
  PORTB  = nombre;        // afficher ce nombre sur la barre LED
  
  while( not win ){
    //--- Afficher le nombre à convertir en hexa ----
    PORTB = 0x0F;   delay( 1); // les 0 vont briller léger
    PORTB = nombre; delay(24); // les 1 vont briller au max
    
    //---- lire la réponse du joueur dans l'USART
    if( (UCSR0A & 0x80) != 0 ){ // on a reçu un caractère
        reponse = UDR0; // lecture du registre d'entrée de l'USART
        UDR0 = reponse; // écho de la réponse vers le moniteur série
        // le joueur envoie un code ASCII dans 0123456789ABCDEF
        win = (reponse ==  nombre+'0' )    // true si bonne réponse était dans '0' .. '9'
           || (reponse ==  nombre-10+'A')  // true si bonne réponse était dans 'A' .. 'F'
           || (reponse ==  nombre-10+'a'); // true si bonne réponse était dans 'a' .. 'a'
        if( not win )animation_looser();
    }
  }//while( not win )

  //---- si on arrive ici c'est qu'on a gagné
  animation_winner();
  
}//loop()

