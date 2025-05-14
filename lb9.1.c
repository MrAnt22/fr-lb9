#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#define UID_THRESHOLD 1000
#define LINE_LEN 1024

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[LINE_LEN];
    char *username;
    int uid;
    int current_uid = getuid();

    printf("Regular users (UID > %d):\n", UID_THRESHOLD);

    while (fgets(line, sizeof(line), fp)) {
        char *saveptr;
        username = strtok_r(line, ":", &saveptr);
        strtok_r(NULL, ":", &saveptr);
        char *uid_str = strtok_r(NULL, ":", &saveptr);  

        if (uid_str) {
            uid = atoi(uid_str);
            if (uid >= UID_THRESHOLD && uid != current_uid) {
                printf("- %s (UID: %d)\n", username, uid);
            }
        }
    }

    pclose(fp);
    return 0;
}
