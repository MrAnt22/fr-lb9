#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>

void list_directory(const char *path) {
    printf("\n Catalog: %s\n", path);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls -l %s", path);
    system(cmd);
}

void check_access(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    char fullpath[512];

    int count = 0;
    while ((entry = readdir(dir)) != NULL && count < 5) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        printf("\nfile: %s\n", fullpath);
        printf("Reading: %s\n", access(fullpath, R_OK) == 0 ? "success" : "denied");
        printf("Writing:   %s\n", access(fullpath, W_OK) == 0 ? "success" : "denied");
        printf("Proceeding: %s\n", access(fullpath, X_OK) == 0 ? "success" : "denied");

        count++;
    }

    closedir(dir);
}

int main() {
    const char *home = getenv("HOME");

    const char *paths[] = {
        home,
        "/usr/bin",
        "/etc"
    };

    for (int i = 0; i < 3; i++) {
        list_directory(paths[i]);
        check_access(paths[i]);
    }

    return 0;
}
