global idt_load

idt_load:
    cli
    lidt [rdi]
    ret
    