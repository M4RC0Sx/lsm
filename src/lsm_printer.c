#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lsm_dir.h"
#include "lsm_file.h"

static int lsm_printer_get_hard_links_count_len(lsm_dir_t *lsm_dir);
static int lsm_printer_get_owner_len(lsm_dir_t *lsm_dir);
static int lsm_printer_get_group_len(lsm_dir_t *lsm_dir);
static int lsm_printer_get_size_len(lsm_dir_t *lsm_dir);
static int lsm_printer_get_last_modified_timestamp_len(lsm_dir_t *lsm_dir);

void lsm_printer_display_long_list_output(bool opt_display_hidden, bool opt_display_dots, lsm_dir_t **dirs, int num_dirs)
{

    lsm_dir_t *lsm_dir = NULL;

    char *final_msg = malloc(sizeof(char));
    final_msg[0] = '\0';

    int final_msg_len = 0;
    for (int i = 0; i < num_dirs; i++)
    {
        lsm_dir = dirs[i];
        int len_hard_links_count = lsm_printer_get_hard_links_count_len(lsm_dir);
        int len_owner = lsm_printer_get_owner_len(lsm_dir);
        int len_group = lsm_printer_get_group_len(lsm_dir);
        int len_size = lsm_printer_get_size_len(lsm_dir);
        int len_last_modified_timestamp = lsm_printer_get_last_modified_timestamp_len(lsm_dir);

        for (int j = 0; j < lsm_dir->num_files; j++)
        {
            lsm_file_t *file = lsm_dir->files[j];
            if ((file->is_hidden && !opt_display_hidden) || (file->is_dot && !opt_display_dots))
                continue;

            char *perms_str = file->perms_str;
            int hard_links_count = file->hard_links_count;
            char *owner = file->owner;
            char *group = file->group;
            long size = file->size;
            char *last_modified_timestamp = ctime(&file->last_modified_timestamp);
            last_modified_timestamp[strlen(last_modified_timestamp) - 1] = '\0'; // Remove newline character
            char *name = file->name;

            int file_msg_len = snprintf(NULL, 0, "%s %*d %*s %*s %*ld %*s %s\n", perms_str, len_hard_links_count, hard_links_count, len_owner, owner, len_group, group, len_size, size, len_last_modified_timestamp, last_modified_timestamp, name);
            char *file_msg = malloc(file_msg_len + 1);
            snprintf(file_msg, file_msg_len + 1, "%s %*d %*s %*s %*ld %*s %s\n", perms_str, len_hard_links_count, hard_links_count, len_owner, owner, len_group, group, len_size, size, len_last_modified_timestamp, last_modified_timestamp, name);

            final_msg_len += file_msg_len;
            final_msg = realloc(final_msg, final_msg_len + 1);
            strcat(final_msg, file_msg);

            free(file_msg);
        }

        fprintf(stdout, "%s", final_msg);
        free(final_msg);
    }
}

static int lsm_printer_get_hard_links_count_len(lsm_dir_t *lsm_dir)
{
    int max_hard_links_count = 0;
    for (int i = 0; i < lsm_dir->num_files; i++)
    {
        lsm_file_t *file = lsm_dir->files[i];
        if (file->hard_links_count > max_hard_links_count)
            max_hard_links_count = file->hard_links_count;
    }

    int hard_links_count_len = snprintf(NULL, 0, "%d", max_hard_links_count);
    return hard_links_count_len;
}

static int lsm_printer_get_owner_len(lsm_dir_t *lsm_dir)
{
    int max_owner_len = 0;
    for (int i = 0; i < lsm_dir->num_files; i++)
    {
        lsm_file_t *file = lsm_dir->files[i];
        int owner_len = strlen(file->owner);
        if (owner_len > max_owner_len)
            max_owner_len = owner_len;
    }

    return max_owner_len;
}

static int lsm_printer_get_group_len(lsm_dir_t *lsm_dir)
{
    int max_group_len = 0;
    for (int i = 0; i < lsm_dir->num_files; i++)
    {
        lsm_file_t *file = lsm_dir->files[i];
        int group_len = strlen(file->group);
        if (group_len > max_group_len)
            max_group_len = group_len;
    }

    return max_group_len;
}

static int lsm_printer_get_size_len(lsm_dir_t *lsm_dir)
{
    int max_size = 0;
    for (int i = 0; i < lsm_dir->num_files; i++)
    {
        lsm_file_t *file = lsm_dir->files[i];
        if (file->size > max_size)
            max_size = file->size;
    }

    int size_len = snprintf(NULL, 0, "%d", max_size);
    return size_len;
}

static int lsm_printer_get_last_modified_timestamp_len(lsm_dir_t *lsm_dir)
{
    int max_last_modified_timestamp_len = 0;
    for (int i = 0; i < lsm_dir->num_files; i++)
    {
        lsm_file_t *file = lsm_dir->files[i];
        char *last_modified_timestamp = ctime(&file->last_modified_timestamp);
        last_modified_timestamp[strlen(last_modified_timestamp) - 1] = '\0'; // Remove newline character
        int last_modified_timestamp_len = strlen(last_modified_timestamp);
        if (last_modified_timestamp_len > max_last_modified_timestamp_len)
            max_last_modified_timestamp_len = last_modified_timestamp_len;
    }

    return max_last_modified_timestamp_len;
}
