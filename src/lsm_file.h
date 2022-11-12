#ifndef _LSM_FILE_H_
#define _LSM_FILE_H_

typedef enum
{
    LSM_FILE,
    LSM_DIRECTORY,
    UNKNOWN
} lsm_file_type_t;

typedef struct
{
    char *name;
    char *path;
    lsm_file_type_t type;
    char *extension;
} lsm_file_t;

lsm_file_t *lsm_file_create(char *name, char *path, lsm_file_type_t type);
void lsm_file_destroy(lsm_file_t *lsm_file);

#endif