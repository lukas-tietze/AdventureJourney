#/bin/bash

make

cd ./build/debug && make | tee /dev/tty | grep -P 'warning' > out.file