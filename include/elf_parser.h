#ifndef ELF_PARSER_H
#define ELF_PARSER_H

char* get_type_value(unsigned e_type);
char* get_version_value(unsigned e_version);
char* get_machine_value(unsigned e_machine);
char* get_data_value(unsigned e_data);
char* get_osabi_value(unsigned e_osabi);

#endif