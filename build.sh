#/bin/bash

CLR_H='\e[32m'
CLR_D='\e[39m'

function PRINT 
{
    echo -e "$CLR_H >> $1 $CLR_D"
}

PRINT 'Starting Make'

make

OS=`uname`
BUILD_PROG=''
BUILD_TARGET=''

PRINT "Detected Os as $OS"

if  [[ $OS == 'CYGWIN_NT-10.0' ]]; then
    BUILD_PROG='MSBuild.exe'
    BUILD_TARGET='./build/debug/GuiTests.sln'
elif [[ $OS == 'Linux' ]]; then
    BUILD_PROG='make'
    BUILD_TARGET='./build/debug/Makefile'
else
    PRINT 'Unknown Os, can not determine builder'
    PRINT 'Exiting'
    exit;
fi

PRINT "Build program is $BUILD_PROG"
PRINT "Build target is $BUILD_TARGET"

# cd ./build/debug && make | tee /dev/tty | grep -P 'warning' > out.file

$BUILD_PROG $BUILD_TARGET | tee lastBuild.txt