#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "config.h"
#include "csv.h"

int main( void )
{
   csv_file csv;

   openCSV(&csv);
   csv.read_header = true;

   if (csv.is_open) {
      while ( getRecordCSV(&csv) ) {

            if ((csv.line_counter > 0) && (csv.line_counter <= 3)) {
               printRecordCSV(&csv);
               printf("\n");
            }
      }

      printf("Taille ligne max = %d\n", csv.max_len);
      printf("Nombre lignes = %d\n", csv.line_counter);

      printFieldmaxCSV(&csv);
      printf("\n");

      closeCSV(&csv);
   }

   return EXIT_SUCCESS;
}
