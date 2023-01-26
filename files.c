#include "files.h"

#define FILE_ERROR -1
#define NL_PRESENT 1
#define NL_ABSENT 0
#define BUFF_SIZE 100

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

char * read_line(FILE * file){
        char * buffer = NULL;
        char * line = NULL;
        size_t len = 0;
        size_t span = 0;
        if(file != NULL){
                buffer = calloc((BUFF_SIZE + 1), sizeof(char));
                len = fread(buffer, sizeof(char), BUFF_SIZE, file);
                span = strcspn(buffer, "\n");
                if(span != 0){
                        line = calloc((span +2), sizeof(char));
                        memcpy(line, buffer, span+1);
                        fseek(file, (len - span -1)*-1, SEEK_CUR);
                        free(buffer);
                }
        }
        return line;
}

void write_line(FILE * file, char * line){
        char newline = '\n';
        if(file != NULL && line != NULL){
                fwrite(line, sizeof(char), (strlen(line)), file);
                fwrite(&newline, sizeof(char), 1, file);
        }
        return;
}
