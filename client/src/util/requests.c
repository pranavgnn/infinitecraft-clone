#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#include "requests.h"

// #pragma comment(lib, "Ws2_32.lib")

int initialize_winsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }
    return 0;
}

SOCKET createSocket() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
    }
    return sock;
}

int connect_to_server(SOCKET sock, const char *hostname) {
    struct addrinfo *result = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(hostname, "80", &hints, &result) != 0) {
        printf("getaddrinfo failed\n");
        WSACleanup();
        return 1;
    }

    if (connect(sock, result->ai_addr, (int) result->ai_addrlen) == SOCKET_ERROR) {
        printf("Failed to connect to server\n");
        freeaddrinfo(result);
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);
    return 0;
}

void send_http_request(SOCKET sock, const char *hostname, const char *path) {
    char request[512];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, hostname);

    if (send(sock, request, strlen(request), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
    }
}

void receive_response(SOCKET sock, char **resp) {
    char response[4096];
    int received;

    do {
        received = recv(sock, response, sizeof(response) - 1, 0);
        if (received > 0) {
            response[received] = '\0';
            printf("Response:\n%s\n", response);
            strcpy(*resp, response);
        } else if (received == 0) {
            printf("Connection closed\n");
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
        }
    } while (received > 0);
}

void cleanup(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

char* requestGET(const char* url) {
    char hostname[256];
    char path[256];
    char *response = (char*) malloc(4096 * sizeof(char));

    sscanf(url, "http://%255[^/]/%255[^\n]", hostname, path);

    initialize_winsock();
    SOCKET sock = createSocket();
    connect_to_server(sock, hostname);
    send_http_request(sock, hostname, path);
    receive_response(sock, &response);
    cleanup(sock);

    return response;
}