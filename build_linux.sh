# COMPILER_OPTIONS="-g"
COMPILER_OPTIONS="-s"

mkdir -p build
rm build/*.o > /dev/null
rm build/usingnasm > /dev/null
rm build/*.asm > /dev/null
# 

if nasm -f elf64 src/linux_platform.asm -o build/platform.o; then
echo "nasm success"
else
echo "nasm failed"
exit 0
fi

cp src/linux_platform.asm build/platform.asm # you can copy asm files directly and gdb will use them as debug symbols
if gcc -O0 -c $COMPILER_OPTIONS -nostartfiles -nostdlib -Wall -x c -std=c99 src/main.c -o build/main.o; then
echo "gcc success"
else
echo "gcc failed"
exit 0
fi

ld $COMPILER_OPTIONS -nostartfiles -nostdlib build/main.o build/platform.o -o build/usingnasm

build/usingnasm

