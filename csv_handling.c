#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "csv.h"

int openCSV(csv_file *csv){
    csv->fcsv = fopen(CSV_FILENAME,"r");
    csv->is_open = true;
    csv->line_counter = 0;
    csv->max_field = 0;
    csv->max_len = 0;
    return EXIT_SUCCESS;
}

int getRecordCSV(csv_file *csv){
    getMaxima(csv);
    getHeader(csv);
    return EXIT_SUCCESS;
}

int printRecordCSV(csv_file *csv){
    int j = 0;
    for(int i=0 ; i<15 ; i++){
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
    printf("Taille max champ = %d\n",csv->max_field);
    return EXIT_SUCCESS;
}

int closeCSV(csv_file *csv){
    fclose(csv->fcsv);
    csv->is_open = false;
    return EXIT_SUCCESS;
}

int getMaxima(csv_file *csv){
    int field_len = 0;
    int line_len = 0;
    char c = '\0';
    while(c != EOF){
        if(c == ',' || c == '\n'){
            if(field_len >= csv->max_field)
                csv->max_field = field_len;
            field_len = 0;
        }
        if(c == '\n'){
            csv->line_counter++;
            if(line_len >= csv->max_len)
                csv->max_len = line_len;
            line_len = 0;
        }
        c = fgetc(csv->fcsv);
        line_len++;
        field_len++;
    }

    fseek(csv->fcsv,0,SEEK_SET);
    
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