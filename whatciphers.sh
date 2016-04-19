#!/bin/sh
# This file is dual licensed under the terms of the Apache License, Version
# 2.0, and the BSD License. See the LICENSE file in the root of this repository
# for complete details.

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

