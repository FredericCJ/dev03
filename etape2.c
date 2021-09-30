#include <stdio.h>
#include<stdlib.h>
#include "config.h"
#include "csv.h"
#include "commune.h"

int main(){
    csv_file csv;
    commune_info commune;
    int nb_valeures = 0;

    commune_init(&commune);
    openCSV(&csv);
    csv.read_header = true;
    
    if(csv.is_open){
        while(getRecordCSV(&csv) == 0 && csv.read_header == false){
            nb_valeures = nb_valeures+valid_record(&csv);
        }    
    }

    closeCSV(&csv);

    printf("%6d champs\n%6d valeures\n%6d champs vides\n",
        CSV_FIELDCNT*csv.line_counter,
        nb_valeures,
        CSV_FIELDCNT*csv.line_counter-nb_valeures);

    return EXIT_SUCCESS;
}