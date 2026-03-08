#include <elf.h>
#include <stdio.h>

// readelf.c function
char* get_type_value(unsigned e_type) {
    switch(e_type){
        case ET_NONE:	return "NONE (None)";
        case ET_REL:	return "REL (Relocatable file)";
        case ET_EXEC:	return "EXEC (Executable file)";
        case ET_DYN:	return "DYN (Shared object file)";
        case ET_CORE:	return "CORE (Core file)";
    }
}

char* get_version_value(unsigned e_version) {
    switch (e_version)
    {
        case EV_NONE: return "0 (Invalid ELF Version)";
        case EV_CURRENT: return "1 (Current)";
        case EV_NUM: return "2";
    }
}

char* get_machine_value(unsigned e_machine) { 

    static char buff[64];
    switch (e_machine)
    {
        case EM_NONE: return "NONE (None)";
        case EM_ARM: return "40 (ARM)";
        case EM_X86_64: return "62 (AMD x86-64 architecture)";
        default: 
            snprintf (buff, sizeof (buff), "%u (Unknown machine name)", e_machine);
            return buff;
    }
}

char* get_data_value(unsigned e_data){
    switch (e_data)
    {
        case ELFDATANONE: return "Invalid data encoding";
        case ELFDATA2LSB: return "2's complement, little endian ";
        case ELFDATA2MSB: return "2's complement, big endian";
        default: return "<unknown>";
    }
}

// readelf.c function
char* get_osabi_value(unsigned e_osabi){
    char buff[32];
    switch (e_osabi)
        {
        case ELFOSABI_NONE:		  return "UNIX - System V";
        case ELFOSABI_HPUX:		  return "UNIX - HP-UX";
        case ELFOSABI_NETBSD:  	  return "UNIX - NetBSD";
        case ELFOSABI_LINUX:	  return "UNIX - Linux";
        case ELFOSABI_SOLARIS:    return "UNIX - Solaris";
        case ELFOSABI_AIX:		  return "UNIX - AIX";
        case ELFOSABI_IRIX:		  return "UNIX - IRIX";
        case ELFOSABI_FREEBSD:	  return "UNIX - FreeBSD";
        case ELFOSABI_TRU64:	  return "UNIX - TRU64";
        case ELFOSABI_MODESTO:	  return "Novell - Modesto";
        case ELFOSABI_OPENBSD:	  return "UNIX - OpenBSD";
        case ELFOSABI_STANDALONE: return"Standalone App";
        case ELFOSABI_ARM:		  return "ARM";
        case ELFOSABI_ARM_AEABI:  return "ARM EABI";
        default:
        snprintf(buff, sizeof(buff), "<unknown> %x", e_osabi);
        return buff;
        }
}