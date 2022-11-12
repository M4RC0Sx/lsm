#ifndef _LSM_DIR_H_
#define _LSM_DIR_H_

#include <stdbool.h>

#include "lsm_file.h"

typedef struct
{
    char *path_name;
    lsm_file_t **files;
    int num_files;
} lsm_dir_t;

lsm_dir_t *lsm_dir_create(char *path_name);
void lsm_dir_destroy(lsm_dir_t *lsm_dir);
bool lsm_dir_read(lsm_dir_t *lsm_dir);

#endif