#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "config.h"

extern int errno;
extern int randint(int upper, int lower);

#define VERSION "0.1"

void input_handler(int argc, char *argv[], int *len, int *amount){
    // Error handeling
    if (argc > 3){
        // E2BIG 7 Argumgent list too long
        errno = 7;
        perror("passwdgen");
        exit(errno);
    // I'm very sorry future me for this:
    } else if (argc == 3 && ((!strcmp(argv[1], "-h") || !strcmp(argv[2], "-h") || (!strcmp(argv[1], "-v") || !strcmp(argv[2], "-v"))))){
        // EINVAL 22 Invalid argument
        errno = 22;
        perror("passwdgen");
        exit(errno);
    } else if (argc == 1){
        // EINVAL 22 Invalid argument
        errno = 22;
        perror("passwdgen");
        exit(errno);
    }

    // Optional args
    if (!strcmp(argv[1], "-h")){
        printf("\
Usage: passwdgen LEN AMNT\n\
\n\
Mandatory arguments:\n\
  LEN       the length of the password(s) that will be generated\n\
  AMNT      the amount of password to be generated\n\
\n\
Optional arguments:\n\
  -h        print this message and exit\n\
  -v        print the passwdgen version number and exit\n\
\n\
If an optional argument is given none of the mandatory arguments are allowed\n");
        exit(0);
    } else if(!strcmp(argv[1], "-v")){
        printf("passwdgen %s\n", VERSION);
        exit(0);
    }

    // Check if all 2 mandatory arguments are given
    /*
        It is checking this after all of the other errors because it had
        to check for single optional arguments
    */
    if (argc < 3){
        // EINVAL 22 Invalid argument
        errno = 22;
        perror("passwdgen");
        exit(errno);
    }
    // Mandatory args
    // LEN - password length
    *len = atoi(argv[1]);
    if (*len == 0){
        // EINVAL 22 Invalid argument
        errno = 22;
        perror("passwdgen");
        exit(errno);
    // len_cap is defined in config.h
    } if (*len >= len_cap){
        // EOVERFLOW 75 Value too large for defined data type
        errno = 75;
        perror("passwdgen");
        exit(errno);
    }
    // AMNT - password amount
    *amount = atoi(argv[2]);
    if (*amount == 0){
        // EINVAL 22 Invalid argument
        errno = 22;
        perror("passwdgen");
        exit(errno);
    // amount_cap is defined in config.h
    } if (*amount >= amount_cap){
        // EOVERFLOW 75 Value too large for defined data type
        errno = 75;
        perror("passwdgen");
        exit(errno);
    }
}

int main(int argc, char *argv[]){
    int len;
    int amount;
    int counter1;
    int counter2;

    // Collect user input
    input_handler(argc, argv, &len, &amount);

    // Use const char *characters from config.h
    int charter_array_len = strlen(characters);

    // Repeat for the amount of passwords
    for(counter1 = 0; counter1 < amount; counter1++){
        // Repeat for the length of the password(s)
        for(counter2 = 0; counter2 < len; counter2++){
            // Grab a random character from the characters array
            printf("%c", characters[randint(charter_array_len, 0)]);
        }
        printf("\n");
    }
    return 0;
}
