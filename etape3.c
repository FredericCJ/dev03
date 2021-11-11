#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>
#include "config.h"
#include "csv.h"
#include "commune.h"

bool is_number(char *parameter);

int main(int argc, char *argv[]){
    if(argc < 4){
        fprintf(stderr,"%s: too few arguments\n\n",argv[0]);
        fprintf(stdout,"Usage:\n\t%s <latitude> <longitude> <distance>\n",argv[0]);
        exit(1);
    }
    if(argc > 4){
        fprintf(stderr,"%s: too many arguments\n\n",argv[0]);
        fprintf(stdout,"Usage:\n\t%s <latitude> <longitude> <distance>\n",argv[0]);
        exit(2);
    }
    if(is_number(argv[1]) == false){
        fprintf(stderr,"invalid argument\n\n");
        fprintf(stdout,"Usage:\n\t%s: latitude must be a number in [-180.0 ; 180.0]\n",argv[0]);
        exit(3);
    }
    if(is_number(argv[2]) == false){
        fprintf(stderr,"invalid argument\n\n");
        fprintf(stdout,"Usage:\n\t%s: longitude must be a number in [-180.0 ; 180.0]\n",argv[0]);
        exit(4);
    }
    if(is_number(argv[3]) == false){
        fprintf(stderr,"invalid argument\n\n");
        fprintf(stdout,"Usage:\n\t%s: distance must be a number in [0.0 ; 19999.0]\n",argv[0]);
        exit(5);
    }
    return EXIT_SUCCESS;
}

bool is_number(char *parameter){
    char *number_pattern = "^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$";
    regex_t regex;
    int err;

    err = regcomp(&regex, number_pattern, REG_EXTENDED);
    err = regexec(&regex, parameter, 0, NULL, 0);

    if (err==0){
            return true;
        }
    return false;
}