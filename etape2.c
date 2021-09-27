#include <stdio.h>
#include<stdlib.h>
#include "config.h"
#include "csv.h"
#include "commune.h"

int main(){
    csv_file csv;
    commune_info commune;

    commune_init(&commune);

    record_cnt(&csv,&commune);
    printf("%6d champs\n%6d valeures\n%6d champs vides\n",
        CSV_FIELDCNT*csv.line_counter,
        commune.nb_valeures,
        CSV_FIELDCNT*csv.line_counter-commune.nb_valeures);

    return EXIT_SUCCESS;
}