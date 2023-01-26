#include "morse.h"

/* Zeichen bestehen aus '.' und '-'*/
/* Zeichen eines Wortes werden durch ' ' getrennt*/
/* Wörter werden durch '/' getrennt*/

/*TODO: Separate meaningfully into .c/.h files*/
/*TODO: Error Handling*/

int morse_encode(char * input, char * output)
{
        char curr_char;
        char * curr_code;
        char * next_char;
        curr_char =  *(input);
        curr_char = toupper(curr_char);
        switch(curr_char)
        {
                case 'A':
                        curr_code = CODE_A;
                        break;
                case 'B':
                        curr_code = CODE_B;
                        break;
                case 'C':
                        curr_code = CODE_C;
                        break;
                case 'D':
                        curr_code = CODE_D;
                        break;
                case 'E':
                        curr_code = CODE_E;
                        break;
                case 'F':
                        curr_code = CODE_F;
                        break;
                case 'G':
                        curr_code = CODE_G;
                        break;
                case 'H':
                        curr_code = CODE_H;
                        break;
                case 'I':
                        curr_code = CODE_I;
                        break;
                case 'J':
                        curr_code = CODE_J;
                        break;
                case 'K':
                        curr_code = CODE_K;
                        break;
                case 'L':
                        curr_code = CODE_L;
                        break;
                case 'M':
                        curr_code = CODE_M;
                        break;
                case 'N':
                        curr_code = CODE_N;
                        break;
                case 'O':
                        curr_code = CODE_O;
                        break;
                case 'P':
                        curr_code = CODE_P;
                        break;
                case 'Q':
                        curr_code = CODE_Q;
                        break;
                case 'R':
                        curr_code = CODE_R;
                        break;
                case 'S':
                        curr_code = CODE_S;
                        break;
                case 'T':
                        curr_code = CODE_T;
                        break;
                case 'U':
                        curr_code = CODE_U;
                        break;
                case 'V':
                        curr_code = CODE_V;
                        break;
                case 'W':
                        curr_code = CODE_W;
                        break;
                case 'X':
                        curr_code = CODE_X;
                        break;
                case 'Y':
                        curr_code = CODE_Y;
                        break;
                case 'Z':
                        curr_code = CODE_Z;
                        break;
/*                 case 'À':
                        curr_code = CODE_À;
                        break; */
/*                 case 'Å':
                        curr_code = CODE_Å;
                        break;
                case 'Ä':
                        curr_code = CODE_Ä;
                        break;
                case 'È':
                        curr_code = CODE_È;
                        break;
                case 'É':
                        curr_code = CODE_É;
                        break;
                case 'Ö':
                        curr_code = CODE_Ö;
                        break;
                case 'Ü':
                        curr_code = CODE_Ü;
                        break;
                case 'ß':
                        curr_code = CODE_ß;
                        break;
                case 'Ñ':
                        curr_code = CODE_Ñ;
                        break;*/
                case '1':
                        curr_code = CODE_1;
                        break;
                case '2':
                        curr_code = CODE_2;
                        break;
                case '3':
                        curr_code = CODE_3;
                        break;
                case '4':
                        curr_code = CODE_4;
                        break;
                case '5':
                        curr_code = CODE_5;
                        break;
                case '6':
                        curr_code = CODE_6;
                        break;
                case '7':
                        curr_code = CODE_7;
                        break;
                case '8':
                        curr_code = CODE_8;
                        break;
                case '9':
                        curr_code = CODE_9;
                        break;
                case '0':
                        curr_code = CODE_0;
                        break;
                case '.':
                        curr_code = CODE_PUNKT;
                        break;
                case ',':
                        curr_code = CODE_KOMMA;
                        break;
                case ':':
                        curr_code = CODE_COLON;
                        break;
                case ';':
                        curr_code = CODE_SEMIC;
                        break;
                case '?':
                        curr_code = CODE_QMARK;
                        break;
                case '!':
                        curr_code = CODE_EMARK;
                        break;
                case '-':
                        curr_code = CODE_MINUS;
                        break;
                case '_':
                        curr_code = CODE_UNDSC;
                        break;
                case '(':
                        curr_code = CODE_PAROP;
                        break;
                case ')':
                        curr_code = CODE_PARCL;
                        break;
                case '\'':
                        curr_code = CODE_SQUOT;
                        break;
                case '"':
                        curr_code = CODE_DQUOT;
                        break;
                case '=':
                        curr_code = CODE_EQUAL;
                        break;
                case '+':
                        curr_code = CODE_PLUSZ;
                        break;
                case '/':
                        curr_code = CODE_SLASH;
                        break;
                case '@':
                        curr_code = CODE_ATSYM;
                        break;
                case ' ':
                        curr_code = WORT_TREN;
                        break;
                default:
                        /*What to do in this situation?*/
                        printf("Unrecognized char '%c' (%i).", curr_char, curr_char);
                        break;
        }
        strcat(output, curr_code);
        next_char = input + 1;
        if(next_char != NULL && *(next_char) != '\0' && *(next_char) != '\n'){
                strcat(output, ZEICH_TREN);
                morse_encode(next_char, output);
        }
        else{
                strcat(output, "\0");
        }
        return 0;
}

