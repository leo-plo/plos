global idt_load

idt_load:
    push rbp
    mov rbp, rsp
    cli
    lidt [rdi]
    sti
    leave
    ret