/* Funktionen, die sich mit Codieren bzw. Decodieren von Nachrichten beschäftigen.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "morsetabelle.h"
#include "files.h"

char *encode_char(char input);
char *encode_string(char *input);
int encode_file(char *file_in, char *file_out);

char *decode_char(char *input);
char *decode_string(char *input);
int decode_file(char *file_in, char *file_out);