#!/bin/bash
set -e

project_directory=$(pwd)
project_repository="https://github.com/corvusoft/restbed"

dependencies[0]="dependency/protocol/dependency/core"
dependencies[1]="dependency/network/dependency/runloop/dependency/core"
dependencies[2]="dependency/network/dependency/runloop"
dependencies[3]="dependency/protocol"
dependencies[4]="dependency/network"

echo "Building Restless dependencies..."
for dependency in ${dependencies[@]}
do
    cd $project_directory

    if [ ! -d "$dependency" ]; then
        echo "ERROR: Failed to locate project directory '$dependency'."
        echo "ERROR: Did you perform 'git clone --recursive $project_repository'?"
        exit 1
    fi

    cd $dependency
    mkdir -p build/
    cd build/
    cmake ..
    
    if [ "$1" == "new" ]; then
        make clean
        find $dependency -iwholename '*cmake*' -not -name CMakeLists.txt -delete
    fi

    make install
    make test
done
