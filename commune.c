#include <stdlib.h>
#include "csv.h"
#include "commune.h"
#include "config.h"

int commune_init(commune_info *commune){
    commune->nom_commune[0] = '\0';
    commune->latitude = 0;
    commune->longitude = 0;
    commune->nb_champs = 0;
    commune->nb_valeures = 0;
    commune->nb_vides = 0;
    return EXIT_SUCCESS;
}

int record_cnt(csv_file *csv, commune_info *commune){

    openCSV(csv);
    csv->read_header = true;
    if (csv->is_open) {
        while(getRecordCSV(csv) == 0){
            for(int i=0 ; i<CSV_FIELDCNT ; i++){
                if(csv->record[i][0] != '\0')
                    commune->nb_valeures++;
            }
        }
    }
    closeCSV(csv);
    return EXIT_SUCCESS;
}