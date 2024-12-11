mipsisa64r6-linux-gnuabi64-gcc-10 -mmsa ex2.c -o ex2-msa.elf -static -DMSA_VERSION
qemu-mips64 -cpu I6400 ex2-msa.elf
