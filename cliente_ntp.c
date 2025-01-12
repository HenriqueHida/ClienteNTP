#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

#define TAM_PACOTE_NTP 48 // Tamanho do pacote NTP
#define TIMEOUT 20 // Timeout para o socket em segundos
#define TIMESTAMP 2208988800ULL // Delta de timestamp NTP para Unix

int main(int argc, char *argv[])
{
    if (argc != 2) { // Verifica se o endereco IP do servidor NTP foi fornecido
        printf("Falta o endereco IP do servidor NTP.\n");
        return 1;
    }

    const char *ntp_server = argv[1]; // Endereco do servidor NTP
    int udpSocket; // Descritor do socket UDP
    struct sockaddr_in server_addr; // Estrutura para endereco do servidor NTP
    uint8_t pacote[TAM_PACOTE_NTP] = {0}; // Pacote NTP
    struct timeval timeout; // Timeout do socket

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0); // Cria o socket UDP
    if (udpSocket < 0) { 
        perror("Erro ao criar socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr)); // Inicializa a estrutura do servidor
    server_addr.sin_family = AF_INET; // Configura o protocolo de endereco IPv4
    server_addr.sin_port = htons(123); // Porta padrao do NTP
    if (inet_pton(AF_INET, ntp_server, &server_addr.sin_addr) <= 0) { // Converte o endereco IP
        perror("Erro ao converter endereco IP");
        close(udpSocket);
        return 1;
    }

    timeout.tv_sec = TIMEOUT; // Configura o timeout em segundos
    timeout.tv_usec = 0; // Sem fracoes de segundo
    if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) { // Configura timeout
        perror("Erro ao configurar timeout");
        close(udpSocket);
        return 1;
    }

    pacote[0] = 0x1B; // Define o primeiro byte do pacote NTP

    if (sendto(udpSocket, pacote, TAM_PACOTE_NTP, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) { // Envia o pacote
        perror("Erro ao enviar pacote");
        close(udpSocket);
        return 1;
    }

    socklen_t addr_len = sizeof(server_addr); // Tamanho do endereco do servidor
    if (recvfrom(udpSocket, pacote, TAM_PACOTE_NTP, 0, (struct sockaddr*)&server_addr, &addr_len) < 0) { // Recebe a resposta
        perror("Erro ao receber pacote");
        close(udpSocket);
        return 1;
    }

    close(udpSocket); // Fecha o socket

    uint32_t segundos_desde_1900; // Segundos desde 1900
    memcpy(&segundos_desde_1900, &pacote[40], sizeof(segundos_desde_1900));
    segundos_desde_1900 = ntohl(segundos_desde_1900) - TIMESTAMP; // Converte para Unix timestamp

    time_t tempo_atual = (time_t)segundos_desde_1900; // Converte para o tempo atual
    printf("Hora atual: %s", ctime(&tempo_atual)); // Exibe o tempo

    return 0;
}

