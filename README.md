# Projet 8 R-UDP

Description⬅️

Ce projet illustre la mise en œuvre d’un protocole de transmission fiable sur UDP (RUDP) et la simulation d’un protocole de fenêtre glissante.

Fonctionnalités principales
etudiant1.c
Définition de paquets RUDP (en-tête + payload).
Envoi d’un paquet et affichage du contenu.
etudiant2.c
Envoi d’un paquet sur UDP et attente d’un ACK.
Retransmission automatique en cas de timeout (perte détectée).
Simulation de plusieurs paquets avec affichage des retransmissions.
etudiant3.c (Serveur)
Simulation d’une fenêtre glissante pour l’envoi de paquets multiples.
Réception simulée des ACK avec probabilité d’échec (timeout).
Glissement de la fenêtre lorsque des ACK sont reçus.
Affichage complet des paquets envoyés, des ACK reçus et des retransmissions.


## Compilation

Pour compiler les fichiers sources C, utilisez les commandes suivantes :


gcc etudiant1.c -o etudiant

gcc etudiant2.c -o etudiant

gcc etudiant3.c -o etudiant


##Exécution

Pour exécuter les programmes executez la commande suivant:

./etudiant   # Exécuter le dernier fichier compilé

Notes sur les fichiers :◀️

etudiant1.c : Test de base de l’envoi d’un paquet RUDP avec affichage du contenu.
etudiant2.c : Envoi de paquets avec retransmission automatique en cas de perte détectée (timeout).
etudiant3.c : Simulation d’une fenêtre glissante et gestion des ACK. Ce fichier est considéré comme le serveur dans cette simulation.




Résultats typiques◀️

etudiant1 affiche un paquet unique :
Packet: seq=1, ack=0, type=1, length=5, payload=Hello

etudiant2 détecte les pertes et retransmet les paquets :
Perte détectée, retransmission du paquet 1

etudiant3 (serveur) affiche la fenêtre glissante et la gestion des ACK :
Envoi du paquet 0
Envoi du paquet 1
ACK reçu pour le paquet 0
Timeout pour le paquet 2
Envoi du paquet 2
...
Tous les paquets ont été envoyés et accusés.

Détails techniques⬅️
Utilisation de structures RUDP_Header et RUDP_Packet pour encapsuler les paquets.
Timeout configuré à 2 secondes pour la retransmission.
Sockets UDP (<sys/socket.h>, <arpa/inet.h>) utilisés pour la communication réseau.
Simulation autonome et tests en local sur 127.0.0.1 (localhost).

Remarques⚠️
Les fichiers peuvent servir de base pour un projet de protocole fiable ou pour l’étude des mécanismes RUDP.
L’exécution multiple écrase le fichier exécutable etudiant à chaque compilation, il est donc recommandé de renommer l’exécutable si besoin.
