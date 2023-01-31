#include "../include/morse.h"

char *char_encode(char input)
{
        char *code;
        input = toupper(input);
        switch(input)
        {
                case 'A':
                        code = CODE_A;
                        break;
                case 'B':
                        code = CODE_B;
                        break;
                case 'C':
                        code = CODE_C;
                        break;
                case 'D':
                        code = CODE_D;
                        break;
                case 'E':
                        code = CODE_E;
                        break;
                case 'F':
                        code = CODE_F;
                        break;
                case 'G':
                        code = CODE_G;
                        break;
                case 'H':
                        code = CODE_H;
                        break;
                case 'I':
                        code = CODE_I;
                        break;
                case 'J':
                        code = CODE_J;
                        break;
                case 'K':
                        code = CODE_K;
                        break;
                case 'L':
                        code = CODE_L;
                        break;
                case 'M':
                        code = CODE_M;
                        break;
                case 'N':
                        code = CODE_N;
                        break;
                case 'O':
                        code = CODE_O;
                        break;
                case 'P':
                        code = CODE_P;
                        break;
                case 'Q':
                        code = CODE_Q;
                        break;
                case 'R':
                        code = CODE_R;
                        break;
                case 'S':
                        code = CODE_S;
                        break;
                case 'T':
                        code = CODE_T;
                        break;
                case 'U':
                        code = CODE_U;
                        break;
                case 'V':
                        code = CODE_V;
                        break;
                case 'W':
                        code = CODE_W;
                        break;
                case 'X':
                        code = CODE_X;
                        break;
                case 'Y':
                        code = CODE_Y;
                        break;
                case 'Z':
                        code = CODE_Z;
                        break;
                case '1':
                        code = CODE_1;
                        break;
                case '2':
                        code = CODE_2;
                        break;
                case '3':
                        code = CODE_3;
                        break;
                case '4':
                        code = CODE_4;
                        break;
                case '5':
                        code = CODE_5;
                        break;
                case '6':
                        code = CODE_6;
                        break;
                case '7':
                        code = CODE_7;
                        break;
                case '8':
                        code = CODE_8;
                        break;
                case '9':
                        code = CODE_9;
                        break;
                case '0':
                        code = CODE_0;
                        break;
                case '.':
                        code = CODE_PUNKT;
                        break;
                case ',':
                        code = CODE_KOMMA;
                        break;
                case ':':
                        code = CODE_COLON;
                        break;
                case ';':
                        code = CODE_SEMIC;
                        break;
                case '?':
                        code = CODE_QMARK;
                        break;
                case '!':
                        code = CODE_EMARK;
                        break;
                case '-':
                        code = CODE_MINUS;
                        break;
                case '_':
                        code = CODE_UNDSC;
                        break;
                case '(':
                        code = CODE_PAROP;
                        break;
                case ')':
                        code = CODE_PARCL;
                        break;
                case '\'':
                        code = CODE_SQUOT;
                        break;
                case '"':
                        code = CODE_DQUOT;
                        break;
                case '=':
                        code = CODE_EQUAL;
                        break;
                case '+':
                        code = CODE_PLUSZ;
                        break;
                case '/':
                        code = CODE_SLASH;
                        break;
                case '@':
                        code = CODE_ATSYM;
                        break;
                case ' ':
                        code = WORT_TREN;
                        break;
                default:
                        code = NULL;
                        printf("Unrecognized char '%c' (%i).", input, input);
                        break;
        }
        return code;
}

char *encode_string(char *input)
{
        /*Initially allocate size for the biggest single char code*/
        char *output = calloc( (7+1), sizeof(char));
        char *code = NULL;
        char *endstr = "\0";
        char *blanksp = ZEICH_TREN;
        int i = 0;
        char c = *(input + i);
        while(c != '\0'){
                code = char_encode(c);
                if(code == NULL){
                        return NULL;
                }
                /*Reallocate output to grow by the size of the char's code, plus space, plus endline*/
                output = realloc(output, (strlen(output) + strlen(code) + 2) * sizeof(char));
                /*Append char's code to output*/
                strcat(output, code);
                ++i;
                c = *(input + i);
                /*Append blankspace to output if more characters are coming*/
                if(c != '\0'){
                        strcat(output, blanksp);
                }
                code = NULL;
        }
        /*Append \0 to output*/
        strcat(output, endstr);
        return output;
}

