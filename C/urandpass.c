/*
 * This file is dual licensed under the terms of the Apache License, Version
 * 2.0, and the BSD License. See the LICENSE file in the root of this repository
 * for complete details.
 */

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DEV_URANDOM "/dev/urandom"

char get_random_character(int fd);
int main(int argc, char **argv);

char get_random_character(int fd)
{
    char tmp;

    tmp = 0;
    while (tmp < 33 || tmp > 126)
    {
        if (read(fd,&tmp,1) != 1)
        {
            errx(EXIT_FAILURE,"read failed: %s",strerror(errno));
            close(fd);
            exit(1);
        }
    }
    return(tmp);
}

int main(int argc, char **argv)
{
    int fd;
    size_t i, len;
    ssize_t wret;
    char pwbuf[_SC_PASS_MAX];

    if (argc != 2)
    {
        printf("Usage: %s <length>\n",argv[0]);
        printf("Note: length must be less than or equal to _SC_PASS_MAX (%d)\n",
            _SC_PASS_MAX);
        exit(0);
    }

    len = (int)strtoul(argv[1],NULL,10);
    if (len == 0 || len > _SC_PASS_MAX)
    {
        errx(EXIT_FAILURE,"Invalid length provided");
        exit(1);
    }

    fd = open(DEV_URANDOM,O_RDONLY);
    if (fd < 0)
    {
        errx(EXIT_FAILURE,"opening %s failed: %s",DEV_URANDOM,strerror(errno));
        exit(1);
    }

    for (i = 0;i < len;i++) { pwbuf[i] = get_random_character(fd); }
    close(fd);

    pwbuf[i] = '\0';

    wret = write(1,pwbuf,strlen(pwbuf));
    if ((size_t)wret != strlen(pwbuf))
    {
        errx(EXIT_FAILURE,"write returned unexpected length");
    }
    wret = write(1,"\n",1);
    if ((size_t)wret != strlen(pwbuf))
    {
        errx(EXIT_FAILURE,"write returned unexpected length");
    }

    for (i = 0;i < sizeof(pwbuf);i++) { pwbuf[i] = 0; }
    return(0);
}

