#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
	mkfifo("stc", 0644);
	printf("Client created pipe\n");

	int cts = open("cts", O_WRONLY);
	printf("Client connected to server\n");

	write(cts, "stc", 10);
	printf("Sent stc pipe\n");
	printf("Waiting for Connection ...\n");

	int stc = open("stc", O_RDONLY);
	printf("Server connected\n");

	remove("stc");
	printf("Removed pipe\n");

	char confirm[100];
	read(stc, confirm, sizeof(confirm));
	printf("Received confirmation: %s\n", confirm);

	write(cts, confirm, sizeof(confirm));
	printf("Sent confirmation\n");
	printf("Done\n");

	char in[100];
	char out[100];

	while (1) {
		printf("Input: ");

		scanf("%s", in);
		write(cts, &in, sizeof(in));
		read(stc, &out, sizeof(out));

		printf("Reversed: %s\n\n", out);
	}

	return 0;
}
