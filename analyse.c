#include "main.h"

extern int error;

int flower_bracket = 0;
static int square_bracket = 0;
static int bracket = 0;

// An array of strings for C keywords
const char* keywords[32] = {
        "auto", "break", "case", "char", "const", "continue", "default", "double" ,"do",
        "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};


// Function to analyze a line of text
int analyse(char *line) {
    int i = 0;

    // Skip leading spaces
    while (line[i] == ' ') {
        line++; // Move the pointer forward until a non-space character is encountered
    }

    // // Checking for single line comments
    // if(line[0] == '/' && line[1] == '/') {
    //     printf("Single line comment - %s",line);
    //     return 0;
    // }

    int ret = 0;
    // Loop to analyze keywords in the line
    while (ret = keyword(line)) {
        line = line + ret; // Move the pointer to the next character after the keyword
    }

    // Call function to identify other components of the line
    identify(line);
}



// Function to identify keywords in the given line of text
int keyword(char * line) {
    int i;

    // Iterate through the array of keywords
    for(i = 0; i < 32; i++) {
        // Compare the current keyword with the beginning of the line
        if (strncmp(line, keywords[i], strlen(keywords[i])) == 0) {

            // If the keyword matches, print it and return its length
            printf("%10s - Keyword\n", keywords[i]);
            return strlen(keywords[i]);
        }
    }
    
    return 0;
}

/* checks for special character */
int isSpecialChar(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' ||
            c == '&' || c == '|' || c == ' ' || c == '\t' || c == '\n' ||
            c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' ||
            c == '"' || c == '\'' || c == ':' || c == ';');
}

/* checks for brackets */
int isBracket(char c) {
    return (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}');
}

/* checks for operators */
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '=' || c == '<' || c == '>' || c == '&' ||
            c == '|' || c == ',' );
}


/* checks string is digits string or not */
int isNumber(char* str) {
    // Check if the string is empty
    if (str == NULL || *str == '\0') {
        return 0;
    }
    int flag = 0;
    if(*str >= '0' && *str <= '9'){
        flag = 1;
    
        // Check each character of the string
        while (*str != '\0') {
            // If the character is not a digit, return 0
            if (!(*str >= '0' && *str <= '9' 
                || *str == '.' || *str == 'f' || *str == 'L' || *str == 'l' ||
                *str == 'x' || *str == 'X')) {
                if(flag) return 2;
                return 0;
            }
            str++; // Move to the next character
        }
    }
    else return 0;
    // If all characters are digits, return 1
    return 1;
}

/* checks for balance of parenthesis */
int parenthesis_checker(char ch) {
    /*
    increment for open bracket 
    decrement for close bracket
    */
    switch (ch)
    {
    case '(': bracket++;
        break;
    case ')' : bracket--;
        break;
    case '{' : flower_bracket++;
        break;
    case '}' : flower_bracket--;
        break;
    case '[' : square_bracket++; 
        break;
    case ']' : square_bracket--;
        break;
    }

}




// function to identify other components of the line
int identify(char * line)
{
    
    char str[10];
    int i = 0, j = 0;

    // Iterate through each character in the line until end of string
    while(line[i] != '\0') 
    {
        // If the current character is a special character
        if(isSpecialChar(line[i]) && j>0) 
        {
            str[j] = '\0';

            if(isNumber(str) == 2) {
                printf("Error : %s\n",str);
                error = 1;
                return 1;
            }
            // Check if the string is a number or an identifier
            else if(isNumber(str)) 
            {
                printf("%10s - constant\n", str);
            }
            else 
            {
                printf("%10s - Identifier\n",str);
            }
            
            j = 0;
            str[j] = '\0';
        }

        // If the current character is a bracket
        if(isBracket( line[i] )) 
        {
            // Check for balanced brackets
            parenthesis_checker(line[i]); 

            printf("%10c - Bracket\n", line[i++]);
        }

        // If the current character is a space, skip it
        else if( line[i] == ' ' ) i++;

        // If the current character is an operator
        else if( isOperator( line[i] ) ) 
        {
            if(line[i] == '+' && line[i+1] == '+') {
                printf("%10c%c - operator\n",line[i],line[i+1]);
                i=i+2;
            }
            else if(line[i] == '-' && line[i+1] == '-') {
                printf("%10c%c - operator\n",line[i],line[i+1]);
                i=i+2;
            }
            else 
                printf("%10c - Operator\n",line[i++]);
        }

        // If the current character is a semicolon
        else if(line[i] == ';') {
            printf("%10c - Semicolon\n", line[i++]);
        }

        // If the current character is a colon
        else if(line[i] == ':') {
            printf("%10c - Colon\n", line[i++]);
        }

        // If the current character is a double inverted comma
        else if(line[i] == '"'){
            printf("%10c - Double inverted coma\n",line[i++]);

            char data[100];
            int k=0;

            // Extract characters until the closing double inverted comma is found
            while(line[i] != '"' && line[i] != '\0') {
                data[k++] = line[i++];
            }
            data[k] = '\0';

            //if double inverted coma is not balanced
            if(line[i] == '\0') {
                printf("Error : double inverted comma not closed\n");
                error = 1;
                return 0;
            }

            printf("%10s - data\n",data);

            printf("%10c - Double inverted coma\n", line[i++]);
        }

        // If the current character is a single inverted comma
        else if(line[i] == '\'') {
            printf("%10c - Single inverted coma\n", line[i++]);
            
            char data[100];
            int k=0;
            // Extract characters until the closing single inverted comma is found
            while(line[i] != '\'' && line[i] != '\0') {
                data[k++] = line[i++];
            }
            data[k] = '\0';

            //if single inverted coma is not balanced
            if(line[i] == '\0') {
                printf("Error : single inverted comma not closed\n");
                error = 1;
                return 0;
            }

            printf("%10s - data\n",data);

            printf("%10c - Single inverted coma\n", line[i++]);

        }

        // If the current character is a regular character
        else 
        {
            str[j++] = line[i++];
        }

        
    }


    // Check for unbalanced brackets at the end of processing
    if(bracket != 0 && !error) {
        printf("Error : Bracket not balanced\n");
        error = 1;
        bracket = 0;
        
    }
    else if( ( square_bracket != 0 )  &&  !error) {
        printf("Error : Square bracket not balanced\n");
        error = 1;
        square_bracket = 0;
       
    }

    

}







