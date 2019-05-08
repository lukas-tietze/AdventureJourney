#/bin/bash

CLR_OUT='\e[32m'
CLR_WARN='\e[33m'
CLR_DEFAULT='\e[39m'

function INFO { echo -e "$CLR_OUT >> $1 $CLR_DEFAULT"; }
function PRINT { echo -e "$CLR_DEFAULT >> $1 $CLR_DEFAULT"; }
function WARN { echo -e "$CLR_WARN >> $1 $CLR_DEFAULT"; }


MAKE_CFG_DEBUG=0
MAKE_CFG_RELEASE=0
RUN_MAKE=0
RUN_BUILD=0
RUN_PROGRAM=0

OS=`uname`
BUILD_PROG=''
BUILD_TARGET=''
BUILD_TYPE=''
EXEC_PATH=''

if [[ $# == 0 ]]; then
    WARN "No options specified, using default options!"
    MAKE_CFG_DEBUG=1
    MAKE_CFG_RELEASE=0
    RUN_BUILD=1
    RUN_PROGRAM=1
else
    for (( i=0; i<${#1}; i++ )); do
        C="${1:$i:1}"

        if [[ $C == 'd' ]]; then
            if [[ $MAKE_CFG_RELEASE == 1 ]]; then
                WARN "release was specified before, now deactivated!"
                MAKE_CFG_RELEASE=0  
            fi

            MAKE_CFG_DEBUG=1
        elif [[ $C == 'r' ]]; then
            if [[ MAKE_CFG_DEBUG == 1 ]]; then
                WARN "debug was specified before, now deactivated!"
                MAKE_CFG_DEBUG=0  
            fi

            MAKE_CFG_RELEASE=1
        elif [[ $C == 'b' ]]; then
            if [[ RUN_BUILD == 1 ]]; then
                WARN "build was already specified, ignoring!"
            fi

            RUN_BUILD=1
        elif [[ $C == 's' ]]; then
            if [[ RUN_PROGRAM == 1 ]]; then
                WARN "start was already specified, ignoring!"
            fi

            RUN_PROGRAM=1
        elif [[ $C == 'm' ]]; then
            if [[ RUN_MAKE == 1 ]]; then
                WARN "make was already specified, ignoring!"
            fi

            RUN_MAKE=1
        else
            WARN "Unknown option '$C'!"
        fi
    done
fi

INFO "Detected Os as $OS"

if  [[ $OS == 'CYGWIN_NT-10.0' ]]; then
    BUILD_PROG='MSBuild.exe'
    BUILD_TARGET='GuiTests.sln'
    EXEC_PATH='Debug/Gui.exe'
elif [[ $OS == 'Linux' ]]; then
    BUILD_PROG='make'
    BUILD_TARGET=''
    EXEC_PATH='Gui'
else
    WARN 'Unknown Os, can not determine builder'
    WARN 'Exiting...'
    exit;
fi

INFO "Parameters are:"
PRINT "MAKE_CFG_DEBUG=$MAKE_CFG_DEBUG"
PRINT "MAKE_CFG_RELEASE=$RUN_MAKE_RELEASE"
PRINT "RUN_MAKE=$RUN_MAKE"
PRINT "RUN_BUILD=$RUN_BUILD"
PRINT "RUN_PROGRAM=$RUN_PROGRAM"

if [[ $MAKE_CFG_DEBUG == 1 ]]; then
    BUILD_TYPE='debug'
elif [[ $MAKE_CFG_RELEASE == 1 ]]; then
    BUILD_TYPE='release'
else
    WARN "Build type unspecified, assuming debug!"
    BUILD_TYPE='debug'
fi

if [[ RUN_MAKE == 1 ]]; then
    PRINT "Build type is $BUILD_TYPE"
    INFO "Starting Make..."
    make $BUILD_TYPE
fi

if [[ $RUN_BUILD == 1 ]]; then
    PRINT "Build program is $BUILD_PROG"
    PRINT "Build target is $BUILD_TARGET"
    INFO "Starting build..."

    cd "./build/$BUILD_TYPE/" && $BUILD_PROG $BUILD_ARGS $BUILD_TARGET
fi

if [[ $RUN_PROGRAM == 1 ]]; then
    FULL_PATH=./build/$BUILD_TYPE/$EXEC_PATH
    PRINT "Executable path is $FULL_PATH"
    INFO "Launching program..."

    if [[ -e $FULL_PATH ]]; then
        $FULL_PATH
    else
        WARN "Could not find executable!"
    fi
fi