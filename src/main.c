#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h> 
#include <getopt.h>
#include <string.h>
#include <elf.h>

#include "elf_parser.h"

FILE* i_file;

// EI_NIDENT(TIPICALLY 16BYTES) START (SAME IN EVERY CLASS)
unsigned char e_ident[EI_NIDENT];

// 64BIT-ELF HEADER
int is_64_bit;
Elf64_Ehdr elf64_ehdr;
Elf64_Shdr elf64_shdr;

// 32BIT-ELF HEADER
int is_32_bit;
Elf32_Ehdr elf32_ehdr;
Elf32_Shdr elf32_shdr;

void print_help(char* filename){
    fprintf(stderr,"Usage: %s <in_file_name>\n",filename);
}

void print_magic(unsigned char* magic){ // Imprime completamente el magic en función de su tamaño(Definido por EI_NIDENT)
    for(int i = 0; i < EI_NIDENT; i++)
        fprintf(stdout, " %02x", magic[i]);
    fprintf(stdout, "\n");
}

int parse_header(){
    if (fread(e_ident, sizeof(e_ident), 1, i_file) != 1){
        fprintf(stderr, "Error: Failed while trying to read magic number.\n");
	    return 0;
    }
    
    if(e_ident[0]!=ELFMAG0 || e_ident[1]!=ELFMAG1 || e_ident[2]!=ELFMAG2 || e_ident[3]!=ELFMAG3){
        fprintf(stderr, "Error: Not an ELF file. The magic number does not match.\n");
        return 0;
    }

    is_64_bit = (e_ident[EI_CLASS] == ELFCLASS64);
    is_32_bit = (e_ident[EI_CLASS] == ELFCLASS32);

    if(is_32_bit){
        memcpy(elf32_ehdr.e_ident, e_ident, EI_NIDENT);
        if (fread(&elf32_ehdr.e_type, sizeof(elf32_ehdr)-EI_NIDENT, 1, i_file) != 1){
            fprintf(stderr, "Error: Unexpected error while trying to read 32bit-elf header.\n");
	        return 0;
        }

    }else if(is_64_bit){
        memcpy(elf64_ehdr.e_ident, e_ident, EI_NIDENT);
        if (fread(&elf64_ehdr.e_type, sizeof(elf64_ehdr)-EI_NIDENT, 1, i_file) != 1){
            fprintf(stderr, "Error: Unexpected error while trying to read 64bit-elf header.\n");
	        return 0;
        }
    }
    return 1;
}

void print_header() {
    if(is_32_bit){
        fprintf(stdout, "Header ELF:\n");
        fprintf(stdout, "  Magic Number:");
        print_magic(elf32_ehdr.e_ident);  
        fprintf(stdout, "  Clase: ELF32\n");
        fprintf(stdout, "  Data Format: %s\n", get_data_value(elf32_ehdr.e_ident[EI_DATA]));
        fprintf(stdout, "  OS/ABI: %s\n", get_osabi_value(elf32_ehdr.e_ident[EI_OSABI]));
        fprintf(stdout, "  ABI Version: %u\n", elf32_ehdr.e_ident[EI_ABIVERSION]);

        fprintf(stdout, "  Type: %s\n", get_type_value(elf32_ehdr.e_type));
        fprintf(stdout, "  Version: %s\n", get_version_value(elf32_ehdr.e_version));
        fprintf(stdout, "  Machine: %s\n", get_machine_value(elf32_ehdr.e_machine));
        fprintf(stdout, "  Entry Point: 0x%08x\n", elf32_ehdr.e_entry);
    }else{
        fprintf(stdout, "Header ELF:\n");
        fprintf(stdout, "  Magic Number:");
        print_magic(elf64_ehdr.e_ident);   
        fprintf(stdout, "  Clase: ELF64\n");
        fprintf(stdout, "  Data Format: %s\n", get_data_value(elf64_ehdr.e_ident[EI_DATA]));
        fprintf(stdout, "  OS/ABI: %s\n", get_osabi_value(elf64_ehdr.e_ident[EI_OSABI]));
        fprintf(stdout, "  ABI Version: %u\n", elf64_ehdr.e_ident[EI_ABIVERSION]);


        fprintf(stdout, "  Type: %s\n", get_type_value(elf64_ehdr.e_type));
        fprintf(stdout, "  Version: %s\n", get_version_value(elf64_ehdr.e_version));
        fprintf(stdout, "  Machine: %s\n", get_machine_value(elf64_ehdr.e_machine));
        fprintf(stdout, "  Entry Point: 0x%016lx\n", elf64_ehdr.e_entry);
        
    }
}

int main(int argc, char *argv[]){

    if(argc == 1){
        print_help(argv[0]);
        exit(1);
    }

    // Start of options parsing
    char* options_str = "hs";
    uint8_t options = 0; // 0000 0000
    /*
    BIT0: ehdr
    BIT1: shdr
    ...
    */

    int opt;
    while ((opt = getopt(argc, argv, options_str)) != -1) {
        char *pos = strchr(options_str, opt);

        if (pos != NULL) {
            int bit = pos - options_str;
            options |= (1 << bit);
        }
    }

    if(optind >= argc){ // If there is no "input file" argument
        print_help(argv[0]);
        exit(1);
    }

    if((i_file = fopen(argv[optind], "rb"))== NULL){
        fprintf(stderr,"Error while opening input file 1\n");
        exit(1);
    }

    if(parse_header() == 0){
        fclose(i_file);
        exit(1);
    }

    // End of parsing options

    // Executing options

    if(options != 0){
        if(options & OPT_EDHR)
            print_header();
        /*
        if(options & OPT_SDHR)
            print_shdr();
        */
    }
    // TODO FUTURE CALLS TO IMPLEMENTATIONS HERE

    fprintf(stdout, "RES: %u" , options);

    fclose(i_file);
    return 0;
}