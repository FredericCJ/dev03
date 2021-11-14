#ifndef ETAPE3_H
#define ETAPE3_H

#include "commune.h"
#include "csv.h"
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DISTANCE_VALID(x) ((x >= 0.0) && (x <= 19999.0))
#define RAD(x) ((x)*M_PI / 180.0)

bool is_number (char *string);
int print_communes_within_range (commune_info *commune, double latitude,
                                 double longitude, double distance);
double distance_to_reference (commune_info *commune, double latitude_ref,
                              double longitude_ref);

#endif

#ifndef M_PI
#define M_PI acos (-1.0)
#endif
