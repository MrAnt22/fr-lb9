#include <stdio.h>
#include <stdlib.h>

int main() {
    int status = system("sudo /bin/cat /etc/shadow");
    if (status == -1) {
        perror("system");
        return 1;
    }
    return 0;
}
