#ifndef ELF_PARSER_H
#define ELF_PARSER_H

static char* get_type_value(unsigned* e_type);
static char* get_version_value(unsigned* e_version);
static char* get_machine_value(unsigned* e_machine);
static char* get_data_value(unsigned* e_data);
static char* get_osabi_value(unsigned* e_osabi);

#endif