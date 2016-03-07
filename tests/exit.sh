echo
./bin/rshell <<EOF
echo "RUN in rshell directory"

echo "The same as the precedence test but shorted since it exits"

echo "[ src ] && (test src)"
[ src ] && (test src)

echo "((test src && ls -a) &&  exit || test junk)#"
((test src && ls -a) && exit || test junk)#

exit

exit(0)

EOF

