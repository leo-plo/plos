set disassembly-flavor intel
target remote 127.0.0.1:1234
shell clear
symbol-file kernel/bin/kernel

break kmain
c
