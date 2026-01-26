set disassembly-flavor intel
target remote localhost:1234
shell clear
symbol-file kernel/bin-x86_64/kernel

break kmain
c
