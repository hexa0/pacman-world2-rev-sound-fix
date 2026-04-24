BUILD_DIR="build"
TMP_DIR=".tmp"

mkdir -p $BUILD_DIR $TMP_DIR

mips64r5900el-ps2-elf-gcc -c src/patch.c -o .tmp/patch.o -march=r5900 -O2 -fno-asynchronous-unwind-tables -fno-exceptions -fno-common -ffreestanding -D_EE
mips64r5900el-ps2-elf-ld -T linker.ld -R game.syms -Ttext 0x00556AD0 -o .tmp/patch.elf .tmp/patch.o
mips64r5900el-ps2-elf-objcopy -O binary .tmp/patch.elf .tmp/patch.bin

ENTRY_ADDR=0x$(mips64r5900el-ps2-elf-nm .tmp/patch.elf | grep pmw2_pre_sound_update_hook | cut -d' ' -f1)

gcc make_pnach.c -o .tmp/make_pnach
.tmp/make_pnach $ENTRY_ADDR