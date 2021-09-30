#ifndef COMMUNE_H
#define COMMUNE_H

#include "csv.h"

typedef struct commune_info{
    char nom_commune[COMMUNE_MAXLEN];
    double latitude;
    double longitude;
}commune_info;

int valid_record(csv_file *csv);
int commune_init(commune_info *commune);

#endif