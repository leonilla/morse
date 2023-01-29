#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ERROR -1
#define NL_PRESENT 1
#define NL_ABSENT 0
#define BUFF_SIZE 100

int val_file(char * filename, char const *mode);
int check_newline(char * filename);
int append_newline(char * filename);
char * read_line(FILE * file);
void write_line(FILE * file, char * line);