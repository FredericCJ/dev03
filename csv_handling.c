#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "csv.h"

int openCSV(csv_file *csv){
    csv->fcsv = fopen(CSV_FILENAME,"r");
    csv->is_open = true;
    csv->line_counter = 0;
    csv->max_len = 0;
    for(int i=0 ; i<CSV_FIELDCNT ; i++)
        csv->fields_maxlen[i] = 0;
    return EXIT_SUCCESS;
}

int getRecordCSV(csv_file *csv){
    char c = '\0';
    int line_len = 0;
    int field_len = 0;
    int field_num = 0;
    
    getHeader(csv);
    
    while(c != EOF){
        c = fgetc(csv->fcsv);
        line_len++;
        field_len++;
        
        if(c == ',' || c == '\n'){
            if(field_len-1 >= csv->fields_maxlen[field_num])
                csv->fields_maxlen[field_num] = field_len-1;
            field_num++;
            field_len = 0;
        }
        
        if(c == '\n'){
            csv->line_counter++;
            if(line_len >= csv->max_len)
                csv->max_len = line_len;
            line_len = 0;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int printRecordCSV(csv_file *csv){
    int j = 0;
    for(int i=0 ; i<CSV_FIELDCNT ; i++){
        while(csv->header[i][j] != '\0'){
            printf("%c",csv->header[i][j]);
            j++;
        }
        j = 0;
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int printFieldmaxCSV(csv_file *csv){
    int j = 0;
    printf("+--------------------------------------+\n");
    printf("| Nom champ               | Taille max |\n");
    printf("|--------------------------------------|\n");
    for(int i=0 ; i<CSV_FIELDCNT ; i++){
        printf("| ");
        while(csv->header[i][j] != '\0'){
            printf("%c",csv->header[i][j]);
            j++;
        }
        while(j < 24){
            printf(" ");
            j++;
        }
        printf("|     %2d     |",csv->fields_maxlen[i]);
        j = 0;
        printf("\n");
    }
    printf("+--------------------------------------+\n");
    return EXIT_SUCCESS;
}

int closeCSV(csv_file *csv){
    fclose(csv->fcsv);
    csv->is_open = false;
    return EXIT_SUCCESS;
}

int getHeader(csv_file *csv){
    char c = '\0';
    int field_pos = 0;
    int field_num = 0;

    if(csv->read_header == true){
        while(c != '\n'){
            c = fgetc(csv->fcsv);
            if(c == ',' || c == '\n'){
                csv->header[field_num][field_pos] = '\0';
                field_num++;
                field_pos = 0;
            }
            if(c != ','){
                csv->header[field_num][field_pos] = c;
                field_pos++;
            }
        }
        csv->read_header = false;
    }
    return EXIT_SUCCESS;
}