#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define TYPE_DATA 1
#define TYPE_ACK  2

typedef struct {
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t  type;
    uint16_t length;
} RUDP_Header;

typedef struct {
    RUDP_Header header;
    char payload[1024];
} RUDP_Packet;

// Fonction pour préparer le prochain paquet (exemple minimal)
void preparer_prochain_paquet(RUDP_Packet *pkt, uint32_t seq) {
    pkt->header.seq_num = seq;
    pkt->header.ack_num = 0;
    pkt->header.type = TYPE_DATA;
    snprintf(pkt->payload, sizeof(pkt->payload), "Paquet %u", seq);
    pkt->header.length = strlen(pkt->payload);
}

int main() {
    int sockfd;
    struct sockaddr_in dest_addr;
    fd_set readfds;
    struct timeval timeout;
    RUDP_Packet mon_paquet, ack_paquet;
    int donnees_a_envoyer = 1;
    uint32_t seq = 1;

    // Création du socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &dest_addr.sin_addr);

    preparer_prochain_paquet(&mon_paquet, seq);

    while (donnees_a_envoyer) {
        // Envoi initial
        if (sendto(sockfd, &mon_paquet, sizeof(mon_paquet), 0,
                   (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("sendto");
        }

        // Attente de l'ACK avec timeout
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        timeout.tv_sec = 2;  // 2 secondes
        timeout.tv_usec = 0;

        int rv = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

        if (rv == 0) {
            // TIMEOUT : Retransmission
            printf("Perte détectée, retransmission du paquet %d\n", mon_paquet.header.seq_num);
            continue; // Repart au début de la boucle pour renvoyer le même paquet
        } else if (rv > 0) {
            socklen_t addrlen = sizeof(dest_addr);
            if (recvfrom(sockfd, &ack_paquet, sizeof(ack_paquet), 0,
                         (struct sockaddr *)&dest_addr, &addrlen) < 0) {
                perror("recvfrom");
            }

            if (ack_paquet.header.ack_num >= mon_paquet.header.seq_num) {
                // Succès : Passage au paquet suivant
                seq++;
                preparer_prochain_paquet(&mon_paquet, seq);
            }
        }

        if (seq > 5) { // exemple : on arrête après 5 paquets
            donnees_a_envoyer = 0;
        }
    }

    close(sockfd);
    return 0;
}
