#!/bin/bash
mkdir build -p
cd build
cmake ..
make
./start_test
lcov --capture --directory ./CMakeFiles/start_test.dir/ --output-file=coverage.info
genhtml coverage.info --output-directory=res
xdg-open ./res/index.html
