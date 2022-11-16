#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "lsm_file.h"

#define PERM_STR_LEN 10

static void lsm_file_load_stats(lsm_file_t *lsm_file);
static lsm_file_type_t lsm_file_get_type(struct stat buf_st);
static char *lsm_file_get_ext(lsm_file_t *lsm_file);
static char *lsm_file_get_owner(lsm_file_t *lsm_file, struct stat buf_st);
static char *lsm_file_get_group(lsm_file_t *lsm_file, struct stat buf_st);
static char *lsm_file_get_permissions_string(lsm_file_t *lsm_file, struct stat buf_st);

lsm_file_t *lsm_file_create(char *file_name, char *file_path)
{
    lsm_file_t *file = malloc(sizeof(lsm_file_t));

    file->name = malloc(strlen(file_name) + 1);
    strcpy(file->name, file_name);

    file->path = malloc(strlen(file_path) + 1);
    strcpy(file->path, file_path);

    /* File stats initialization */
    file->extension = NULL;
    file->is_hidden = false;
    file->is_dot = false;
    file->owner = NULL;
    file->group = NULL;
    file->size = 0;
    file->last_modified_timestamp = 0;
    file->perms_str = NULL;

    lsm_file_load_stats(file);
    return file;
}

void lsm_file_destroy(lsm_file_t *lsm_file)
{
    free(lsm_file->name);
    free(lsm_file->path);
    free(lsm_file->perms_str);
    free(lsm_file);
}

void lsm_file_print(lsm_file_t *lsm_file)
{
    printf("%s, %s, %s, %s, %s, %s, %ld, %ld, %s, %d\n", lsm_file->name, lsm_file->path, lsm_file->type == LSM_FILE ? "file" : "directory", lsm_file->extension, lsm_file->owner, lsm_file->group, lsm_file->size, lsm_file->last_modified_timestamp, lsm_file->perms_str, lsm_file->hard_links_count);
}

static void lsm_file_load_stats(lsm_file_t *lsm_file)
{
    struct stat buf_st;
    if (stat(lsm_file->path, &buf_st) == -1)
        return;

    lsm_file->type = lsm_file_get_type(buf_st);
    lsm_file->extension = lsm_file_get_ext(lsm_file);
    lsm_file->is_hidden = lsm_file->name[0] == '.';
    lsm_file->is_dot = strcmp(lsm_file->name, ".") == 0 || strcmp(lsm_file->name, "..") == 0;
    lsm_file->owner = lsm_file_get_owner(lsm_file, buf_st);
    lsm_file->group = lsm_file_get_group(lsm_file, buf_st);
    lsm_file->size = buf_st.st_size;
    lsm_file->last_modified_timestamp = buf_st.st_mtime;
    lsm_file->perms_str = lsm_file_get_permissions_string(lsm_file, buf_st);
    lsm_file->hard_links_count = buf_st.st_nlink;
}

static lsm_file_type_t lsm_file_get_type(struct stat buf_st)
{
    lsm_file_type_t file_type = UNKNOWN;
    if (S_ISDIR(buf_st.st_mode))
        file_type = LSM_DIRECTORY;
    else if (S_ISREG(buf_st.st_mode))
        file_type = LSM_FILE;
    else
        file_type = UNKNOWN;

    return file_type;
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

static char *lsm_file_get_owner(lsm_file_t *lsm_file, struct stat buf_st)
{
    if (lsm_file->type == UNKNOWN)
        return NULL;

    struct passwd *pw = getpwuid(buf_st.st_uid);
    return pw ? pw->pw_name : NULL;
}

static char *lsm_file_get_group(lsm_file_t *lsm_file, struct stat buf_st)
{
    if (lsm_file->type == UNKNOWN)
        return NULL;

    struct group *gr = getgrgid(buf_st.st_gid);
    return gr ? gr->gr_name : NULL;
}

static char *lsm_file_get_permissions_string(lsm_file_t *lsm_file, struct stat buf_st)
{
    if (lsm_file->type == UNKNOWN)
        return NULL;

    char *perm_str = malloc((PERM_STR_LEN + 1) * sizeof(char));
    perm_str[0] = (S_ISDIR(buf_st.st_mode)) ? 'd' : '-';
    perm_str[1] = (buf_st.st_mode & S_IRUSR) ? 'r' : '-';
    perm_str[2] = (buf_st.st_mode & S_IWUSR) ? 'w' : '-';
    perm_str[3] = (buf_st.st_mode & S_IXUSR) ? 'x' : '-';
    perm_str[4] = (buf_st.st_mode & S_IRGRP) ? 'r' : '-';
    perm_str[5] = (buf_st.st_mode & S_IWGRP) ? 'w' : '-';
    perm_str[6] = (buf_st.st_mode & S_IXGRP) ? 'x' : '-';
    perm_str[7] = (buf_st.st_mode & S_IROTH) ? 'r' : '-';
    perm_str[8] = (buf_st.st_mode & S_IWOTH) ? 'w' : '-';
    perm_str[9] = (buf_st.st_mode & S_IXOTH) ? 'x' : '-';
    perm_str[10] = '\0';

    return perm_str;
}