#include <stdarg.h>
#include <stdio.h>

// todo: eventually we can turn some of these into functional calls

int access(const char *path, int mode) { return -1; }
int getpid(void) { return 1; }
int gettimeofday(void *time, void *zone) { return 0; }
int kill(int process, int signal) { return -1; }
int mkdir(const char *path, int mode) { return -1; }
int open(const char *path, int flags, ...) { return -1; }
int usleep(unsigned int microseconds) { return 0; }

int _fseeko_r(struct _reent *context, FILE *file, _off_t offset, int origin) { return -1; }
_off_t _ftello_r(struct _reent *context, FILE *file) { return -1; }

int fprintf(FILE *file, const char *format, ...) { return 0; }
int fscanf(FILE *file, const char *format, ...) { return 0; }
int printf(const char *format, ...) { return 0; }
int sprintf(char *output, const char *format, ...) { output[0] = 0; return 0; }
int sscanf(const char *input, const char *format, ...) { return 0; }
int vfprintf(FILE *file, const char *format, va_list arguments) { return 0; }
