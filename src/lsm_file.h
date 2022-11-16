#ifndef _LSM_FILE_H_
#define _LSM_FILE_H_

#include <stdbool.h>
#include <time.h>

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
    bool is_hidden;
    bool is_dot;
    char *owner;
    char *group;
    long size;
    time_t last_modified_timestamp;
    char *perms_str;
    int hard_links_count;
} lsm_file_t;

lsm_file_t *lsm_file_create(char *name, char *path);
void lsm_file_destroy(lsm_file_t *lsm_file);
void lsm_file_print(lsm_file_t *lsm_file);

#endif