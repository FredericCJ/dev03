#ifndef CSV_H
#define CSV_H

#include <stdbool.h>

typedef struct csv_file{
    FILE *fcsv;
    bool is_open;
    bool read_header;
    int line_counter; 
    int max_len; //inclu '\n'

    char fields_maxlen[CSV_FIELDCNT];
    char header[CSV_FIELDCNT][50];
    char record[CSV_FIELDCNT][50];
} csv_file;

int openCSV(csv_file *csv);
int getRecordCSV(csv_file *csv);
int printRecordCSV(csv_file *csv);
int printFieldmaxCSV(csv_file *csv);
int closeCSV(csv_file *csv);
int getHeader(csv_file *csv);

#endif
