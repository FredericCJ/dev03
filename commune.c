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
        for(int i=0 ; i<CSV_FIELDCNT ; i++){
            if(csv->record[i][0] != '\0')
                return 1;
        }
    return 0;
}