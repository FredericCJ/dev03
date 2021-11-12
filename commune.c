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

bool valid_commune(csv_file *csv, commune_info *commune){

    if(strcmp(csv->record[5],"") != 0)
        commune->latitude = atof(csv->record[5]);
    else
        return false;

    if(strcmp(csv->record[6],"") != 0)
        commune->longitude = atof(csv->record[6]);
    else
        return false;

    if(GPS_VALID(commune->latitude) && GPS_VALID(commune->longitude)){
        strcpy(commune->nom_commune,csv->record[10]);
        return true;
    }
    return false;
}
