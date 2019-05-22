#/bin/bash

CLR_OUT='\e[32m'
CLR_WARN='\e[33m'
CLR_DEFAULT='\e[39m'

function INFO { echo -e "$CLR_OUT ["`date`"] >> $1 $CLR_DEFAULT"; }
function PRINT { echo -e "$CLR_DEFAULT ["`date`"] >> $1 $CLR_DEFAULT"; }
function WARN { echo -e "$CLR_WARN ["`date`"] >> $1 $CLR_DEFAULT"; }

OS=`uname`
INFO "Detected Os as $OS"

if [[ $# == 0 ]]; then
    WARN "Nothing to do..."
else
    for TASK in $@; do
        if [[ $TASK == "clean" ]]; then
            INFO "Cleaning..."
            rm -rf ./build/
        elif [[ $TASK == "make" ]]; then
            INFO "Creating build files..."
            make
        elif [[ $TASK == "build" ]]; then
            INFO "Building project..."

            if  [[ $OS == 'CYGWIN_NT-10.0' ]]; then
                MSBuild.exe -nr:true -m "./build/debug/GalaxyAtWar.sln"
            elif [[ $OS == 'Linux' ]]; then
                cd ./build/debug/ && make
            else
                WARN 'Unknown Os, can not determine builder!'
            fi
        elif (( $TASK == "run")); then
            if  [[ $OS == 'CYGWIN_NT-10.0' ]]; then
                ./build/debug/Debug/Gui.exe
            elif [[ $OS == 'Linux' ]]; then
                ./build/debug/Gui
            else
                WARN 'Unknown Os, can not determine builder!'
            fi
        else
            ERR "Unknown task $TASK!"
        fi

        if [[ $? != 0 ]]; then
            WARN "Error Occured, exiting..."
            break;
        else
            INFO "Done!"
        fi
    done
fi