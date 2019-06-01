#!/bin/bash

CLR_OUT='\e[32m'
CLR_WARN='\e[33m'
CLR_DEFAULT='\e[39m'

GREP=/bin/grep
DATE=/bin/date

function INFO { echo -e "$CLR_OUT ["`$DATE`"] >> $1 $CLR_DEFAULT"; }
function PRINT { echo -e "$CLR_DEFAULT ["`$DATE`"] >> $1 $CLR_DEFAULT"; }
function WARN { echo -e "$CLR_WARN ["`$DATE`"] >> $1 $CLR_DEFAULT"; }

OS=`uname`
INFO "Detected Os as $OS"

if [[ $# == 0 ]]; then
    WARN "Nothing to do..."
else
    for TASK in $@; do
        case "$TASK" in
        "todo")
            PATHS=(./libCommon/ ./libGlUtil ./libTermUtil ./gui/ ./playground ./terminal_ui)
            
            for PATH in ${PATHS[@]}; do
                INFO "Searching $PATH"
                $GREP -r -E "TODO|FIXME" $PATH
            done;;            
        "sync")
            git pull
            git push
            git status;;
        "clean")
            INFO "Cleaning..."
            rm -rf ./build/;;
        "make")
            INFO "Creating build files..."
            make;;
        "build")
            INFO "Building project..."

            if  [[ $OS == 'CYGWIN_NT-10.0' ]]; then
                MSBuild.exe -nr:true -m "./build/debug/GalaxyAtWar.sln"
            elif [[ $OS == 'Linux' ]]; then
                make -C ./build/debug/ 
            else
                WARN 'Unknown Os, can not determine builder!'
            fi;;
        "run")
            if  [[ $OS == 'CYGWIN_NT-10.0' ]]; then
                ./build/debug/Debug/Gui.exe
            elif [[ $OS == 'Linux' ]]; then
                ./build/debug/Gui
            else
                WARN 'Unknown Os, can not determine builder!'
            fi;;
        *)
            ERR "Unknown task $TASK!";;
        esac

        if [[ $? != 0 ]]; then
            WARN "Error Occured, exiting..."
            break;
        else
            INFO "Done!"
        fi
    done
fi