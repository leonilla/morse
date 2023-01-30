/*Funktionen, die Benutzereingabe und Ausgabe behandeln.
Validierung von Kommandozeile Parametern, Ausgabe von Menüs und Hilfe Seiten, 
Ausgabe von Prompten und Einlesen von Benutzereingabe gehören in dieser Datei.*/
#include "files.h"
#include "morse.h"

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

#define EXIT_COMMND "exit()"
#define EXIT -1

void flush(void);
char *read_input(char *input);
int input_filenames(char **filename_in, char **filename_out);
int main_menu();
int launch_interactive();
int validate_syntax(int argc, char *argv[]);
void show_help();
void show_hint();
