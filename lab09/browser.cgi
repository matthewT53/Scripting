#!/bin/sh
echo Content-type: text/html
echo

host_address=`host $REMOTE_ADDR | sed "s/^.*\.in-addr.arpa domain name pointer //g"`
host_address=`echo "$host_address" | sed "s/\.$//g"`

cat <<eof
<!DOCTYPE html>
<html lang="en">
<head>
<title>IBrowser IP, Host and User Agent</title>
</head>
<body>
Your browser is running at IP address: <b>$REMOTE_ADDR</b>
<p>
Your browser is running on hostname: <b>$host_address</b>
<p>
Your browser identifies as: <b>$HTTP_USER_AGENT</b>
</body>
</html>
eof
