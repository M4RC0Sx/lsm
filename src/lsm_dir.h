#ifndef _LSM_DIR_H_
#define _LSM_DIR_H_

typedef struct
{
    char *path_name;
} lsm_dir_t;

lsm_dir_t *lsm_dir_create(char *path_name);
void lsm_dir_destroy(lsm_dir_t *dir);

#endif