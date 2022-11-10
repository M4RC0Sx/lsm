#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int option;
    char **paths = NULL;
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

    int num_paths = argc - optind;
    if (num_paths > 0)
    {
        paths = malloc(num_paths * sizeof(char *));
        for (int i = 0; i < num_paths; i++)
        {
            paths[i] = argv[optind + i];
        }
    }
    else
    {
        paths = malloc(sizeof(char *));
        paths[0] = ".";
        num_paths = 1;
    }

    // Print paths
    char *path = NULL;

    char *final_msg = malloc(1);
    final_msg[0] = '\0';
    int n = 0;
    for (int i = 0; i < num_paths; i++)
    {
        path = paths[i];

        struct dirent *de;
        DIR *dr = opendir(path);
        if (!dr)
        {
            perror("There was an error opening path!");
            exit(EXIT_FAILURE);
        }

        n += strlen(path) + 3;
        final_msg = realloc(final_msg, n);
        strcat(final_msg, path);
        strcat(final_msg, ":\n");
        while ((de = readdir(dr)) != NULL)
        {
            // Append the file name to the message
            n += strlen(de->d_name) + 2;
            final_msg = realloc(final_msg, n);
            strcat(final_msg, de->d_name);
            strcat(final_msg, "\t");
        }
        closedir(dr);

        n += 3;
        final_msg = realloc(final_msg, n);
        strcat(final_msg, "\n\n");
    }

    printf("%s", final_msg);
    free(final_msg);

    free(paths);

    return 0;
}