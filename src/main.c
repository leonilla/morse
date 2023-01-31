#include "../include/inputoutput.h"

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
        
        /* Running with parameters: command line mode.*/
        /* Command syntax is checked and the corresponding functions are called.*/
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
                        aus = decode_string(ein); 
                        printf("%s\n", aus);
                        free(aus);
                        break;
                case ENCODE_STRING:
                        printf("Running encoding mode on input '%s':\n", argv[2]);
                        ein = argv[2];
                        aus = encode_string(ein);
                        printf("%s\n", aus);
                        free(aus);
                        break;
                case DECODE_FILE:
                        append_newline(argv[3]);
                        decode_file(argv[3], argv[5]);
                        break;
                case ENCODE_FILE:
                        append_newline(argv[3]);
                        encode_file(argv[3], argv[5]);
                        break;
                default:
                        show_hint();
        }        
        return 0;
}
