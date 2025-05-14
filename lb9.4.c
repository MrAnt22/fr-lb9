#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("whoami: \n");
    int status1 = system("whoami");
    if (status1 == -1) {
        perror("error whoami");
        return 1;
    }

    printf("\nid: \n");
    int status2 = system("id");
    if (status2 == -1) {
        perror("error id");
        return 1;
    }

    return 0;
}
