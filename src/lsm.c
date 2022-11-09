#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int option;
    char *path = NULL;
    while ((option = getopt(argc, argv, "a")) != -1)
    {
        switch (option)
        {
        case 'a':
            printf("OPTION a\n");
            break;
        default:
            break;
        }
    }

    path = argv[optind];
    if (!path)
    {
        fprintf(stderr, "No directory specified!\n");
        exit(EXIT_FAILURE);
    }

    struct dirent *de;
    DIR *dr = opendir(path);

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