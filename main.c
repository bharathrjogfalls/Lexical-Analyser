/*
Name           : Bharath R
Date           : 4/5/2024
Project name   : Lexical analyser
Description    : Analyse the c file and idntifies the kewords, identifiers, constants, operators, brackets,
                colons, double and single inverted coma, etc.
*/

#include "main.h"


int main(int argc, char ** argv) {
    if(argc == 2){
        lexical_analyser(argv[1]);
    }
    else printf("please provide:\n ./a.out (file_name)\n");
    
    return 0; 
}

