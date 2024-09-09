%macro isr_err_stub 1
isr_stub_%+%1:
    call exception_handler
    iret
%endmacro

global isr_stub_table
isr_stub_table:
%assign i 0
%rep    32
    dd isr_stub_%+i
%assign i i+1
%endrep
