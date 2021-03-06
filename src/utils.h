/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
 */

#ifndef HEADER_UTILS_H
#define HEADER_UTILS_H

#include <sys/stat.h>
#include <sys/types.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "error.h"

#define maybe_unused __attribute__((unused))
#define assert_func(fn) ({ maybe_unused int r_ = fn; assert(r_ == 0); })
#define nitems(x) (sizeof(x) / sizeof(*x))

#define MODE_DIR(mode) ((mode) | S_IFDIR)
#define MODE_REG(mode) ((mode) | S_IFREG)

bool log_active(void);
void log_open(const char *);
void log_close(void);
void log_write(char, const char *, unsigned long, const char *, ...)
    __attribute__((format(printf, 4, 5), nonnull(4)));
int  log_pipe_output(struct error *, int[2]);

#define log_info(fmt, ...) log_write('I', __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...) log_write('W', __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_err(fmt, ...)  log_write('E', __FILE__, __LINE__, fmt, ##__VA_ARGS__)

void strlower(char *);
int  strpcmp(const char *, const char *);
int  strrcmp(const char *, const char *);
bool strmatch(const char *, const char * const [], size_t);

int nsenterat(struct error *, int, int);
int nsenter(struct error *, const char *, int);

char **array_new(struct error *, size_t);
void array_free(char *[], size_t);
void array_pack(char *[], size_t *);
const char **array_append(const char **, const char * const [], size_t);

void *file_map(struct error *, const char *, size_t *);
int  file_create(struct error *, const char *, uid_t, gid_t, mode_t);
int  file_remove(struct error *, const char *);
int  file_exists(struct error *, const char *);
int  file_mode(struct error *, const char *, mode_t *);

int path_append(struct error *, char *, const char *);
int path_join(struct error *, char *, const char *, const char *);
int path_resolve(struct error *, char *, const char *, const char *);

#endif /* HEADER_UTILS_H */
