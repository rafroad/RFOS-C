section .text
global switchTask

switchTask:
    pusha
    pushf
    mov eax, cr3             ; Push CR3
    push eax
    mov eax, [esp + 44]      ; The first argument, where to save
    mov [eax + 4], ebx       ; Save EBX
    mov [eax + 8], ecx       ; Save ECX
    mov [eax + 12], edx      ; Save EDX
    mov [eax + 16], esi      ; Save ESI
    mov [eax + 20], edi      ; Save EDI

    mov ebx, [esp + 36]      ; EAX
    mov ecx, [esp + 40]      ; IP
    mov edx, [esp + 20]      ; ESP
    add edx, 4               ; Remove the return value
    mov esi, [esp + 16]      ; EBP
    mov edi, [esp + 4]       ; EFLAGS

    mov [eax], ebx           ; Save EAX
    mov [eax + 24], edx      ; Save ESP
    mov [eax + 28], esi      ; Save EBP
    mov [eax + 32], ecx      ; Save IP
    mov [eax + 36], edi      ; Save EFLAGS

    pop ebx                   ; CR3
    mov [eax + 40], ebx      ; Save CR3
    push ebx                 ; Goodbye again

    mov eax, [esp + 48]      ; Now it is the new object
    mov ebx, [eax + 4]       ; EBX
    mov ecx, [eax + 8]       ; ECX
    mov edx, [eax + 12]      ; EDX
    mov esi, [eax + 16]      ; ESI
    mov edi, [eax + 20]      ; EDI
    mov ebp, [eax + 28]      ; EBP

    push eax
    mov eax, [eax + 36]      ; EFLAGS
    push eax
    popf
    pop eax
    mov esp, [eax + 24]      ; ESP
    push eax
    mov eax, [eax + 40]      ; CR3
    mov cr3, eax
    pop eax
    push eax
    mov eax, [eax + 32]      ; EIP
    xchg [esp], eax          ; We do not have any more registers to use as tmp storage
    mov eax, [eax]           ; EAX
    ret                       ; This ends all!
