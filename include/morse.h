/* Funktionen, die sich mit Codieren bzw. Decodieren von Nachrichten beschäftigen.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "morsetabelle.h"
#include "files.h"

int morse_encode(char * input, char * output);
int morse_decode(char * input, char * output);
int file_encode(char * file_in, char * file_out);
int file_decode(char * file_in, char * file_out);