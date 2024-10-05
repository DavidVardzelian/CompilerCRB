#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <sourcefile> \n", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (!source)
    {
        printf("Error: Could not open source file %s\n", argv[2]);
        return 1;
    }

    
}