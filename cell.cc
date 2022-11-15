#include "cell.h"

void Cell::flip()
{
    char heart[] = "\xe2\x99\xa5";
    char ace[] = "\xe2\x99\xa4";
    if (state == heart)
    {
        id = 2;
        state = ace;
    }
    else if (state == ace)
    {
        id = 1;
        state = heart;
    }
}