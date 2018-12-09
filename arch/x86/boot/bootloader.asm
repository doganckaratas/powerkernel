;### PowerKernel
;### (c) 2011 - 2017
;### Doğan Can Karataş -- v0.3

;Stage 2 multiboot uyumlu bootloader
;sektor 0'da bulunan GRUB 0x7c00'a oturup burayi isletmeye baslar
;biz de buradan stack kurup kernel_main sembolune ziplariz

MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bootstrap_stack, nobits
align 4
stack_bottom:
;resb 16384 ;16 kb stack
resb 32768  ;32 kb stack
stack_top:

section .text
global _start				; linker icin entry point sembolu
_start:
	mov esp, stack_top		; stack kur
	extern kernel_main		; kernel_main sembolunu cagir
	call kernel_main
	cli
.hang:
	hlt
	jmp .hang

