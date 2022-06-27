#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"

typedef enum {true, false} bool;

#define VERSION "0.1"

void input_handler(int argc, char *argv[], int *len, int *amount, bool *outfile, int *outfile_location){
    // Error handeling
    if (argc > 5){
        fprintf(stderr, "passwdgen: Too many arguments\n");
        exit(EXIT_FAILURE);
    // I'm very sorry future me for this:
    } else if ((argc >= 3) && ((!strcmp(argv[1], "-h") || !strcmp(argv[2], "-h") || (!strcmp(argv[1], "-v") || !strcmp(argv[2], "-v"))))){
        fprintf(stderr, "passwdgen: Invalid argument\n");
        exit(EXIT_FAILURE);
    } else if (argc == 1){
        fprintf(stderr, "passwdgen: Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    // Optional args
    if (!strcmp(argv[1], "-h")){
        printf("\
Usage: passwdgen LEN AMNT <option>\n\
\n\
Mandatory arguments:\n\
\tLEN\tthe length of the password(s) that will be generated\n\
\tAMNT\tthe amount of password to be generated\n\
\n\
Optional arguments:\n\
\t-h\tprint this message and exit\n\
\t-v\tprint the passwdgen version number and exit\n\
\t-of\twrites the passwords to a file\n");
        exit(EXIT_SUCCESS);
    } else if(!strcmp(argv[1], "-v")){
        printf("passwdgen %s\n", VERSION);
        exit(EXIT_SUCCESS);
    }

    // Check if all 2 mandatory arguments are given
    /*
        It is checking this after all of the other errors because it had
        to check for single optional arguments
    */
    if (argc < 3){
        fprintf(stderr, "passwdgen: Not enough arguments\n");
        exit(EXIT_FAILURE);
    }
    // Mandatory args
    // LEN - password length
    *len = atoi(argv[1]);
    if (*len == 0){
        fprintf(stderr, "passwdgen: Password length invalid\n");
        exit(EXIT_FAILURE);
    // len_cap is defined in config.h
    } if (*len >= len_cap){
        fprintf(stderr, "passwdgen: Password length too large\n");
        exit(EXIT_FAILURE);
    }
    // AMNT - password amount
    *amount = atoi(argv[2]);
    if (*amount == 0){
        fprintf(stderr, "passwdgen: Password amount invalid\n");
        exit(EXIT_FAILURE);
    // amount_cap is defined in config.h
    } if (*amount >= amount_cap){
        fprintf(stderr, "passwdgen: Password amount too large\n");
        exit(EXIT_FAILURE);
    }

    // Out file
    if (argc == 5){
        for (int i=0; i<argc; i++){
            if (!strcmp(argv[i], "-of")){
                *outfile_location = i+1;
                *outfile = true;
                break;
            }
        }
    }
}

int main(int argc, char *argv[]){
    int len;
    int amount;
    int counter1;
    int counter2;
    bool outfile = false;
    int outfile_location;

    // Collect user input
    input_handler(argc, argv, &len, &amount, &outfile, &outfile_location);
    // Use const char *characters from config.h
    int charter_array_len = strlen(characters);

    if (outfile == true){
        // Open a file for writing
        FILE *fp;
        fp = fopen(argv[outfile_location], "w");

        // Repeat for the amount of passwords
        srand(time(0));
        for(counter1 = 0; counter1 < amount; counter1++){
            // Repeat for the length of the password(s)
            for(counter2 = 0; counter2 < len; counter2++){
                // Grab a random character from the characters array
                int randint;
                randint = rand() % charter_array_len;
                // Instead of writing it to stdout write it to a file
                fprintf(fp, "%c", characters[randint]);
            }
            fprintf(fp, "\n");
        }
    } else {
        // Repeat for the amount of passwords
        srand(time(0));
        for(counter1 = 0; counter1 < amount; counter1++){
            // Repeat for the length of the password(s)
            for(counter2 = 0; counter2 < len; counter2++){
                // Grab a random character from the characters array
                int randint;
                randint = rand() % charter_array_len;
                printf("%c", characters[randint]);
            }
            printf("\n");
        }
    }
    return 0;
}
