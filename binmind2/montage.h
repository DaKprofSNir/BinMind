/*
-----------Presentation -----------------------------------
Bindmind est un jeu de binaire.

Le but est de trouver le code hexadécimal (zéro à F) affiché en binaire.

Le jeu affiche un code en binaire.
   Bit allumé = bit à 1
   Bit clignotant = bit à zéro
Pour gagner vous devez envoyer la lettre [0123456789ABCDEF] qui correspond au code.

-------- Montage -------------------------------------------
La barre LED se connecte des broches 8 jusqu'au GND
Le bit 0 du nombre à deviner apparait sur le port B bit zéro (broche 8 Arduino)
Le bit 1 du nombre à deviner apparait sur le port B bit 1 (broche 9)
Le bit 2 du nombre à deviner apparait sur le port B bit 2 (broche 10)
Le bit 3 du nombre à deviner apparait sur le port B bit 3 (broche 11)
Pour lire le code il faut donc regarder l'Arduino prise USB vers la gauche

-------- Versions ---------------------------------------
Bindmind1
Utilisation du port parallèle + port USART

Bindmind2
Utilisation du port parallele + USART + Timer
On ajoute un timer pour mesurer votre niveau de rapidité pour trouver la solution

*/
