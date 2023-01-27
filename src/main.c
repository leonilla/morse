#include "../include/files.h"
#include "../include/morse.h"

#define INVALID_FILE -4
#define INVALID_DEC_INPUT -3
#define INVALID_ENC_INPUT -2
#define INVALID_OPTION -1
#define HELP 0
#define DECODE_STRING 1
#define ENCODE_STRING 2
#define DECODE_FILE 3
#define ENCODE_FILE 4

void show_help();
void show_hint();
int validate_syntax(int argc, char *argv[]);

int main(int argc, char *argv[]){
        FILE * fptr_ein;
        FILE * fptr_aus;
        char * ein;
        char * aus;
        char * line = NULL;
        int mode = validate_syntax(argc, argv);
        switch(mode)
        {
                case INVALID_DEC_INPUT:
                        printf("Decodable strings can only contain the characters ' ', '/', '-' and '.'.\n");
                        break;
                case INVALID_ENC_INPUT:
                        printf("Encodable strings can only contain letters A-Z, numbers 0-9, or punctuation signs.\n");
                        break;
                case INVALID_OPTION:
                        show_hint();
                        break;
                case HELP:
                        show_help();
                        break;
                case DECODE_STRING:
                        printf("Running decoding mode on input '%s':\n", argv[2]);
                        ein = argv[2];
                        aus = malloc((strlen(ein) + 1) * sizeof(char));
                        morse_decode(ein, aus); 
                        printf("%s\n", aus);
                        free(aus);
                        break;
                case ENCODE_STRING:
                        printf("Running encoding mode on input '%s':\n", argv[2]);
                        ein = argv[2];
                        aus = malloc((strlen(ein) + 1) * 6 * sizeof(char));
                        morse_encode(ein, aus);
                        printf("%s\n", aus);
                        free(aus);
                        break;
                case DECODE_FILE:
                        printf("Decoding file '%s'.\n", argv[3]);
                        append_newline(argv[3]);
                        fptr_ein = fopen(argv[3], "r");
                        if(fptr_ein == NULL){
                                printf("Error opening file %s.\n", argv[3]);
                                return INVALID_FILE;
                        }
                        fptr_aus = fopen(argv[5], "a");
                        if(fptr_aus == NULL){
                                printf("Error opening file %s.\n", argv[5]);
                                return INVALID_FILE;
                        }
                        line = read_line(fptr_ein);
                        while(line != NULL){
                                aus = calloc((strlen(line) + 1) , sizeof(char));
                                morse_decode(line, aus);
                                write_line(fptr_aus, aus);
                                free(aus);
                                line = read_line(fptr_ein);
                        }
                        printf("Decoding done. Output written to %s.\n", argv[5]);
                        fclose(fptr_ein);
                        fclose(fptr_aus);                        
                        break;
                case ENCODE_FILE:
                        printf("Encoding file '%s'.\n", argv[3]);
                        append_newline(argv[3]);
                        fptr_ein = fopen(argv[3], "r");
                        if(fptr_ein == NULL){
                                printf("Error opening file %s.\n", argv[3]);
                                return INVALID_FILE;
                        }
                        fptr_aus = fopen(argv[5], "a");
                        if(fptr_aus == NULL){
                                printf("Error opening file %s.\n", argv[5]);
                                return INVALID_FILE;
                        }
                        line = read_line(fptr_ein);
                        while(line != NULL){
                                aus = calloc((strlen(line) + 1) * 6 , sizeof(char));
                                morse_encode(line, aus);
                                write_line(fptr_aus, aus);
                                free(aus);
                                line = read_line(fptr_ein);
                        }
                        printf("Encoding done. Output written to %s.\n", argv[5]);
                        fclose(fptr_ein);
                        fclose(fptr_aus);
                        break;
                default:
                        show_hint();
        }        
        return 0;
}

void show_help(){
        printf("USAGE:\n");
        printf("\tmorse [MODE] [\"QUOTED STRING\"]\n");
        printf("\tor\n");
        printf("\tmorse [MODE] [INPUTFLAG] [FILENAME] [OUTPUTFLAG] [FILENAME]\n");
        printf("\tRun \"morse -H\" or \"morse --help\" for more details.\n");
        printf("\n");
        printf("\tTo decode the string \"--. ..- ..- --.\":\n");
        printf("\t\tmorse -D \"--. ..- ..- --.\"\n");
        printf("\t\tmorse --decode \"--. ..- ..- --.\"\n");
        printf("\n");
        printf("\tTo encode the string \"String to encode\":\n");
        printf("\t\tmorse -E \"String to encode\"\n");
        printf("\t\tmorse --encode \"String to encode\"\n");
        printf("\n");
        printf("\tTo decode the contents of file input.file onto output.file:\n");
        printf("\t\tmorse -D -I <path/to/input.file> -O <path/to/output.file>\n");
        printf("\t\tmorse --decode -I <path/to/input.file> -O <path/to/output.file>\n");
        printf("\n");
        printf("\tTo encode the contents of file input.file onto output.file:\n");
        printf("\t\tmorse -E -I <path/to/input.file> -O <path/to/output.file>\n");
        printf("\t\tmorse --encode -I <path/to/input.file> -O <path/to/output.file>\n");
        printf("\n");
        printf("\tTo show this help screen:\n");
        printf("\t\tmorse -H\n");
        printf("\t\tmorse --help\n");
}

void show_hint(){
        printf("USAGE:\n");
        printf("\tmorse [MODE] [\"QUOTED STRING\"]\n");
        printf("\tor\n");
        printf("\tmorse [MODE] [INPUTFLAG] [FILENAME] [OUTPUTFLAG] [FILENAME]\n");
        printf("\tRun \"morse -H\" or \"morse --help\" for more details.\n");
}

int validate_syntax(int argc, char *argv[]){
        if (argc == 2){
                if((strcmp(argv[1],"-H") == 0) || strcmp(argv[1],"--help") == 0){
                        return HELP;
                }
                else
                        return INVALID_OPTION;
        }
        else if (argc == 3){
                if ((strcmp(argv[1],"-D") == 0) || (argc == 3 && strcmp(argv[1],"--decode") == 0)){
                        if(strspn(argv[2], DECODABLE) == strlen(argv[2])){
                                return DECODE_STRING;
                        }
                        else{
                                return INVALID_DEC_INPUT;
                        }
                }
                else if ((strcmp(argv[1],"-E") == 0) || (strcmp(argv[1],"--encode") == 0)){
                        if(strspn(argv[2], ENCODABLE) == strlen(argv[2])){
                                return ENCODE_STRING;
                        }
                        else{
                                return INVALID_ENC_INPUT;
                        }
                }
                else{
                        return INVALID_OPTION;
                }
        }
        else if (argc == 6){
                if(((strcmp(argv[1],"-D") == 0) || (strcmp(argv[1],"--decode") == 0) ) && (strcmp(argv[2],"-I") == 0) && (strcmp(argv[4],"-O") == 0)){
                        return DECODE_FILE;
                }
                else if(((strcmp(argv[1],"-E") == 0) || (strcmp(argv[1],"--encode") == 0)) && (strcmp(argv[2],"-I") == 0) && (strcmp(argv[4],"-O") == 0)){
                        return ENCODE_FILE;
                }
        } 
        return INVALID_OPTION;
}