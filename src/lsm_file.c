#include <stdlib.h>
#include <string.h>

#include "lsm_file.h"

static char *lsm_file_get_ext(lsm_file_t *lsm_file);

lsm_file_t *lsm_file_create(char *file_name, char *file_path, lsm_file_type_t file_type)
{
    lsm_file_t *file = malloc(sizeof(lsm_file_t));

    file->name = malloc(strlen(file_name) + 1);
    strcpy(file->name, file_name);

    file->path = malloc(strlen(file_path) + 1);
    strcpy(file->path, file_path);

    file->type = file_type;
    file->extension = lsm_file_get_ext(file);

    return file;
}

void lsm_file_destroy(lsm_file_t *lsm_file)
{
    free(lsm_file->name);
    free(lsm_file->path);
    free(lsm_file);
}

static char *lsm_file_get_ext(lsm_file_t *lsm_file)
{
    if (lsm_file->type != LSM_FILE)
        return NULL;

    char *ext = strrchr(lsm_file->name, '.');
    if (ext)
        return ext + 1;
    else
        return NULL;
}