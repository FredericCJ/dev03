#ifndef CONFIG_H
#define CONFIG_H

#define CSV_FILENAME "communes.csv"
#define STRING_DELIM '"'
#define CSV_DELIM ','
#define CSV_FIELDCNT 15

#define OUT_OF_FIELD 0
#define QUOTED_FIELD 1
#define UNQUOTED_FIELD 2
#define ON_CSV_DELIM 3
#define ON_EOL 4

#define COMMUNE_MAXLEN 50
#define LIGNE_5_MAXLEN 50
#define COMMUNE_CHAMP_LATITUDE 14
#define COMMUNE_CHAMP_LONGITUDE 18

#endif
