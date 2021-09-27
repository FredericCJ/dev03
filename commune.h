#ifndef COMMUNE_H
#define COMMUNE_H

#include "csv.h"

typedef struct commune_info{
    char nom_commune[COMMUNE_MAXLEN];
    double latitude;
    double longitude;
    int nb_champs;
    int nb_valeures;
    int nb_vides;
}commune_info;

int record_cnt(csv_file *csv, commune_info *commune);
int commune_init(commune_info *commune);

#endif