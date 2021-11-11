#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "csv.h"
#include "commune.h"



int main(){
    csv_file csv;
    commune_info commune;
    int nb_record_with_valid_gps = 0;

    commune_init(&commune);
    if(openCSV(&csv) !=0)
        exit(1);
    csv.read_header = true;
    
    if(csv.is_open){
        while(getRecordCSV(&csv) == 0 && csv.read_header == false){
            if(valid_gps(&csv, &commune) == true){
                nb_record_with_valid_gps++;
            }
        }    
    }

    if(closeCSV(&csv) != 0)
        exit(1);

    printf("%48s %6d\n%48s %6d\n",
        "Nombre total d'enregistrements:--------------------:",
        csv.line_counter,
        "Enregistrements avec des coordonnées gps valides:--:",
        nb_record_with_valid_gps);

    return EXIT_SUCCESS;
}