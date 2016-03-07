echo
./bin/rshell <<EOF
echo "RUN in rshell directory"

echo "[ src ]"
[ src ]

echo "test src"
test src

echo "[ fdafds ]"
[ fdafds ]

echo "test lfkjasldkfja"
test lfkjasldkfja

echo "[ -d src ]"
[ -d src ]

echo "[ -f src ]"
[ -f src ]

echo " [ -e src ]"
[ -e src ]

echo "test -d src"
test -d src

echo "test -f src"
test -f src

echo "test -e src"
test -e src

echo "[ -f src/main.cpp ]"
[ -f src/main.cpp]

echo "[ -d src/main.cpp ]"
[ -d src/main.cpp]

echo "test -f src/main.cpp"
test -f src/main.cpp

echo "test -d src/main.cpp"
test -d src/main.cpp

exit
EOF
