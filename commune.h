#ifndef COMMUNE_H
#define COMMUNE_H

#define GPS_VALID(x) ((x>=-180.0) && (x<=180.0))

#include "csv.h"

typedef struct commune_info{
    char nom_commune[COMMUNE_MAXLEN];
    double latitude;
    double longitude;
}commune_info;

int commune_init(commune_info *commune);
bool valid_commune(csv_file *csv, commune_info *commune);

#endif