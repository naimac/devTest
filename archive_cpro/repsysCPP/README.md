# reporter_messages

This project allows to translate the KEBA messages (class from 1 to 12)  by the SEPRO message (class 13 to 15) 

	see the confluence page for more information :
   http://vmjira/confluence/display/BEELP/5-+Reporter+Message	

Le projet est cense fonctionner dans un environnement docker ... pas su faire fonctionner perso
Le projet est prevu pour une compilation / utilisation en ligne de commande (exit Eclipse)

Pour compiler (ligne de commande) :
	make

Lancer l executable :
L executable s appelle reporter_message il est situe dans le dossier bin a la racine du projet mais un lien symbolique est fait
a la racine du dossier par le makefile. Il est donc inutile d'aller dans le dossier bin (le dossier bin est la pour organiser le projet)
Une fois la compilation reussie, il faut lancer ./reporter_message

Pour supprimer les .o et l'executable
	make clean

Pour recompiler (effacer tous les .o et l'executable puis compiler a nouveau)
	make re

Pour verifier envoi des messages avec lib keba bpApiRepSys :
ssh 172.16.11.23
tail -f /opt/kecontrol/protocol/pipeserver/OutputCtrl.txt | grep -i REPSYS

[ AVANT EXECUTION (si pas deja fait) !! ]

--> A la racine du projet, executer la commande : 
ls -l system/bp/lib/

--> Resultat attendu :
total 20
-rwxrwxrwx 1 bep bep 19908 Apr 29 17:39 libBPApi.so
lrwxrwxrwx 1 bep bep    11 Apr 30 13:58 libBPApi.so.2 -> libBPApi.soecho "\033[1;34m\n$@ available\033[1;0m\n"

--> si la lib libBPApi.so.2 n est pas presente, la creer
A la racine du projet faire :
cd system/bp/lib/
ln -s libBPApi.so libBPApi.so.2
