if [[ ! -f CMakeLists.txt ]] then
    echo "!!! No CMakeLists.txt in $(pwd). Exiting..."
    exit
fi

cmake -S . -B build \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_C_COMPILER=/usr/local/bin/clang \
    -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++ \
    -DFB_STDLIB='libc++' \
    -G "Unix Makefiles";


if [[ $? -ne 0 ]] then 
    printf "\n!!! CMake configuration failed. Exiting...\n"
    exit
fi

make -C build
if [[ $? -ne 0 ]] then
    printf "\n!!! Compilation failed. Exiting...\n"
    exit
fi

for f in $(ls build/*) 
do
    if [[ -x $f ]] then
        printf "\n----- Running \'$f\' ------\n"
        ./$f
    fi
done
