#include <stdlib.h>
#include "csv.h"
#include "commune.h"
#include "config.h"

int commune_init(commune_info *commune){
    commune->nom_commune[0] = '\0';
    commune->latitude = 0;
    commune->longitude = 0;
    return EXIT_SUCCESS;
}

int valid_record(csv_file *csv){
    int nb_valid = 0;
        for(int i=0 ; i<CSV_FIELDCNT ; i++){
            if(csv->record[i][0] != '\0'){
                nb_valid++;
            }
        }
    return nb_valid;
}