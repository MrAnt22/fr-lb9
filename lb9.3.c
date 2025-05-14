#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/stat.h>

int main() {
    const char *orig_file = "/tmp/testfile.txt";
    struct passwd *pw = getpwuid(getuid());
    const char *home = pw->pw_dir;
    char dest_file[512];
    snprintf(dest_file, sizeof(dest_file), "%s/testfile_copy.txt", home);

    FILE *f = fopen(orig_file, "w");
    if (!f) {
        perror("Cannot create file");
        return 1;
    }
    fprintf(f, "Original content\n");
    fclose(f);
    printf("Created file %s\n", orig_file);

    printf("Copying file to home directory using sudo (root)\n");
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "sudo cp %s %s", orig_file, dest_file);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "sudo chown %s:%s %s", pw->pw_name, pw->pw_name, dest_file);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "chmod u+rw %s", dest_file);
    system(cmd);

    printf("Trying to modify the file as a normal user...\n");
    f = fopen(dest_file, "a");
    if (!f) {
        perror("Cannot modify file");
    } else {
        fprintf(f, "User modification attempt\n");
        fclose(f);
        printf("Modification succeeded (unexpected)\n");
    }

    printf("Trying to delete the file as a normal user...\n");
    if (remove(dest_file) != 0) {
        perror("Cannot delete file");
    } else {
        printf("File deleted successfully (unexpected)\n");
    }

    return 0;
}
