#!/bin/sh

echo""
echo "---------------simple - valid--------------------"
# VALID
/bin/ls
/usr/bin/make
/bin/echo
/bin/date
/bin/ps

echo ""
echo "----------------simple - invalid-------------------"
# INVALID
/sbin/ls
/xxx
/bin/ddate

echo ""
echo "----------------outsource with args----------------"
/bin/ls -la
/usr/bin/make
/bin/echo hello

echo ""
echo "-------------outsource with args - invalid---------"
/bin/ps hello

echo ""
echo "---------------------test echo---------------------"
echo
echo d
echo coffee
echo -n black
echo pumpkin;echo pumpkin
echo bla\; bla
echo "test no error ;| hehehe"
echo 'test no error ;| hehehe'
echo \| pumpkin
echo $?

echo ""
echo "-------------------env---------------------"

echo ""
echo ""
