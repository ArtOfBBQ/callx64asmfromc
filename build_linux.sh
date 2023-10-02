# COMPILER_OPTIONS="-g -nostartfiles -nostdlib"
COMPILER_OPTIONS="-Wall -s -nostartfiles -nostdlib -I src/linux_platform/"
# COMPILER_OPTIONS="-Wall -g -fno-stack-protector"
# COMPILER_OPTIONS="-g -fno-stack-protector"

C_SOURCE_FILES="src/main.c src/linux_platform/platform.c"

mkdir -p build
rm build/*.o > /dev/null
rm build/syscalls > /dev/null
rm build/*.asm > /dev/null
# 

if nasm -g -f elf64 src/linux_platform/platform.asm -o build/platform.o; then
echo "nasm success"
else
echo "nasm failed"
exit 0
fi

# you can copy asm files directly and gdb will use them as debug symbols
cp src/linux_platform/platform.asm build/platform.asm

if gcc -lc -O0 $COMPILER_OPTIONS build/platform.o -x c -std=c99 $C_SOURCE_FILES -o build/syscalls
then
echo "gcc success"
else
echo "gcc failed"
exit 0
fi

build/syscalls

