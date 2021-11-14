#include "etape3.h"

int
main (int argc, char *argv[])
{
  double longitude, latitude, distance;
  commune_info commune;
  char *usage;

  /* memory allocation of ```char *usage``` to match the lenth of formatted
   * usage message */
  usage = calloc (
      1, snprintf (NULL, 0,
                   "usage: %s latitude longitude distance\n\tlatitude, "
                   "longitude: number in [-180.0 ; 180.0]\n\tdistance: number "
                   "in [0.0 ; 19999.0]\n",
                   argv[0]));
  sprintf (
      usage,
      "usage: %s latitude longitude distance\n\tlatitude, longitude: number "
      "in [-180.0 ; 180.0]\n\tdistance: number in [0.0 ; 19999.0]\n",
      argv[0]);

  if (argc < 4)
    {
      fprintf (stderr, "%s", usage);
      exit (EXIT_FAILURE);
    }
  if (argc > 4)
    {
      errno = E2BIG;
      fprintf (stderr, "%s", usage);
      exit (errno);
    }

  latitude = atof (argv[1]);
  longitude = atof (argv[2]);
  distance = atof (argv[3]);

  if (((is_number (argv[1]) != 0) || !GPS_VALID (latitude))
      || ((is_number (argv[2]) != 0) || !GPS_VALID (longitude))
      || ((is_number (argv[3]) != 0) || !DISTANCE_VALID (distance)))
    {
      errno = EINVAL;
      fprintf (stderr, "%s", usage);
      exit (errno);
    }

  free (usage);

  if (print_communes_within_range (&commune, latitude, longitude, distance)
      != 0)
    exit (6);

  return EXIT_SUCCESS;
}

/* Checks if the string passed as parameter contains only one real number;
 * returns 0 if string passed as argument contains only one real number;
 * returns EXIT_FAILURE if regex did not compile;
 * returns 2 if regex did not match */
int
is_number (char *string)
{
  /* Expression that matches text containing only one real number written like
   * x or x.y or .y */
  char *number_pattern = "^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$";

  /* Contains compiled regex */
  regex_t regex;

  /* Nonzero means regex could not compile;
   * zero means regex compiled */
  int regex_compilation_error;

  /* Nonzero means regex does not match;
   * zero means regex does match */
  int regex_match_status;

  regex_compilation_error = regcomp (&regex, number_pattern, REG_EXTENDED);

  if (regex_compilation_error)
    {
      return EXIT_FAILURE;
    }

  regex_match_status = regexec (&regex, string, 0, NULL, 0);

  if (regex_match_status == 0)
    {
      return 0;
    }
  return 2;
}

int
print_communes_within_range (commune_info *commune, double latitude_ref,
                             double longitude_ref, double distance)
{
  csv_file csv;
  double distance_to;

  if (openCSV (&csv) != 0)
    {
      return EXIT_FAILURE;
    }

  csv.read_header = true;

  while (getRecordCSV (&csv) == 0)
    {
      if ((valid_commune (&csv, commune) == true)
          && ((distance_to
               = distance_to_reference (commune, latitude_ref, longitude_ref))
              <= distance))
        {
          printf ("%-45s\t%-33s\t%12f km\n", commune->nom_commune,
                  commune->ligne_5, distance_to);
        }
    }

  closeCSV (&csv);

  return EXIT_SUCCESS;
}

/*Calculates the geodesic distance between the gps point described in commune
 * and another gps point described by [latutude_ref ; longitude_ref] */
double
distance_to_reference (commune_info *commune, double latitude_ref,
                       double longitude_ref)
{
  /* Distance between the two points given as argument*/
  double distance;

  double latitude = commune->latitude;
  double longitude = commune->longitude;

  distance = acos (sin (RAD (latitude_ref)) * sin (RAD (latitude))
                   + cos (RAD (latitude_ref)) * cos (RAD (latitude))
                         * cos (RAD (longitude_ref) - RAD (longitude)))
             * 6371;

  return distance;
}