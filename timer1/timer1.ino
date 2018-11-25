
void setup() {
   Serial.begin(9600);
   // Programmation du timer 1 (un timer 16 bits)
   // mode normal WGM13=WGM12=WGM11=WGM10=0
   // prédivision/1024 CS12=1 CS11=0 CS10=1 
   // bits de TCCR1A : COM1A1 COM1A0 COM1B1 COM1B0 NU NU WGM11 WGM10 
   // bits de TCCR1B : ICNC1 ICES1 NU WGM13 WGM12  CS12  CS11 CS10 
   //---- initialisation du timer1 en simple compteur ---------
   TCCR1B = 0x00; // 00000000 bloquage du timer
   TCNT1 = 0x0000;// on comptera à partir de zéro
   TCCR1A = 0x00; // 00000000
   TCCR1B = 0x05; // 00000101 lancement et prédivision par 1024
   //---- fin initialisation du timer1 ------------------------

  //----- affichage des frequences et des periodes --------
  Serial.print("Frequence d'entree du compteur : fe = 16Mz/1024 = ");
  uint32_t fe = 16000000L/1024; 
  Serial.print(fe);
  Serial.println(" Hz" );

  Serial.print("Periode d'entree : pe = " );
  float pe = 1000000.0/(float)fe;
  Serial.print(pe);
  Serial.println(" micro secondes" );
  
  Serial.print("Micro secondes avant d'atteindre 0xFFFF = pe*65535 = " );
  Serial.println(pe*65535.0);

  Serial.print("Secondes avant d'atteindre 0xFFFF = pe*65535/1000000 = " );
  Serial.print(pe*65535.0/1000000.0);
  Serial.println(" s\n" );
}

uint16_t tcnt = 0;
uint32_t total= 0;

void loop(){
    //---- lire le compteur avant qu'il ne deborde (son max est 65535)
    tcnt = TCNT1; // on enregistre la valeur courante écoulée
    TCNT1 = 0;    // on recommence à compter des 64µs à partir de zéro
    total = total + tcnt; // on ajoute le temps écoulé au total
    
    //---- affichage 
    Serial.print( "Nombre de periodes d'entree ecoulees = " );
    Serial.println( total );
    Serial.print( "               soit en microsecondes : ");
    Serial.println( total*64 );
    Serial.print( "               soit en secondes : ");
    Serial.println( total*64/1000000 );
    delay(1000); // on ne dois pas attendre plus de 4 secondes sinon ... !
}