int encode_file(char *file_in, char *file_out)
{
        FILE *fptr_in, *fptr_out;
        char *line, *aus;
        int i = 0;
        printf("Encoding file '%s'.\n", file_in);
        append_newline(file_in);
        fptr_in = fopen(file_in, "r");
        if(fptr_in == NULL){
                printf("Error opening file %s.\n", file_in);
                return FILE_ERROR;
        }
        fptr_out = fopen(file_out, "a");
        if(fptr_out == NULL){
                printf("Error opening file %s.\n", file_out);
                return FILE_ERROR;
        }
        line = read_line(fptr_in);
        while(line != NULL){
                ++i;
                aus = encode_string(line);
                if(aus == NULL){
                        printf("Issue on line %i of file %s .\n", i, file_in);
                        printf("Please verify no unsupported characters are present in file to encode.\n");
                        return UNSUPPORTED;
                }
                write_line(fptr_out, aus);
                line = read_line(fptr_in);
        }
        printf("Encoding done. Output written to %s.\n", file_out);
        fclose(fptr_in);
        fclose(fptr_out);
        return 0;
}

char *decode_char(char *input)
{
        char *c;
        size_t len = strlen(input);
        /*decode input by comparing with codes of the appropriate length*/
        switch(len)
        {
                case 0:
                        c = "\0";
                        break;
                case 1:
                        if(strcmp(input, CODE_E) == 0){
                                c = "E";
                        }
                        else if(strcmp(input, CODE_T) == 0){
                                c = "T";
                        }
                        else if(strcmp(input, WORT_TREN) == 0){
                                c = " ";
                        }
                        break;
                case 2:
                        if(strcmp(input, CODE_M) == 0){
                                c = "M";
                        }
                        else if(strcmp(input, CODE_N) == 0){
                                c = "N";
                        }
                        else if(strcmp(input, CODE_A) == 0){
                                c = "A";
                        }
                        else if(strcmp(input, CODE_I) == 0){
                                c = "I";
                        }
                        break;
                case 3:
                        if(strcmp(input, CODE_O) == 0){
                                c = "O";
                        }
                        else if(strcmp(input, CODE_G) == 0){
                                c = "G";
                        }
                        else if(strcmp(input, CODE_K) == 0){
                                c = "K";
                        }
                        else if(strcmp(input, CODE_D) == 0){
                                c = "D";
                        }
                        else if(strcmp(input, CODE_W) == 0){
                                c = "W";
                        }
                        else if(strcmp(input, CODE_R) == 0){
                                c = "R";
                        }
                        else if(strcmp(input, CODE_U) == 0){
                                c = "U";
                        }
                        else if(strcmp(input, CODE_S) == 0){
                                c = "S";
                        }
                        break;
                case 4:
                        if(strcmp(input, CODE_Q) == 0){
                                c = "Q";
                        }
                        else if(strcmp(input, CODE_Z) == 0){
                                c = "Z";
                        }
                        else if(strcmp(input, CODE_Y) == 0){
                                c = "Y";
                        }
                        else if(strcmp(input, CODE_C) == 0){
                                c = "C";
                        }
                        else if(strcmp(input, CODE_X) == 0){
                                c = "X";
                        }
                        else if(strcmp(input, CODE_B) == 0){
                                c = "B";
                        }
                        else if(strcmp(input, CODE_J) == 0){
                                c = "J";
                        }
                        else if(strcmp(input, CODE_P) == 0){
                                c = "P";
                        }
                        else if(strcmp(input, CODE_L) == 0){
                                c = "L";
                        }
                        else if(strcmp(input, CODE_F) == 0){
                                c = "F";
                        }
                        else if(strcmp(input, CODE_V) == 0){
                                c = "V";
                        }
                        else if(strcmp(input, CODE_H) == 0){
                                c = "H";
                        }
                        else if(strcmp(input, CODE_CH) == 0){
                                c = "CH";
                        }
                        else if(strcmp(input, CODE_O_UMLT) == 0){
                                c = "Ö";
                        }
                        else if(strcmp(input, CODE_A_UMLT) == 0){
                                c = "Ä";
                        }
                        else if(strcmp(input, CODE_U_UMLT) == 0){
                                c = "Ü"; 
                        }
                        break;
                case 5:
                        if(strcmp(input, CODE_0) == 0){
                                c = "0";
                        }
                        else if(strcmp(input, CODE_9) == 0){
                                c = "9";
                        }
                        else if(strcmp(input, CODE_8) == 0){
                                c = "8";
                        }
                        else if(strcmp(input, CODE_N_TILD) == 0){
                                c = "Ñ";
                        }
                        else if(strcmp(input, CODE_7) == 0){
                                c = "7";
                        }
                        else if(strcmp(input, CODE_PAROP) == 0){
                                c = "(";
                        }
                        else if(strcmp(input, CODE_SLASH) == 0){
                                c = "/";
                        }
                        else if(strcmp(input, CODE_EQUAL) == 0){
                                c = "=";
                        }
                        else if(strcmp(input, CODE_6) == 0){
                                c = "6";
                        }
                        else if(strcmp(input, CODE_1) == 0){
                                c = "1";
                        }
                        else if(strcmp(input, CODE_A_GRAV) == 0){
                                c = "À";
                        }
                        else if(strcmp(input, CODE_PLUSZ) == 0){
                                c = "+";
                        }
                        else if(strcmp(input, CODE_E_GRAV) == 0){
                                c = "È";
                        }
                        else if(strcmp(input, CODE_2) == 0){
                                c = "2";
                        }
                        else if(strcmp(input, CODE_E_ACUT) == 0){
                                c = "É";
                        }
                        else if(strcmp(input, CODE_3) == 0){
                                c = "3";
                        }
                        else if(strcmp(input, CODE_4) == 0){
                                c = "4";
                        }
                        else if(strcmp(input, CODE_5) == 0){
                                c = "5";
                        }
                        break;
                case 6:
                        if(strcmp(input, CODE_COLON) == 0){
                                c = ":";
                        }
                        else if(strcmp(input, CODE_KOMMA) == 0){
                                c = ",";
                        }
                        else if(strcmp(input, CODE_PARCL) == 0){
                                c = ")";
                        }
                        else if(strcmp(input, CODE_EMARK) == 0){
                                c = "!";
                        }
                        else if(strcmp(input, CODE_SEMIC) == 0){
                                c = ";";
                        }
                        else if(strcmp(input, CODE_MINUS) == 0){
                                c = "-";
                        }
                        else if(strcmp(input, CODE_SQUOT) == 0){
                                c = "'";
                        }
                        else if(strcmp(input, CODE_ATSYM) == 0){
                                c = "@";
                        }
                        else if(strcmp(input, CODE_PUNKT) == 0){
                                c = ".";
                        }
                        else if(strcmp(input, CODE_DQUOT) == 0){
                                c = "\"";
                        }
                        else if(strcmp(input, CODE_UNDSC) == 0){
                                c = "_";
                        }
                        else if(strcmp(input, CODE_QMARK) == 0){
                                c = "?";
                        }
                        break;
                case 7:
                        if(strcmp(input, CODE_S_ZED) == 0){
                                c = "ß";
                        }
                        break;
                default:
                        printf("Code '%s' unknown.\n", input);
                        c = NULL;
                        break;
        }              
        return c;
}

