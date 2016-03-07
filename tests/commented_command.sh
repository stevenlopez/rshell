echo
./bin/rshell <<EOF
echo "RUN in rshell directory"

echo "The same as the precedence test but inlcude #'s"

echo "[ src ] && #(test src)"
[ src ] && #(test src)

echo "((test src && ls -a) && test junk)#"
((test src && ls -a) && test junk)#

echo "[ fdafds ] #|| ((test lfkjasldkfja) && test src)"
[ fdafds ] #|| ((test lfkjasldkfja) && test src)

echo "(([ -d #src ]))"
(([ -d #src ]))

echo "(([ -f src ])# && (test -f src))"
(([ -f src ])# && (test -f src))

echo "((([ -e src ]) || #(test junk)# && ls -a) &&# test -e src)"
((([ -e src ]) || #(test junk) && ls -a) &&# test -e src)

echo "(((test -d src))#)"
(((test -d src))#)

echo "((test -f src#) || test -f src/main.cpp) && ([ -e src ])"
((test -f src#) || test -f src/main.cpp) && ([ -e src ])

echo "(([ -f src/main.cpp] && [ ju#nk ]) || test -f src)"
(([ -f src/main.cpp] && [ ju#nk ]) || test -f src)

echo "[ -d src/main.cpp] && (#([ -e src ]) || (-f main.cpp))"
[ -d src/main.cpp] && (#([ -e src ]) || (-f main.cpp))

exit

EOF