int morse_decode(char * input, char * output)
{
        char * curr_code;
        char * curr_char;
        /*take input, find index of first ' '*/
        char * next_char_start = (strchr(input, ' '));
        /*store first char in curr_code*/
        size_t span = strspn(input, ".-/");
        curr_code = malloc((span+1) * sizeof(char));
        strncpy(curr_code, input, span);
        curr_code[span] = '\0';
        /*decode curr_code string*/
        switch(span)
        {
                case 0:
                        curr_char = "\0";
                        break;
                case 1:
                        if(strcmp(curr_code, CODE_E) == 0){
                                curr_char = "E";
                        }
                        else if(strcmp(curr_code, CODE_T) == 0){
                                curr_char = "T";
                        }
                        else if(strcmp(curr_code, WORT_TREN) == 0){
                                curr_char = " ";
                        }
                        break;
                case 2:
                        if(strcmp(curr_code, CODE_M) == 0){
                                curr_char = "M";
                        }
                        else if(strcmp(curr_code, CODE_N) == 0){
                                curr_char = "N";
                        }
                        else if(strcmp(curr_code, CODE_A) == 0){
                                curr_char = "A";
                        }
                        else if(strcmp(curr_code, CODE_I) == 0){
                                curr_char = "I";
                        }
                        break;
                case 3:
                        if(strcmp(curr_code, CODE_O) == 0){
                                curr_char = "O";
                        }
                        else if(strcmp(curr_code, CODE_G) == 0){
                                curr_char = "G";
                        }
                        else if(strcmp(curr_code, CODE_K) == 0){
                                curr_char = "K";
                        }
                        else if(strcmp(curr_code, CODE_D) == 0){
                                curr_char = "D";
                        }
                        else if(strcmp(curr_code, CODE_W) == 0){
                                curr_char = "W";
                        }
                        else if(strcmp(curr_code, CODE_R) == 0){
                                curr_char = "R";
                        }
                        else if(strcmp(curr_code, CODE_U) == 0){
                                curr_char = "U";
                        }
                        else if(strcmp(curr_code, CODE_S) == 0){
                                curr_char = "S";
                        }
                        break;
                case 4:
                        if(strcmp(curr_code, CODE_Q) == 0){
                                curr_char = "Q";
                        }
                        else if(strcmp(curr_code, CODE_Z) == 0){
                                curr_char = "Z";
                        }
                        else if(strcmp(curr_code, CODE_Y) == 0){
                                curr_char = "Y";
                        }
                        else if(strcmp(curr_code, CODE_C) == 0){
                                curr_char = "C";
                        }
                        else if(strcmp(curr_code, CODE_X) == 0){
                                curr_char = "X";
                        }
                        else if(strcmp(curr_code, CODE_B) == 0){
                                curr_char = "B";
                        }
                        else if(strcmp(curr_code, CODE_J) == 0){
                                curr_char = "J";
                        }
                        else if(strcmp(curr_code, CODE_P) == 0){
                                curr_char = "P";
                        }
                        else if(strcmp(curr_code, CODE_L) == 0){
                                curr_char = "L";
                        }
                        else if(strcmp(curr_code, CODE_F) == 0){
                                curr_char = "F";
                        }
                        else if(strcmp(curr_code, CODE_V) == 0){
                                curr_char = "V";
                        }
                        else if(strcmp(curr_code, CODE_H) == 0){
                                curr_char = "H";
                        }
/*                      else if(strcmp(curr_code, CODE_CH) == 0){
                                curr_char = "CH";
                        }
                        else if(strcmp(curr_code, CODE_Ö) == 0){
                                curr_char = "Ö";
                        }
                        else if(strcmp(curr_code, CODE_Ä) == 0){
                                curr_char = "Ä";
                        }
                        else if(strcmp(curr_code, CODE_Ü) == 0){
                                curr_char = "Ü"; 
                        }
*/
                        break;
                case 5:
                        if(strcmp(curr_code, CODE_0) == 0){
                                curr_char = "0";
                        }
                        else if(strcmp(curr_code, CODE_9) == 0){
                                curr_char = "9";
                        }
                        else if(strcmp(curr_code, CODE_8) == 0){
                                curr_char = "8";
                        }
/*                         else if(strcmp(curr_code, CODE_Ñ) == 0){
                                curr_char = "Ñ";
                        } */
                        else if(strcmp(curr_code, CODE_7) == 0){
                                curr_char = "7";
                        }
                        else if(strcmp(curr_code, CODE_PAROP) == 0){
                                curr_char = "(";
                        }
                        else if(strcmp(curr_code, CODE_SLASH) == 0){
                                curr_char = "/";
                        }
                        else if(strcmp(curr_code, CODE_EQUAL) == 0){
                                curr_char = "=";
                        }
                        else if(strcmp(curr_code, CODE_6) == 0){
                                curr_char = "6";
                        }
                        else if(strcmp(curr_code, CODE_1) == 0){
                                curr_char = "1";
                        }
/*                         else if(strcmp(curr_code, CODE_À) == 0){
                                curr_char = "À";
                        } */
                        else if(strcmp(curr_code, CODE_PLUSZ) == 0){
                                curr_char = "+";
                        }
/*                         else if(strcmp(curr_code, CODE_È) == 0){
                                curr_char = "È";
                        } */
                        else if(strcmp(curr_code, CODE_2) == 0){
                                curr_char = "2";
                        }
/*                         else if(strcmp(curr_code, CODE_É) == 0){
                                curr_char = "É";
                        } */
                        else if(strcmp(curr_code, CODE_3) == 0){
                                curr_char = "3";
                        }
                        else if(strcmp(curr_code, CODE_4) == 0){
                                curr_char = "4";
                        }
                        else if(strcmp(curr_code, CODE_5) == 0){
                                curr_char = "5";
                        }
                        break;
                case 6:
                        if(strcmp(curr_code, CODE_COLON) == 0){
                                curr_char = ":";
                        }
                        else if(strcmp(curr_code, CODE_KOMMA) == 0){
                                curr_char = ",";
                        }
                        else if(strcmp(curr_code, CODE_PARCL) == 0){
                                curr_char = ")";
                        }
                        else if(strcmp(curr_code, CODE_EMARK) == 0){
                                curr_char = "!";
                        }
                        else if(strcmp(curr_code, CODE_SEMIC) == 0){
                                curr_char = ";";
                        }
                        else if(strcmp(curr_code, CODE_MINUS) == 0){
                                curr_char = "-";
                        }
                        else if(strcmp(curr_code, CODE_SQUOT) == 0){
                                curr_char = "'";
                        }
                        else if(strcmp(curr_code, CODE_ATSYM) == 0){
                                curr_char = "@";
                        }
                        else if(strcmp(curr_code, CODE_PUNKT) == 0){
                                curr_char = ".";
                        }
                        else if(strcmp(curr_code, CODE_DQUOT) == 0){
                                curr_char = "\"";
                        }
                        else if(strcmp(curr_code, CODE_UNDSC) == 0){
                                curr_char = "_";
                        }
                        else if(strcmp(curr_code, CODE_QMARK) == 0){
                                curr_char = "?";
                        }
/*                         else if(strcmp(curr_code, CODE_ß) == 0){
                                curr_char = "ß";
                        } */
                        break;
                default:
                        /*What to do in this situation?*/
                        printf("Non-supported character.\n");
                        break;
        }              
        /*append char to output*/
        strcat(output, curr_char);
        free(curr_code);
        /*call again with (pointer to start of next char code, output)*/
        if(next_char_start != NULL){
                if(*(next_char_start + 1) != '\n'){
                        morse_decode((next_char_start + 1), output);
                }                
        }
        return 0;
}