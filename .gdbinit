set disassembly-flavor intel
target remote 127.0.0.1:1234
shell clear
symbol-file kernel/bin-x86_64/kernel

break kmain
c
