#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "csv.h"

int
main (void)
{
  int err;
  csv_file csv;

  if ((err = openCSV (&csv)) != 0)
    {
      fprintf (stderr, "Couldn't open %s: %s\n", CSV_FILENAME, strerror (err));
      exit (err);
    }
  csv.read_header = true;

  if (csv.is_open)
    {
      while (getRecordCSV (&csv) == 0)
        {

          if ((csv.line_counter > 0) && (csv.line_counter <= 3))
            {
              printRecordCSV (&csv);
              printf ("\n");
            }
        }

      printf ("Taille ligne max = %d\n", csv.max_len);
      printf ("Nombre lignes = %d\n", csv.line_counter);

      printFieldmaxCSV (&csv);
      printf ("\n");

      closeCSV (&csv);
    }

  return EXIT_SUCCESS;
}
