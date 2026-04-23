BUILD_DIR="build"
TMP_DIR=".tmp"

mkdir -p $BUILD_DIR $TMP_DIR

mips64r5900el-ps2-elf-gcc -c src/patch.c -o .tmp/patch.o -march=r5900 -O2 -fno-asynchronous-unwind-tables -fno-exceptions -fno-common -ffreestanding -D_EE
mips64r5900el-ps2-elf-objcopy -O binary -j .text .tmp/patch.o .tmp/patch.bin

gcc make_pnach.c -o .tmp/make_pnach
.tmp/make_pnach