# ./build.sh [MODE] [ARGUMENTS]
#
# Modes:
#   build: (default) Builds the project
#   clean: Removes the build directory
#   run: Runs the project

mode=$1

[ -z "$mode" ] && mode="build"

build_dir="build"

if [ "$mode" == "build" ]; then
    echo -e "\033[0;31mBuild the project...\033[0m"

    mkdir -p $build_dir
    cd $build_dir
    cmake ..
    make -j
    if [ $? -ne 0 ]; then
        echo -e "\033[0;31mBuild failed!\033[0m"
        exit 1
    fi
    exit 0
fi

if [ "$1" == "clean" ]; then
    echo -e "\033[0;31mClean the build directory...\033[0m"
    rm -rf $build_dir
    exit 0
fi

if [ "$1" == "run" ]; then
    echo -e "\033[0;31mRun the project...\033[0m"
    shift 1 # remove the first argument

    ./build.sh build
    ret=$?
    if [ $ret -ne 0 ]; then
        exit $ret
    fi

    cd $build_dir
    ./main "$@"
    if [ $? -ne 0 ]; then
        echo -e "\033[0;31mRun failed!\033[0m"
        exit 1
    fi
    exit 0
fi

echo -e "\033[0;31mInvalid mode: $mode\033[0m"
