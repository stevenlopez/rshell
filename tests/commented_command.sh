#!bin/bash
echo "commented commands"

echo "ls -a && junk && ls # && ls"

ls -a && junk && ls # && ls

echo "junk && #dont output this"

junk && #dont output this

echo "#dont do any of this; || this || ls"

#dont do any of this; || this || ls

echo "ls && #; test"

ls && #; test

echo "junk && ls && # echo here"

junk && ls && # echo here

echo "LS || LS || # || stuff"

LS || LS || # || stuff

echo ""#" TEST THIS OUT"

"#" TEST THIS OUT

echo "#done with the test cases here"

"done with the test cases here"