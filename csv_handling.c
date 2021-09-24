#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "csv.h"

int openCSV(csv_file *csv){
    csv->fcsv = fopen(CSV_FILENAME,"r");
    csv->is_open = true;
    csv->line_counter = 0;
    csv->fieldcnter = 0;
    return EXIT_SUCCESS;
}

int getRecordCSV(csv_file *csv){
    char c = '\0';
    while(c != EOF){
        if(csv->read_header = true && c == '\n')
            csv->read_header = false;
        if(c == '\n')
            csv->line_counter++;
        c = fgetc(csv->fcsv);
    }

    /*if(feof(csv->fcsv))
        return EXIT_FAILURE;
    if(fgetc(csv->fcsv) == ',')
        csv->fieldcnter++;
    if(csv->fieldcnter == CSV_FIELDCNT){
        csv->line_counter++;
        csv->fieldcnter = 0;
    }*/
    return EXIT_SUCCESS;
}

int printRecordCSV(csv_file *csv){
    printf("%d",csv->line_counter);
    return EXIT_SUCCESS;
}

int printFieldmaxCSV(csv_file *csv){
    return EXIT_SUCCESS;
}

int closeCSV(csv_file *csv){
    fclose(csv->fcsv);
    csv->is_open = false;
    return EXIT_SUCCESS;
}