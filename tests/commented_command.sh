#!bin/bash
echo "commented commands"

echo ls -a && junk && ls # && ls

echo junk && #dont output this

echo #dont do any of this; || this || ls

echo ls && #; test

echo junk && ls && # echo here

echo LS || LS || # || stuff

echo "#" TEST THIS OUT

echo #done with the test cases here
