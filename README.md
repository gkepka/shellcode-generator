shellcode-generator
===================

Tool for preparing shellcodes. Converts objdump disassembly to ANSI-C quoted form.

```
$ ./shellcode-generator -h
Usage: ./shellcode-generator [options]
-f <File> Use File as an input instead of stdin
-o <File> Redirect output to File
-h Prints this help and exits

$ objdump -d ../shellcode

../shellcode:     file format elf64-x86-64


Disassembly of section .text:

0000000000400078 <_start>:
  400078:	48 31 d2             	xor    %rdx,%rdx
  40007b:	48 bb ff 2f 62 69 6e 	movabs $0x68732f6e69622fff,%rbx
  400082:	2f 73 68 
  400085:	48 c1 eb 08          	shr    $0x8,%rbx
  400089:	53                   	push   %rbx
  40008a:	48 89 e7             	mov    %rsp,%rdi
  40008d:	48 31 c0             	xor    %rax,%rax
  400090:	50                   	push   %rax
  400091:	57                   	push   %rdi
  400092:	48 89 e6             	mov    %rsp,%rsi
  400095:	b0 3b                	mov    $0x3b,%al
  400097:	0f 05                	syscall 

$ objdump -d ../shellcode | ./shellcode-generator 
\x48\x31\xd2\x48\xbb\xff\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xeb\x08\x53\x48\x89\xe7\x48\x31\xc0\x50\x57\x48\x89\xe6\xb0\x3b\x0f\x05

```
