#!/bin/sh
# Author:   Sean Davis <sdigit@github.com>
# License:  Apache 2.0
usage()
{
    echo "Usage: $0 <webserver:port>"
    echo "Example: $0 github.com:443"
    exit
}

getcert()
{
    WHERE=$1
    WHAT=$2
    echo | \
    openssl s_client -connect ${WHAT} 2>/dev/null | \
    sed -ne '/-----BEGIN CERTIFICATE-----/,/-----END CERTIFICATE-----/p' > ${WHERE}
}

[ -z "$1" ] && usage

TARGET="$1"
TMPFILE=`mktemp whatcertXXXXX`
OSSL="openssl x509 -noout -in ${TMPFILE}"

getcert ${TMPFILE} ${TARGET}

echo "Checked target: ${TARGET}"
${OSSL} -checkend 2592000 > /dev/null 2>&1
echo -n "Expires in the next 30 days? "
if [ $? = 0 ]
then
    echo "NO"
else
    echo "YES"
fi
echo "Subject: "$(${OSSL} -subject|cut -d/ -f2-)
echo "Issuer:  "$(${OSSL} -issuer|cut -d/ -f2-)
echo "Start:   "$(${OSSL} -startdate|cut -d= -f2)
echo "End:     "$(${OSSL} -enddate|cut -d= -f2)

rm -f ${TMPFILE}

