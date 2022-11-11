#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>

#include "lsm_dir.h"

int main(int argc, char *argv[])
{
    lsm_dir_t **dirs = NULL;

    /* Command options */
    bool opt_display_hidden = false;
    bool opt_display_dots = true;

    int option;
    while ((option = getopt(argc, argv, "aA")) != -1)
    {
        switch (option)
        {
        case 'a':
            opt_display_hidden = true;
            break;
        case 'A':
            opt_display_dots = false;
            break;
        default:
            break;
        }
    }

    int num_dirs = argc - optind;
    if (num_dirs > 0)
    {
        dirs = malloc(num_dirs * sizeof(lsm_dir_t *));
        for (int i = 0; i < num_dirs; i++)
        {
            dirs[i] = lsm_dir_create(argv[optind + i]);
        }
    }
    else
    {
        dirs = malloc(sizeof(lsm_dir_t *));
        dirs[0] = lsm_dir_create(".");
        num_dirs = 1;
    }

    // Print paths
    lsm_dir_t *dir = NULL;

    char *final_msg = malloc(1);
    final_msg[0] = '\0';
    int n = 0;
    for (int i = 0; i < num_dirs; i++)
    {
        dir = dirs[i];

        struct dirent *de;
        DIR *dr = opendir(dir->path_name);
        if (!dr)
        {
            perror("There was an error opening path!");
            exit(EXIT_FAILURE);
        }

        n += strlen(dir->path_name) + 3;
        final_msg = realloc(final_msg, n);
        strcat(final_msg, dir->path_name);
        strcat(final_msg, ":\n");
        while ((de = readdir(dr)) != NULL)
        {
            // Skip hidden files
            if (!opt_display_hidden && de->d_name[0] == '.')
                continue;

            // Skip . and ..
            if (!opt_display_dots && (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0))
                continue;

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

    for (int i = 0; i < num_dirs; i++)
    {
        lsm_dir_destroy(dirs[i]);
    }
    free(dirs);

    return 0;
}