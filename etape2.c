#include <stdio.h>
#include<stdlib.h>
#include "config.h"
#include "csv.h"
#include "commune.h"

int main(){
    csv_file csv;
    int nb_records;
    nb_records = record_cnt(&csv);
    printf("%6d champs\n%6d valeures\n%6d champs vides\n",CSV_FIELDCNT*csv.line_counter,nb_records,CSV_FIELDCNT*csv.line_counter-nb_records);
    return EXIT_SUCCESS;
}