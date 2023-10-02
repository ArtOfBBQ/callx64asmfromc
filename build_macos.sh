COMPILER_OPTIONS="-g -O0 -x c -std=c99 -I src/macos_platform"
LINKER_OPTIONS="-e __start -arch x86_64 -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem"

C_SOURCE_FILES="src/main.c src/macos_platform/platform.c"

echo "compiler script..."

rm build/*.o
mkdir -p build/$PLATFORM

if nasm -g -f macho64 src/macos_platform/platform.asm -o build/platform_asm.o;
then
    echo "nasm succesful"
else
    echo "nasm failed!"
    exit 0
fi

if gcc -c $COMPILER_OPTIONS $C_SOURCE_FILES;
then
    echo "compiled c code"
    mv *.o build/
else
    rm *.o
    exit 0
fi

if ld $LINKER_OPTIONS build/*.o -o build/syscalls;
then
    echo "linked c code & asm"
    read -p "enter to run app, ctrl-c to quit"
    build/syscalls
else
    echo "linker failed"
    exit 0
fi

