#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "lsm_dir.h"
#include "lsm_file.h"
#include "lsm_printer.h"

int main(int argc, char *argv[])
{
    lsm_dir_t **dirs = NULL;

    /* Command options */
    bool opt_display_hidden = false;
    bool opt_display_dots = true;
    bool opt_display_long_list = false; // -l

    int option;
    while ((option = getopt(argc, argv, "aAl")) != -1)
    {
        switch (option)
        {
        case 'a':
            opt_display_hidden = true;
            break;
        case 'A':
            opt_display_dots = false;
            break;
        case 'l':
            opt_display_long_list = true;
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
        if (!lsm_dir_read(dir))
        {
            perror("Error while reading directory");
            for (int i = 0; i < num_dirs; i++)
            {
                lsm_dir_destroy(dirs[i]);
            }
            free(dirs);
            free(final_msg);
            exit(EXIT_FAILURE);
        }

        n += strlen(dir->path_name) + 3;
        final_msg = realloc(final_msg, n);
        strcat(final_msg, dir->path_name);
        strcat(final_msg, ":\n");

        for (int j = 0; j < dir->num_files; j++)
        {
            lsm_file_t *file = dir->files[j];
            lsm_file_print(file);
            if (file->type == LSM_DIRECTORY)
            {
                if (opt_display_dots || (strcmp(file->name, ".") != 0 && strcmp(file->name, "..") != 0))
                {
                    n += strlen(file->name) + 1;
                    final_msg = realloc(final_msg, n);
                    strcat(final_msg, file->name);
                    strcat(final_msg, "\t");
                }
            }
            else if (file->type == LSM_FILE)
            {
                if (opt_display_hidden || file->name[0] != '.')
                {
                    n += strlen(file->name) + 1;
                    final_msg = realloc(final_msg, n);
                    strcat(final_msg, file->name);
                    strcat(final_msg, "\t");
                }
            }
        }

        n += 3;
        final_msg = realloc(final_msg, n);
        strcat(final_msg, "\n\n");
    }

    printf("%s", final_msg);
    free(final_msg);

    if (opt_display_long_list)
    {
        lsm_printer_display_long_list_output(opt_display_hidden, opt_display_dots, dirs, num_dirs);
    }

    for (int i = 0; i < num_dirs; i++)
    {
        lsm_dir_destroy(dirs[i]);
    }
    free(dirs);

    return 0;
}