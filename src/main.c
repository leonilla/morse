#include "../include/files.h"
#include "../include/morse.h"

#define STR_BUFF_SIZE 10

#define INVALID_FILE -4
#define INVALID_DEC_INPUT -3
#define INVALID_ENC_INPUT -2
#define INVALID_OPTION -1
#define HELP 0
#define DECODE_STRING 1
#define ENCODE_STRING 2
#define DECODE_FILE 3
#define ENCODE_FILE 4

#define EXIT -1

void flush(void);
char *read_input(char *input);
int input_filenames(char **filename_in, char **filename_out);
int main_menu();
void show_help();
void show_hint();
int validate_syntax(int argc, char *argv[]);

int main(int argc, char *argv[])
{
        int mode, opt = 0;
        char *ein, *aus;
        /* Running without parameters: interactive mode.*/
        if(argc == 1){
                while(opt > EXIT){
                        opt = main_menu();
                }
                return 0;
        }
        mode = validate_syntax(argc, argv);
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
                        file_decode(argv[3], argv[5]);
                        break;
                case ENCODE_FILE:
                        printf("Encoding file '%s'.\n", argv[3]);
                        append_newline(argv[3]);
                        file_encode(argv[3], argv[5]);
                        break;
                default:
                        show_hint();
        }        
        return 0;
}

void flush(void)
{
        while (getchar() != '\n'){ 

        }
}

char *read_input(char *input)
{
        int i = 0;
        char c = getchar();
        input = malloc((STR_BUFF_SIZE + 1) * sizeof(char));
        if(input == NULL){
                return NULL;
        }
        while(c != '\n'){
                if(i >= STR_BUFF_SIZE){
                        input = realloc(input, (i + 1 + 1) * sizeof(char));
                }
                *(input + i) = c;
                i++;
                c= getchar();
        }
        *(input + i) = '\0';
        return input;
}

int input_filenames(char **filename_in, char **filename_out)
{
        int ret = 0;
        printf("\nInput file: ");
        *filename_in = read_input(*filename_in);
        while(strlen(*filename_in) == 0){
                printf("Please provide a non-empty input filename: ");
                *filename_in = read_input(*filename_in);
        }
        ret = val_file(*filename_in, "r");
        if(ret != 0){
                printf("Input file not found. Please double check the file '%s' exists.\n", *filename_in);
                return -1;
        }
        printf("Output file: ");
        *filename_out = read_input(*filename_out);
        if(strlen(*filename_out) == 0){
                printf("Empty output filename provided. Output will be written to default 'file.out'.\n");
                *filename_out = "file.out";
        }
        ret = val_file(*filename_out, "a");
        if(ret != 0){
                printf("Error writing to '%s'. Please double check that you have permissions to write to this path.\n", *filename_out);
                return -1;
        }
        return 0;
}

/* Show main menu, capture single letter option, launch corresponding mode.*/
/* opt is returned to main for flow control.*/
int main_menu()
{
        char opt;
        char *filename_in = NULL, *filename_out = NULL;
        printf("\n******** Morse Code Encoder/Decoder ********\n");
        printf("***************  Main Menu  ****************\n");
        printf("\td - Decode a file\n");
        printf("\te - Encode a file\n");
        printf("\ti - Interactive Encode/Decode\n\n");       
        printf("\tx - Terminate application and exit\n");
        printf("--------------------------------------------\n\n");
        printf("Please enter the desired option: ");
        opt = getchar();
        flush();
        
        switch(opt)
        {
                case 'd':
                case 'D':
                        printf("Launching file decoding mode...\n\n");
                        input_filenames(&filename_in, &filename_out);
                        if(filename_in != NULL && filename_out != NULL){
                                file_decode(filename_in, filename_out);
                        }
                        break;
                case 'e':
                case 'E':
                        printf("Launching file encoding mode...\n\n");
                        input_filenames(&filename_in, &filename_out);
                        if(filename_in != NULL && filename_out != NULL){
                                file_encode(filename_in, filename_out);
                        }
                        break;
                case 'i':
                case 'I':
                        printf("Launching interactive mode...\n\n");
                        printf("Type 'exit()' in order to leave interactive mode.\n");
                        break;
                case 'x':
                case 'X':
                        printf("\nHave a great day!\n");
                        return EXIT;
                default:
                        printf("Please try again using one of the options listed in the menu.\n\n");
                        return 0;
        }
        return opt;
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