char *decode_string(char *input)
{
        /*Initially allocate size for a single char string*/
        char *output = calloc( (1+1), sizeof(char));
        /*Initially allocate size for the shortest code*/
        char *code = calloc( (1+1), sizeof(char));
        char *endstr = "\0";
        size_t i = 0;
        char c = *(input);
        while (c != '\0' && c != 0){
                while(c != ' ' && c != '\0'){
                        *(code+i) = *(input+i);
                        ++i;
                        c = *(input + i);
                        if(c != ' ' && c != '\0'){
                                code = realloc(code, (strlen(code) + 1 + 1) * sizeof(char));
                        }
                        /*Reallocate code to grow by the size of the char's code, plus space, plus endline*/                        
                }
                *(code+i) = '\0';
                if(decode_char(code) == NULL){
                        return NULL;
                }
                /*Append decoded char to output*/
                strcat(output, decode_char(code));
                code = calloc( (1+1), sizeof(char));
                if(strlen(input) > i+1){
                        input = input + i + 1;
                        output = realloc(output, (strlen(output) + 1 + 1) * sizeof(char));
                        i = 0;
                        c = *(input);
                }
        }
        /*Append endline to output*/
        strcat(output, endstr);
        free(code);
        code = NULL;
        return output;
}

int decode_file(char *file_in, char *file_out)
{
        FILE *fptr_in, *fptr_out;
        char *line, *aus;
        int i = 0;
        printf("Decoding file '%s'.\n", file_in);
        append_newline(file_in);
        fptr_in = fopen(file_in, "r");
        if(fptr_in == NULL){
                printf("Error opening file %s.\n", file_in);
                return FILE_ERROR;
        }
        fptr_out = fopen(file_out, "a");
        if(fptr_out == NULL){
                printf("Error opening file %s.\n", file_out);
                return FILE_ERROR;
        }
        line = read_line(fptr_in);
        while(line != NULL){
                ++i;
                aus = decode_string(line);
                if(aus == NULL){
                        printf("Issue on line %i of file %s .\n", i, file_in);
                        printf("Please verify no unsupported characters are present in the file to decode.\n");
                        return UNSUPPORTED;
                }
                write_line(fptr_out, aus);
                line = read_line(fptr_in);
        }
        printf("Decoding done. Output written to %s.\n", file_out);
        fclose(fptr_in);
        fclose(fptr_out);
        return 0;
}
