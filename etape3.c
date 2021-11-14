#include "etape3.h"

int
main (int argc, char *argv[])
{
  double longitude, latitude, distance;
  commune_info commune;
  char *usage;

  // memory allocation of ```char *usage``` to match lenth of formatted usage
  // message
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
      exit (1);
    }
  if (argc > 4)
    {
      fprintf (stderr, "%s", usage);
      exit (2);
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

  if (print_communes_within_range (&commune, latitude, longitude, distance)
      != 0)
    exit (6);

  return EXIT_SUCCESS;
}

bool
is_number (char *parameter)
{
  char *number_pattern = "^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$";
  regex_t regex;
  int err;

  err = regcomp (&regex, number_pattern, REG_EXTENDED);
  err = regexec (&regex, parameter, 0, NULL, 0);

  if (err == 0)
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

  if (openCSV (&csv) != 0)
    return EXIT_FAILURE;

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

double
distance_to_reference (commune_info *commune, double latitude_ref,
                       double longitude_ref)
{
  double distance;

  double latitude = commune->latitude;
  double longitude = commune->longitude;

  distance = acos (sin (RAD (latitude_ref)) * sin (RAD (latitude))
                   + cos (RAD (latitude_ref)) * cos (RAD (latitude))
                         * cos (RAD (longitude_ref) - RAD (longitude)))
             * 6371;

  return distance;
}
