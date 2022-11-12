#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

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
        struct stat buf_st;
        char *file_name = de->d_name;
        char *file_path = (char *)malloc(strlen(lsm_dir->path_name) + strlen(file_name) + 2);
        lsm_file_type_t file_type;
        sprintf(file_path, "%s/%s", lsm_dir->path_name, file_name);

        if (stat(file_path, &buf_st) == -1)
        {
            free(file_path);
            continue;
        }

        if (S_ISDIR(buf_st.st_mode))
            file_type = LSM_DIRECTORY;
        else if (S_ISREG(buf_st.st_mode))
            file_type = LSM_FILE;
        else
            file_type = UNKNOWN;

        lsm_file_t *file = lsm_file_create(file_name, file_path, file_type);
        lsm_dir->files = (lsm_file_t **)realloc(lsm_dir->files, sizeof(lsm_file_t *) * (lsm_dir->num_files + 1));
        lsm_dir->files[lsm_dir->num_files] = file;
        lsm_dir->num_files++;

        free(file_path);
    }

    closedir(dr);
    return true;
}