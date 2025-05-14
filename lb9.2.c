#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Effective UID: %d\n", geteuid());
    printf("Default UID: %d\n", getuid());

    FILE *f = fopen("/etc/shadow", "r");
    if (f == NULL) {
        perror("fopen");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    fclose(f);
    return 0;
}
