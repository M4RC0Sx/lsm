#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    struct dirent *de;
    DIR *dr = opendir("/etc");

    char *final_msg = malloc(1);
    final_msg[0] = '\0';

    int n = 0;
    while ((de = readdir(dr)) != NULL)
    {
        // Append the file name to the message
        n += strlen(de->d_name) + 2;
        final_msg = realloc(final_msg, n);
        strcat(final_msg, de->d_name);
        strcat(final_msg, "\t");
    }
    closedir(dr);

    printf("%s\n", final_msg);
    free(final_msg);
    return 0;
}