#include <stdio.h>
#include <stdlib.h>
#include "csv.h"

int openCSV(csv_file *csv){
    csv->fcsv = fopen("communes_distrib.csv","rb");
    return EXIT_SUCCESS;
}

int getRecordCSV(csv_file *csv){
    return EXIT_SUCCESS;
}

int printRecordCSV(csv_file *csv){
    return EXIT_SUCCESS;
}

int printFieldmaxCSV(csv_file *csv){
    return EXIT_SUCCESS;
}

int closeCSV(csv_file *csv){
    return EXIT_SUCCESS;
}