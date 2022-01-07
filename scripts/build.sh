#!/bin/bash
projectDir="/d/PUBLIC/FalconView"
buildDir="/d/PUBLIC/build-FalconView_Multi-Desktop_Qt_5_15_2_GCC_64bit-Debug"
libdirs="src/baselib src/lcLib"
plugins="src/plugPages src/statusInfo"
appDir="src/app"

/opt/qt5.15/5.15.2/gcc_64/bin/qmake \
    ${projectDir}/FalconView_Multi.pro \
    -spec linux-g++ \
    CONFIG+=debug

for lib in ${libdirs}; do
    echo "lib: $lib"
    cd ${buildDir}/$lib
    make clean && make
done

for plugBase in ${plugins}; do
    echo "base: ${buildDir}/${plugBase}"
    for i in $(ls ${buildDir}/${plugBase} | grep -v '.pro$'); do
        echo "plugin: ${buildDir}/${plugBase}/$i"
        cd ${buildDir}/${plugBase}/$i
        make clean && make
    done
done

cd ${buildDir}/$appDir
make clean && make

