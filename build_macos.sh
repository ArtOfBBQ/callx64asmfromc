# COMPILER_OPTIONS="-s -mmacosx-version-min=10.6 -nostartfiles -nostdlib -O0 -x c -std=c99"
COMPILER_OPTIONS="-g -O0 -x c -std=c99"
LINKER_OPTIONS="-arch x86_64 -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem"

C_SOURCE_FILES="src/main.c"

echo "compiler script..."

rm build/*.o
mkdir -p build/$PLATFORM

if nasm -g -f macho64 src/macos_platform.asm -o build/platform.o;
then
    echo "nasm succesful"
else
    echo "nasm failed!"
    exit 0
fi

if gcc -c $COMPILER_OPTIONS $C_SOURCE_FILES -o build/main.o;
then
    echo "compiled c code"
else
    exit 0
fi

if ld $LINKER_OPTIONS build/platform.o build/main.o -o build/syscalls;
then
    echo "linked c code & asm"
    read -p "enter to run app, ctrl-c to quit"
    build/syscalls
else
    echo "linker failed"
    exit 0
fi

