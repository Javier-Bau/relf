# RELF - Basic ELF analyzer
RELF is an educational ELF (Executable and Linkable Format) analyzer written in C.
It parses ELF binaries directly using the structures defined in <elf.h>, providing a minimal implementation of basic ELF inspection tools.

The project focuses on understanding the internal structure of ELF files by reading and interpreting binary data directly, without relying on external ELF parsing libraries.

It also explores how the dynamic linker (ld.so) resolves external symbols by examining ELF structures such as .gnu.hash and .hash, and their relationship with .dynsym, .dynstr, and the .plt/.got mechanisms used for dynamic symbol resolution.

Understanding this symbol resolution process was the main motivation behind developing this ELF analyzer.

To compile the program use: gcc -Iinclude src/main.c src/elf_parser.c -o relf