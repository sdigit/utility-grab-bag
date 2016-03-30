#!/bin/sh
# Author:   Sean Davis <sdigit@github.com>
# License:  Apache 2.0
usage()
{
    echo "Usage: $0 <webserver:port>"
    echo "Example: $0 github.com:443"
    exit
}

[ -z "$1" ] && usage

TARGET="$1"
sslscan --no-failed ${TARGET} | \
awk '/Accepted\s+(TLS|SSL)/ {printf("[%s] (%d bit): %s\n",$2,$3,$5)}'

