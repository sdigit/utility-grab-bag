# Utility Grab Bag

Small and useful wheels that don't need reinventing :)

### Scripts:
* whatcert.sh: show basic information on the certificate a site is using
* whatciphers.sh: run sslscan on a target and output supported ciphersuites (requires sslscan in $PATH, will print nothing if sslscan isn't compatible with any server ciphers)

### C stuff
* minigrep: searches standard input for a regex. written to stand-in for egrep -E on huge jobs where all the feature bloat of GNU egrep is a detriment to runtime.

