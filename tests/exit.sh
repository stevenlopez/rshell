echo "running exit command"
echo
.bin/rshell <<EOF
echo "executing exit commands"
echo "This command will be tested"
echo junk && exit
echo "returns false for the first statement and exit never gets executed"
echo "new command to test will be &&exit"
echo &&exit
echo "full string passed in and exit is never a command"
echo "We'll now exit with junk || exit"
echo "executes junk first, then goes to exit and terminates"
EOF
echo
