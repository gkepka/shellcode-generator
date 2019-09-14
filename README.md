shellcode-generator
===================

Tool for preparing shellcodes. Unfortunately, at the moment it only allows
for converting raw binary data to ANSI-C quoted form.
```
$ ./shellcode-generator -h
Usage: ./shellcode-generator [options]
-f <File> Use File as an input instead of stdin
-o <File> Redirect output to File
-h Prints this help and exits

$ hd file
00000000  41 20 73 68 6f 72 74 20  66 69 6c 65 20 66 6f 72  |A short file for|
00000010  20 64 65 6d 6f 6e 73 74  72 61 74 69 6f 6e 2e 0a  | demonstration..|
00000020  0a                                                |.|
00000021

$ ./shellcode-generator -f ./file
\x41\x20\x73\x68\x6f\x72\x74\x20\x66\x69\x6c\x65\x20\x66\x6f\x72\x20\x64\x65\x6d\x6f\x6e\x73\x74\x72\x61\x74\x69\x6f\x6e\x2e\xa\xa
```

