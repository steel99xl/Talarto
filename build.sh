#!/bin/bash

case $1 in
    -r) g++ -Wall -Wextra -pedantic -O2 --std=c++11 main.cpp -o Talatro
        exit;;
    -d) g++ -Wall -Wextra -pedantic -ggdb --std=c++11 main.cpp -o Talatro
        exit;;
esac

g++ -Wall -Wextra -pedantic -ggdb --std=c++11 main.cpp -o Talatro
