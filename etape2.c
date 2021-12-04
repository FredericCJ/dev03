#include "commune.h"
#include "config.h"
#include "csv.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  csv_file csv;
  commune_info commune;
  int nb_record_with_valid_gps = 0;
  int err;

  commune_init (&commune);
  if ((err = openCSV (&csv)) != 0)
    {
      fprintf (stderr, "Couldn't open %s: %s\n", CSV_FILENAME, strerror (err));
      exit (err);
    }
  csv.read_header = true;

  if (csv.is_open)
    {
      while (getRecordCSV (&csv) == 0 && csv.read_header == false)
        {
          if (valid_commune (&csv, &commune) == true)
            {
              nb_record_with_valid_gps++;
            }
        }
    }

  if (closeCSV (&csv) != 0)
    exit (1);

  printf (
      "%48s %6d\n%48s %6d\n",
      "Nombre total d'enregistrements:--------------------:", csv.line_counter,
      "Enregistrements avec des coordonnées gps valides:--:",
      nb_record_with_valid_gps);

  return EXIT_SUCCESS;
}
