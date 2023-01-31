#include "../include/files.h"

int val_file(char *filename, char const *mode)
{
        FILE * file = fopen(filename, mode);
        if(file == NULL){
                return FILE_ERROR;
        }
        fclose(file);
        return FILE_VALID;
}


int check_newline(char *filename)
{
        FILE *file = fopen(filename, "r");
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

int append_newline(char *filename)
{
        FILE *file = fopen(filename, "a");
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

char read_char(FILE *file)
{
        char c = 0;
        size_t read = 0;
        if(file == NULL){
                return 0;
        }
        read = fread(&c, sizeof(char), 1, file);
        if(read == 1){
                /*1 char erfolgreich von Datei gelesen*/
                /*Dieses char wird zurückgegeben*/
                return c;
        }
        /*Lesen von 1 char von Datei hat nicht geklappt --> EOF erreicht*/
        return 0;
}

char *read_line(FILE *file)
{
        char *line = NULL;
        char c;
        int i = 0;
        if(file != NULL){
                /*Zeilen aus einer Datei werden ein char auf einmal gelesen*/
                c = read_char(file);
                /*Überprüfen, ob Zeile leer ist*/
                if (c == 0){
                        return NULL;
                }
                /*Gelesene char werden im String gespeichert*/
                line = calloc((BUFF_SIZE + 1), sizeof(char));
                while(c != 0 && c != '\n'){
                        /*Gibt es kein Platz im String mehr, eine einzige weitere Speicherzelle wird reserviert*/
                        if(i >= BUFF_SIZE){
                                line = realloc(line, (i + 1 + 1) * sizeof(char));
                        }
                        *(line + i) = c;
                        ++i;
                        c = read_char(file);
                }
                /*Terminal char wird am ende des Strings angehängt*/
                *(line + i) = '\0';
                return line;
        }
        return NULL;
}

void write_line(FILE *file, char *line)
{
        char newline = '\n';
        if(file != NULL && line != NULL){
                fwrite(line, sizeof(char), (strlen(line)), file);
                /*Ein newline wird am Ende jeder Zeile angehängt*/
                fwrite(&newline, sizeof(char), 1, file);
        }
        return;
}

