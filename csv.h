#ifndef CSV_H
#define CSV_H

#include <stdbool.h>

typedef struct csv_file{
    FILE *fcsv;
    bool is_open;
    bool read_header;
    int fieldcnter;
    int line_counter;
    int max_len;
} csv_file;

int openCSV(csv_file *csv);
int getRecordCSV(csv_file *csv);
int printRecordCSV(csv_file *csv);
int printFieldmaxCSV(csv_file *csv);
int closeCSV(csv_file *csv);

#endif
