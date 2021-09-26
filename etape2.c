#include <stdio.h>
#include<stdlib.h>
#include "config.h"
#include "csv.h"

int main(){
    csv_file csv;
    openCSV(&csv);
    csv.read_header = true;
    if (csv.is_open) {
        while ( getRecordCSV(&csv) == 0 ) {

            if ((csv.line_counter > 0) && (csv.line_counter <= 3)) {
               printRecordCSV(&csv);
               printf("\n");
            }
        }
    }
    closeCSV(&csv);
    return EXIT_SUCCESS;
}