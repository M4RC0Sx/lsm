#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "lsm_file.h"
#include "lsm_dir.h"

lsm_dir_t *lsm_dir_create(char *path_name)
{
    lsm_dir_t *lsm_dir = malloc(sizeof(lsm_dir_t));

    lsm_dir->path_name = malloc(strlen(path_name) + 1);
    strcpy(lsm_dir->path_name, path_name);

    lsm_dir->files = NULL;
    lsm_dir->num_files = 0;

    return lsm_dir;
}

void lsm_dir_destroy(lsm_dir_t *lsm_dir)
{
    free(lsm_dir->path_name);

    for (int i = 0; i < lsm_dir->num_files; i++)
        lsm_file_destroy(lsm_dir->files[i]);

    free(lsm_dir->files);
    free(lsm_dir);
}

bool lsm_dir_read(lsm_dir_t *lsm_dir)
{

    struct dirent *de;
    DIR *dr = opendir(lsm_dir->path_name);
    if (!dr)
        return false;

    while ((de = readdir(dr)) != NULL)
    {

        char *file_name = de->d_name;
        char *file_path = malloc(strlen(lsm_dir->path_name) + strlen(file_name) + 2);
        sprintf(file_path, "%s/%s", lsm_dir->path_name, file_name);

        lsm_file_t *file = lsm_file_create(file_name, file_path);
        lsm_dir->files = realloc(lsm_dir->files, sizeof(lsm_file_t *) * (lsm_dir->num_files + 1));
        lsm_dir->files[lsm_dir->num_files] = file;
        lsm_dir->num_files++;

        free(file_path);
    }

    closedir(dr);
    return true;
}