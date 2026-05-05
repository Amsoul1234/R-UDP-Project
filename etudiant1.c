#include <stdint.h>
#include <stdio.h>

// Définition des types de messages
#define TYPE_DATA 1
#define TYPE_ACK  2
#define TYPE_SYN  3
#define TYPE_FIN  4

typedef struct {
    uint32_t seq_num;    // Numéro de séquence pour l'ordre
    uint32_t ack_num;    // Numéro d'accusé de réception
    uint8_t  type;       // Type du paquet (DATA, ACK, etc.)
    uint16_t length;     // Taille des données dans le payload
} RUDP_Header;

typedef struct {
    RUDP_Header header;
    char payload[1024];  // Données utiles
} RUDP_Packet;

int main() {
    RUDP_Packet pkt;
    pkt.header.seq_num = 1;
    pkt.header.ack_num = 0;
    pkt.header.type = TYPE_DATA;
    pkt.header.length = 5;
    snprintf(pkt.payload, sizeof(pkt.payload), "Hello");

    printf("Packet: seq=%u, ack=%u, type=%u, length=%u, payload=%s\n",
           pkt.header.seq_num,
           pkt.header.ack_num,
           pkt.header.type,
           pkt.header.length,
           pkt.payload);

    return 0;
}
