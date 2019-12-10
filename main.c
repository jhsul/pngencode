#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static const char *help_msg = 
    "%1$s - encode a file in a png\n"
    "\n"
    "Usage: %1$s [OPTIONS] <source file> <dest file>\n"
    "\n"
    "Options:\n"
    "  -v  verbose output\n"
    "  -d  decode a png created with %1$s\n"
    "  -h  display this message\n";

extern int encode(char *source, char *dest, char verbose);
extern int decode(char *source, char *dest);


int main(int argc, char *argv[])
{
    char *source;
    char *dest;
    char *args = "vdh";

    char opt;

    char verbose = 0;
    char decode = 0;

    if(argc < 3)
    {
        printf(help_msg, argv[0]);
        return 1;
    }

    while((opt = getopt(argc-2, argv, args)) != -1)
    {
        switch(opt)
        {
            case 'v':
            verbose = 1;
            break;

            case 'd':
            decode = 1;
            break;

            case 'h':
            printf(help_msg, argv[0]);
            return 0;

            default:
            printf("Unknown option: -%c\n", opt);
            printf("More info with: %s -h\n", argv[0]);
            return 1;
        }
    }
    source = argv[argc-2];
    dest = argv[argc-1];
    
    if(decode)
    {
        printf("Decode coming soon\n");
    }
    else
    {
        int len = strlen(dest);
        if(strcmp(dest+len-4, ".png") != 0)
        {
            printf("Error: %s missing file extension .png\n", dest);
            return 1;
        }
        if(encode(source, dest, verbose))
            return 1;
        return 0;
    }
}
