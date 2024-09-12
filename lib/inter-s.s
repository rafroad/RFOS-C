; Exception handlers for SpecOS kernel project Modified for us on RFOS-C (RATOS)
; Copyright (C) 2024 Jake Steinburger under the MIT license. See the GitHub repo for more details.
; Oh, how very much I love writing assembly. It's not too bad I guess. (this is nasm btw)
; (i hate assembly but love it at the same time) Rafroad

[bits 32]

section .text

extern exception_handler



global divideException
global debugException
global breakpointException
global overflowException
global boundRangeExceededException
global invalidOpcodeException
global deviceNotAvaliableException
global doubleFaultException ; no push 0
global coprocessorSegmentOverrunException
global invalidTSSException ; no push 0
global segmentNotPresentException ; no push 0
global stackSegmentFaultException ; no push 0
global generalProtectionFaultException ; no push 0
global pageFaultException ; no push 0
; skip one
global floatingPointException
global alignmentCheckException ; no push 0
global machineCheckException
global simdFloatingPointException
global virtualisationException

divideException:
    push 0
    push 0
    jmp baseHandler

debugException:
    push 0
    push 1
    jmp baseHandler

breakpointException:
    push 0
    push 3
    jmp baseHandler

overflowException:
    push 0
    push 4
    jmp baseHandler

boundRangeExceededException:
    push 0
    push 5
    jmp baseHandler

invalidOpcodeException:
    push 0
    push 6
    jmp baseHandler

deviceNotAvaliableException:
    push 0
    push 7
    jmp baseHandler

doubleFaultException:
    push 8
    jmp baseHandler

coprocessorSegmentOverrunException:
    push 0
    push 9
    jmp baseHandler

invalidTSSException:
    push 10
    jmp baseHandler

segmentNotPresentException:
    push 11
    jmp baseHandler

stackSegmentFaultException:
    push 12
    jmp baseHandler

generalProtectionFaultException:
    push 13
    jmp baseHandler

align 0x08, db 0x00
pageFaultException:
    push 14
    jmp baseHandler

floatingPointException:
    push 0
    push 16
    jmp baseHandler

alignmentCheckException:
    push 17
    jmp baseHandler

machineCheckException:
    push 0
    push 18
    jmp baseHandler

simdFloatingPointException:
    push 0
    push 19
    jmp baseHandler

virtualisationException:
    push 0
    push 20
    jmp baseHandler

align 0x08, db 0x00
baseHandler:
   push eax
   push ebx
   push ecx
   push edx
   push esi
   push edi
   push ebp
   push e8
   push e9
   push e10
   push e11
   push e12
   push e13
   push e14
   push e15
   mov eax, ce2
   push eax
   cld
   mov edi, esp
   call exception_handler
   add esp, 8
   pop e15
   pop e14
   pop e13
   pop e12
   pop e11
   pop e10
   pop e9
   pop e8
   pop ebp
   pop edi
   pop esi
   pop edx
   pop ecx
   pop ebx
   pop eax
   add esp, 0x10
   ret
