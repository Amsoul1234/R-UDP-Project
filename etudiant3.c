#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_PAQUETS 10
#define WINDOW_SIZE 4
#define TIMEOUT_SEC 2

// Simule l'envoi d'un paquet
void envoyer_paquet(int seq) {
    printf("Envoi du paquet %d\n", seq);
}

// Simule l'attente d'un ACK avec timeout
// Retourne 1 si ACK reçu, 0 si timeout
int attendre_ack(int *ack_recu, int base) {
    // Simulation aléatoire : 80% de chances de recevoir un ACK
    if (rand() % 10 < 8) {
        *ack_recu = base; // on reçoit l'ACK du paquet 'base'
        printf("ACK reçu pour le paquet %d\n", *ack_recu);
        return 1;
    } else {
        printf("Timeout pour le paquet %d\n", base);
        return 0;
    }
}

int main() {
    srand(time(NULL));

    int base = 0;
    int next_seq = 0;

    while (base < TOTAL_PAQUETS) {
        // Envoyer les paquets tant que la fenêtre n'est pas pleine
        while (next_seq < base + WINDOW_SIZE && next_seq < TOTAL_PAQUETS) {
            envoyer_paquet(next_seq);
            next_seq++;
        }

        // Attendre un ACK avec un timeout (simulé)
        int ack_recu;
        if (attendre_ack(&ack_recu, base)) {
            if (ack_recu >= base) {
                base = ack_recu + 1; // La fenêtre glisse
            }
        } else {
            // TIMEOUT : On recommence à partir de 'base'
            next_seq = base;
        }

        // Petite pause pour mieux voir la simulation
        sleep(1);
    }

    printf("Tous les paquets ont été envoyés et accusés.\n");
    return 0;
}
