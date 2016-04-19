/*
 * This file is dual licensed under the terms of the Apache License, Version
 * 2.0, and the BSD License. See the LICENSE file in the root of this repository
 * for complete details.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <errno.h>

#define LINELEN     BUFSIZ

static inline void io_loop(regex_t *,FILE *,FILE *);
int main(int,char **);

static char inbuf[LINELEN];

static inline void
io_loop(re,in,out)
    regex_t *re;
    FILE *in;
    FILE *out;
{
    char *buf;
    size_t len;
    while (!feof(in) && !feof(out))
    {
        buf = fgets((char *)&inbuf,LINELEN,in);
        if (buf == NULL)
        {
            break;
        }
        len = strlen(buf);
        buf[--len] = '\0';
        if (!regexec(re,(const char *)inbuf,0,NULL,0))
        {
            fwrite(inbuf,len,1,out);
            fwrite("\n",1,1,out);
        }
    }
}

int
main(argc,argv)
    int argc;
    char **argv;
{
    regex_t re;
    if (argc != 2)
    {
        printf("Usage: %s <regex>\n",argv[0]);
        exit(0);
    }
    if (regcomp(&re,argv[1],REG_EXTENDED|REG_NOSUB))
    {
        fprintf(stderr,"regular expression failed to compile\n");
        exit(0);
    }
    io_loop(&re,stdin,stdout);
    exit(0);
}

