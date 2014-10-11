#include <string.h>
#include <stdlib.h>

char*  itoa(int value, char * str, int base)
{
    sprintf(str, "%d", value);
}
