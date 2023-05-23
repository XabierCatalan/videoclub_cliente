
#include <stdio.h>
#include <winsock2.h>
#include "cliente.h"
#include "Pelicula.h"


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
WSADATA wsaData;
SOCKET s;
struct sockaddr_in server;
char sendBuff[512], recvBuff[512];

char menuSesion(){
	printf("\n");
	printf("Elige una OPCION: \n");
	printf("1. Iniciar Sesión \n");
	printf("2. Salir \n");
	printf("Opcion: ");
	fflush(stdout);
	char opcion = getchar();

	char c; while ((c = getchar()) != '\n' && c != EOF);

	return opcion;
}
char menuPrincipal(){
	printf("\n");
	printf("Elige una OPCION: \n");
	printf("1. VerPelis \n");
	printf("2. Comprar \n");
	printf("3. Salir \n");
	printf("Opcion: ");
	fflush(stdout);
	char opcion = getchar();

	char c; while ((c = getchar()) != '\n' && c != EOF);

	return opcion;
}

char* escribirNombre(){
	printf("Escribe tu nombre: \n");
	fflush(stdout);
	char* opcion = new char[20];
	scanf("%s", opcion);
	return opcion;
}
char* escribirContra(){
	printf("Escribe tu contra: \n");
	fflush(stdout);
	char* opcion = new char[20];
	scanf("%s", opcion);
	return opcion;
}

void menu(){
	char c;
		do
		{
			c = menuPrincipal();
			if (c == '1')
			{
				// SENDING command SUMAR and parameters to the server
				strcpy(sendBuff, "VERPELIS");
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, "VERPELISEND");
				send(s, sendBuff, sizeof(sendBuff), 0);

				// RECEIVING response to command SUMAR from the server
				recv(s, recvBuff, sizeof(recvBuff), 0);
				int numP = atoi(recvBuff);
				Pelicula* listaPelis = new Pelicula[numP];
				int id_pelicula;
				char *titulo;
				char *genero;
				char *director;
				char *formato;
				float precio;
				int cantidad;
				for (int i = 0; i < numP; ++i) {
					recv(s, recvBuff, sizeof(recvBuff), 0);
					id_pelicula=atoi(recvBuff);
					recv(s, recvBuff, sizeof(recvBuff), 0);
					titulo=recvBuff;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					genero=recvBuff;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					director=recvBuff;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					formato=recvBuff;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					precio=atof(recvBuff);
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cantidad=atoi(recvBuff);
					Pelicula peli(id_pelicula, titulo, genero, director, formato, precio, cantidad);
					listaPelis[i]=peli;
					peli.imprimirPeli();
				}
				printf("Suma = %s \n", recvBuff);
				fflush(stdout);
			}

			if (c == '2')
			{
				// SENDING command RAIZ and parameter to the server
				strcpy(sendBuff, "RAIZ");
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, "9");
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, "RAIZ-END");
				send(s, sendBuff, sizeof(sendBuff), 0);

				// RECEIVING response to command RAIZ from the server
				recv(s, recvBuff, sizeof(recvBuff), 0);
				printf("Raiz cuadrada = %s \n", recvBuff);
				fflush(stdout);
			}

			if (c == '3')
			{
				// SENDING command IP
				strcpy(sendBuff, "IP");
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, "IP-END");
				send(s, sendBuff, sizeof(sendBuff), 0);

				// RECEIVING response to command IP from the server
				recv(s, recvBuff, sizeof(recvBuff), 0);
				printf("IP del servidor = %s \n", recvBuff);
				fflush(stdout);
			}

			if (c == '4')
			{
				// SENDING command EXIT
				strcpy(sendBuff, "EXIT");
				send(s, sendBuff, sizeof(sendBuff), 0);
			}
		}while(c != '4');
}


int main(int argc, char *argv[])
{



	printf("\nInitialising Winsock...\n");
	fflush(stdout);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");
	fflush(stdout);
	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		fflush(stdout);
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");
	fflush(stdout);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Connection error: %d", WSAGetLastError());
		fflush(stdout);
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));
	fflush(stdout);
	//SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	char d;
	char* n;
	char* h;
		do
		{
			d = menuSesion();
			if (d == '1')
			{
				// SENDING command SUMAR and parameters to the server
				strcpy(sendBuff, "INICIARSESION");
				send(s, sendBuff, sizeof(sendBuff), 0);
				n=escribirNombre();
				strcpy(sendBuff, n);
				send(s, sendBuff, sizeof(sendBuff), 0);
				h=escribirContra();
				strcpy(sendBuff, h);
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, "SESIONEND");
				send(s, sendBuff, sizeof(sendBuff), 0);

				// RECEIVING response to command SUMAR from the server
				recv(s, recvBuff, sizeof(recvBuff), 0);
				printf("Response enviadda: %s \n", recvBuff);
				if(strcmp(recvBuff, "1")==0){
					printf("El usuario es correcto\n");
					menu();
				} else {
					printf("El usuario es incorrecto\n");
				}

				fflush(stdout);
			}


			if (d == '2')
			{
				// SENDING command EXIT
				strcpy(sendBuff, "EXIT");
				send(s, sendBuff, sizeof(sendBuff), 0);
			}
		}while(d != '2');

		// CLOSING the socket and cleaning Winsock...
		closesocket(s);
		WSACleanup();

		return 0;





	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}


