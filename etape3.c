#include "etape3.h"

int
main (int argc, char *argv[])
{
  double longitude, latitude, distance;
  commune_info commune;
  char *usage;
  int err;

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

  if (((is_number (argv[1]) == false) || !GPS_VALID (latitude))
      || ((is_number (argv[2]) == false) || !GPS_VALID (longitude))
      || ((is_number (argv[3]) == false) || !DISTANCE_VALID (distance)))
    {
      errno = EINVAL;
      fprintf (stderr, "%s", usage);
      exit (errno);
    }

  free (usage);

  if ((err
       = print_communes_within_range (&commune, latitude, longitude, distance))
      != 0)
    {
      fprintf (stderr, "Couldn't open %s: %s\n", CSV_FILENAME, strerror (err));
      exit (err);
    }

  return EXIT_SUCCESS;
}

/* Checks if the string passed as parameter is a real number with nothing
 * aside;
 * returns true if string passed as argument is a real number;
 * returns false if not */
bool
is_number (char *string)
{
  /* Expression that matches only a real number without anything beside written
   * like "x" or "x.y" or ".y", with x in Z| and y in [0 ; 1] */
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
  assert (regex_compilation_error == 0);

  regex_match_status = regexec (&regex, string, 0, NULL, 0);

  if (regex_match_status == 0)
    {
      return true;
    }
  return false;
}

int
print_communes_within_range (commune_info *commune, double latitude_ref,
                             double longitude_ref, double distance)
{
  csv_file csv;
  double distance_to;
  int err;

  if ((err = openCSV (&csv)) != 0)
    {
      return err;
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