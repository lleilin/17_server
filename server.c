#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void reverse(char *buffer){
	int len = strlen(buffer);

	for (int i = 0, j = len - 1; i < j; i++, j--) {
		char ch = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = ch;
	}
}

int main() {
	while (1) {
		mkfifo("cts", 0644);
		printf("Server created\n");
		printf("Waiting for client...\n");

		int cts = open("cts", O_RDONLY);
		printf("Connecting...\n");

		char name[128];
		read(cts, name, sizeof(name));
		printf("Received client name: %s\n", name);

		remove("cts");
		printf("cts removed\n");

		int stc = open("stc", O_WRONLY);
		printf("Connected to client\n");

		write(stc, "confirm", 8);
		printf("Confirmation sent\n");

		char confirm[128];
		read(cts, confirm, sizeof(confirm));
		printf("Received Confirmation: %s\n", confirm);

		char input[128];

		while (read(cts, &input, sizeof(input))) {
			reverse(input);
			write(stc, &input, sizeof(input));
		}
	}
}
