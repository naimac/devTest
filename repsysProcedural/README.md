# reporter_messages

This project allows to translate the KEBA messages (class from 1 to 1)  by the SEPRO message (class 13 to 15) 

Le projet ne fonctionne pas dans un environnement docker

Pour compiler :
	make

Lancer l executable :
L executable s appelle reporter_message il est situe dans le dossier bin a la racine du projet
Le makefile fait un lien symbolique vers ce binaire directement dans le dossier root, il est donc inutile d'aller dans le dossier bin
Une fois la compilation reussie, il faut lancer ./reporter_message

Pour supprimer les .o et l'executable
	make clean

Pour recompiler (effacer tous les .o et l'executable puis compiler a nouveau)
	make re

Pour verifier envoi des messages avec lib keba bpApiRepSys :
ssh 172.16.11.23
tail -f /tmp/OutputCtrl.txt/

[ AVANT EXECUTION !! ]

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

NB : JE NE SAIS PAS POURQUOI IL CHER UN libBPApi.so.2 ... peut etre une mauvaise manip sur mon system
