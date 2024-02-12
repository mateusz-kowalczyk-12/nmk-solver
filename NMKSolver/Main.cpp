#include "MainSubfunctions.h"


int main(void)
{
    while (true)
    {
        if (feof(stdin) != 0)
            break;

        read_command();

    }
}