#include <stdlib.h>
#include <string.h>

#include "lsm_dir.h"

lsm_dir_t *lsm_dir_create(char *path_name)
{
    lsm_dir_t *dir = malloc(sizeof(lsm_dir_t));

    dir->path_name = malloc(strlen(path_name) + 1);
    strcpy(dir->path_name, path_name);

    return dir;
}

void lsm_dir_destroy(lsm_dir_t *dir)
{
    free(dir->path_name);
    free(dir);
}