#include "../include/files.h"

int val_file(char * filename, char const *mode)
{
        FILE * file = fopen(filename, mode);
        if(file == NULL){
                return FILE_ERROR;
        }
        fclose(file);
        return FILE_VALID;
}


int check_newline(char * filename)
{
        FILE * file = fopen(filename, "r");
        char last;
        if(file == NULL){
                return FILE_ERROR;
        }
        fseek(file, -sizeof(char), SEEK_END);
        fread(&last, sizeof(char), 1, file);
        fclose(file);
        if(last == '\n')
                return NL_PRESENT;
        else
                return NL_ABSENT;
}

int append_newline(char * filename)
{
        FILE * file = fopen(filename, "a");
        char newline = '\n';
        int nl = check_newline(filename);
        printf("Checked for newline with result %i\n", nl);
        switch(nl)
        {
                case FILE_ERROR:
                        fclose(file);
                        return FILE_ERROR;
                case NL_ABSENT:
                        if(fwrite(&newline, sizeof(char), 1, file) == 1){
                                fclose(file);
                                return NL_PRESENT;
                        }
                        else{
                                fclose(file);
                                return NL_ABSENT;
                        }
                case NL_PRESENT:
                        fclose(file);
                        return NL_PRESENT;
                default:
                        fclose(file);
                        return NL_ABSENT;
        }
}

char read_char(FILE * file)
{
        char c = 0;
        size_t read = 0;
        if(file == NULL){
                return 0;
        }
        read = fread(&c, sizeof(char), 1, file);
        if(read == 1){
                /*1 char successfully read from file*/
                /*exit function returning char*/
                return c;
        }
        /*Failed to read 1 char from file --> EOF reached*/
        return 0;
}

char * read_line(FILE * file)
{
        char * line = NULL;
        char c;
        int i = 0;
        if(file != NULL){
                c = read_char(file);
                if (c == 0){
                        return NULL;
                }
                line = calloc((BUFF_SIZE + 1), sizeof(char));
                while(c != 0 && c != '\n'){
                        if(i >= BUFF_SIZE){
                                line = realloc(line, (i + 1 + 1) * sizeof(char));
                        }
                        *(line + i) = c;
                        ++i;
                        c = read_char(file);
                }
                *(line + i) = '\0';
                printf("Line: %s.\n", line);
                return line;
        }
        return NULL;
}

void write_line(FILE * file, char * line)
{
        char newline = '\n';
        if(file != NULL && line != NULL){
                fwrite(line, sizeof(char), (strlen(line)), file);
                fwrite(&newline, sizeof(char), 1, file);
        }
        return;
}

