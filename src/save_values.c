#include "../includes/save_values.h"

void init_values(char * filename)
{
    // Open file
    FILE * file;
    file = fopen(filename,"w");
    if ( file == NULL )
    {
        fprintf(stderr, "Error opening file %s", filename);
        exit(1);
    }

    // Write empty data
    fprintf(file,"");

    // close
    fclose(file);

}

void save_values(char * data, char * filename)
{
    // Open file
    FILE * file;
    file = fopen(filename,"a");
    if ( file == NULL )
    {
        fprintf(stderr, "Error opening file %s", filename);
        exit(1);
    }

    // Write data
    fprintf(file,data);

    // close
    fclose(file);

}