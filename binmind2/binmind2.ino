// Auteur DaK nov 2018
// pour le montage => voir montage.h

void setup(){
    //--------- initialisation du barre LED sur le port B ----------
    DDRB  = 0x3F; // 0011 1111 6 bits en sortie car 6 LEDs
    PORTB = 0x3F; // 0011 1111 on allume les 6 LEDs
    //---------- Initialisation de l'USART --------------------------
    UCSR0A = 0x00; // reset status + vitesse non doublée
    UCSR0C = 0x0E; // 00001110 8 bits de données, 1 start, 2 stop, pas de parité, mode asynchrone.
    UBRR0L = 0x68; // 9600Bds poid faible de (SysClock / (16 * bauds)) -1
    UBRR0H = 0x00; // 9600Bds poid fort de (SysClock / (16 * bauds)) -1
    UCSR0B = 0x18; // 00011000 Autoriser Réception + Emission
    //---------- Initialisation du timer1 mode normal --------------
    TCCR1B = 0x00; // 00000000 bloquage du timer
    TCNT1 = 0x0000;// on comptera à partir de zéro
    TCCR1A = 0x00; // 00000000
    TCCR1B = 0x__; // 00000101 lancement et prédivision par 1024
    //---- petite danse des LEDs avant de commencer un nouveau jeu
    animation_winner();
}//setup()

//---- déclaration des variables
uint16_t tcnt = 0;
uint32_t total= 0;

void loop(){
  byte nombre=0, reponse=0;
  boolean win=false;

  //---- Tirer un nombre en lisant le registre de comptage du timer zéro ----
  nombre = TCNT0;         // choisir un nombre au hasard (dans le compteur du timer0)
  nombre = nombre & 0x0F; // ne garder que les 4 bits de poid faible
  PORTB  = nombre;        // afficher ce nombre sur la barre LED

  //----- remettre le timer1 à zéro au début de chaque jeu
  total = 0;
  TCNT1 = 0;
  
  while( not win ){
    //---- lire le compteur avant qu'il ne deborde (son max est 65535)
    ?
    ?
    ?
    
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
  if( total>00100000 ) PORTB = 0x3F; delai(500); // 00111111 Grand maître
  if( total>00500000 ) PORTB = 0x1F; delai(500); // 00011111 Expert
  if( total>01000000 ) PORTB = 0x0F; delai(500); // 00001111 Chapeau
  if( total>05000000 ) PORTB = 0x07; delai(500); // 00000111 Pas mal du tout
  if( total>07500000 ) PORTB = 0x03; delai(500); // 00000011 Peut mieux faire
  if( total>10000000 ) PORTB = 0x01; delai(500); // 00000001 Petit joueur
  if( total>20000000 ) PORTB = 0x00; delai(500); // 00000000 Débutant
  delay(10000);
  
}//loop()

