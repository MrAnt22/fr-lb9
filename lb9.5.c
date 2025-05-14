#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int can_read(const char *filename) {
    	return access(filename, R_OK) == 0;
}

int can_write(const char *filename) {
    	return access(filename, W_OK) == 0;
}

int main() {
	const char *filename = "/tmp/tempfile_example2.txt";

    	FILE *fp = fopen(filename, "w");
    	if (!fp) {
        	perror("file");
        	return 1;
    	}
	fprintf(fp, "Temporary file");
	fclose(fp);
	printf("File: %s created\n", filename);

    	printf("to root\n");
    	char cmd[256];
    	snprintf(cmd, sizeof(cmd), "sudo chown root %s", filename);
    	system(cmd);

    	printf("to chmod 644\n");
    	snprintf(cmd, sizeof(cmd), "sudo chmod 644 %s", filename);
    	system(cmd);

    	printf("READING: %s\n", can_read(filename) ? "success" : "denied");
    	printf("WRITE:   %s\n", can_write(filename) ? "success" : "denied");

    	return 0;
}
