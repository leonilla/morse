#include "../include/inputoutput.h"

int main(int argc, char *argv[])
{
        int mode, opt = 0;
        char *ein, *aus;

        /* Keine Kommando Zeile Parameter: Interaktive Modus.*/
        if(argc == 1){
                /* Menü wird wiederholend gezeigt, bis zur Eingabe des Exits Kommandos.*/
                while(opt > EXIT){
                        opt = main_menu();
                }
                return 0;
        }
        
        /* Kommando Zeile Parameter: UNIX Utility Modus.*/
        /* Syntax wird validiert und die entsprechende Funktionen werden aufgerufen.*/
        /* Anwendung wird automatisch beendet nach der Ausführung der Aufgabe*/
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
                        if(val_file(argv[3], "r") == -1){
                                printf("Input file not found. Please double check the file '%s' exists.\n", argv[3]);
                                return FILE_ERROR;
                        }
                        else if(val_file(argv[5], "a") == -1){
                                printf("Error writing to '%s'. Please double check that you have permissions to write to this path.\n", argv[5]);
                                return FILE_ERROR;
                        }
                        append_newline(argv[3]);
                        decode_file(argv[3], argv[5]);
                        break;
                case ENCODE_FILE:
                        if(val_file(argv[3], "r") == -1){
                                printf("Input file not found. Please double check the file '%s' exists.\n", argv[3]);
                                return FILE_ERROR;
                        }
                        else if(val_file(argv[5], "a") == -1){
                                printf("Error writing to '%s'. Please double check that you have permissions to write to this path.\n", argv[5]);
                                return FILE_ERROR;
                        }                
                        append_newline(argv[3]);
                        encode_file(argv[3], argv[5]);
                        break;
                default:
                        show_hint();
        }        
        return 0;
}
