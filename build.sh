#!/bin/bash

function usage()
{
    echo "Usage: build.sh [-c] <x86 | arm7va | native> <release | debug> [ configure_opts ]"
}

coverage=0
while getopts "c" o; do
    case "${o}" in
        c)
            coverage=1
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done
shift $((OPTIND-1))

THIS_DIR=`pwd`
COVERAGE_ARGS="-fprofile-arcs -ftest-coverage"
COVERAGE_DIR="$THIS_DIR/test_output"

if [ $# -eq 2 ]; then
    BUILD_ARCH=$1
    BUILD_MODE=$2
elif [ $# -eq 3 ]; then
    BUILD_ARCH=$1
    BUILD_MODE=$2
    CONFIGURE_OPTS=$3
else
    usage
    exit 1
fi

if [ "$BUILD_ARCH" != "x86" ] && [ "$BUILD_ARCH" != "armv7a" ] && [ "$BUILD_ARCH" != "native" ] ; then
    usage
    exit 1
fi

if [ "$BUILD_MODE" != "release" ] && [ "$BUILD_MODE" != "debug" ]; then
    usage
    exit 1
fi

if [ -z "$BUILD_DIR" ]; then
    BUILD_DIR=`pwd`/build/$1/$2
fi

if [ $# -eq 2 ]; then
    CONFIGURE_OPTS="--prefix=${BUILD_DIR}"
fi


PLATFORM=`uname -s`

HOST=x86_64-linux

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
if [ "$coverage" = 1 ]; then
    if [ -x "/usr/bin/lcov" ]; then
        if [ ! -d $COVERAGE_DIR ]; then
            mkdir -p $COVERAGE_DIR
        fi
        lcov --directory . --capture --output-file $COVERAGE_DIR/app.info
        genhtml $COVERAGE_DIR/app.info -o $COVERAGE_DIR
        exit $?
    fi
    echo "lcov must be installed for coverage."
    exit 1
fi

if [ "$BUILD_MODE" = "debug" ]; then
    ${THIS_DIR}/configure CFLAGS="-g -O0 $COVERAGE_ARGS" CXXFLAGS="-std=c++11 -g -O0 $COVERAGE_ARGS" --host=$HOST --enable-debug HOST=$HOST $CONFIGURE_OPTS $TOOLCHAIN_OPTS $HOST_TOOLCHAIN_OPTS
else 
    ${THIS_DIR}/configure CFLAGS="-O2" CXXFLAGS="-std=c++11 -O2" --host=$HOST --disable-debug HOST=$HOST $CONFIGURE_OPTS $TOOLCHAIN_OPTS $HOST_TOOLCHAIN_OPTS
fi

make