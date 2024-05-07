#include "main.h"

int error = 0;
extern int flower_bracket;

/* lexical_analyser analyses file content */
int lexical_analyser(char * file_name) {
    // Open the file for reading
    FILE *file = fopen(file_name, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1; 
    }


    printf("---------------------------------------------------\n");
    printf("LEXICAL ANALYSER RESULTS\n");
    printf("---------------------------------------------------\n");

    char line[1000];
    
    // Flag to indicate if currently in a multi-line comment
    // int multi_line = 0;

    // Read and process each line until the end of file is reached
    while ( (!error) && fgets(line, sizeof(line), file) != NULL) {

        
        //comparing for macro or preprocessor
        // if(line[0] == '#' && (!multi_line)){
        //     //comparing for preprocessor
        //     if(strncmp(line,"#include", 8) == 0){
        //         printf("Preprocessor directive - %s\n", line);
        //     }
        //     //comparing for macro
        //     else if(strncmp(line, "#define",7) == 0){
        //         printf("MACRO - %s\n", line);
        //     }
        // }


        // // Print the current line
        
        // else if (line[0] == '/' && line[1] == '*' )
        // {
        //     printf("Multi line comment\n");
            
        //     multi_line = 1; // Set flag to indicate multi-line comment
            
        //     // Print the current line
        //     printf("%s",line);

        //     int in = 0;

        //     // Loop until end of line is reached
        //     while(line[in] != '\0') 
        //     {
        //         // Checking for end of multi-line comment
        //         if(line[in] == '*' && line[in + 1] == '/')
        //         {
        //             // Reset flag
        //             multi_line = 0;
        //         }
        //         in++;
        //     }
        // }

        // // Continue processing if inside a multi-line comment
        // else if(multi_line) {
        //     printf("%s",line);
        //     int in = 0;

        //     // Loop until end of line is reached
        //     while(line[in] != '\0') 
        //     {
        //         // Checking for end of multi-line comment
        //         if(line[in] == '*' && line[in + 1] == '/')
        //         {
        //             multi_line = 0;
        //         }
        //         in++;
        //     }
        // }
        
        
        // Perform further analysis on the line
        analyse(line);
        
            

    }

    // Check if flower brackets are balanced
    if( ( flower_bracket != 0 ) &&  !error){
        printf("Error : Flower bracket not balanced\n");
    }

    // Close the file
    fclose(file);

}