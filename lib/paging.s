section .text
global enablePaging
global loadPageDirectory

enablePaging:
    push ebp                     ; Save base pointer
    mov ebp, esp                ; Establish stack frame
    mov eax, cr0                ; Read CR0
    or eax, 0x80000000          ; Set the paging enable bit
    mov cr0, eax                ; Write back to CR0
    pop ebp                     ; Restore base pointer
    ret                          ; Return from the function

loadPageDirectory:
    push ebp                     ; Save base pointer
    mov ebp, esp                ; Establish stack frame
    mov eax, [ebp + 8]          ; Load the address of the page directory from the argument
    mov cr3, eax                ; Load CR3 with the address of the page directory
    pop ebp                     ; Restore base pointer
    ret                          ; Return from the function
