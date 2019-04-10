#ifndef _STATIC_KEY_MAP_H
#define _STATIC_KEY_MAP_H

#include<map>
#include<vector>
#include"static_key_struct.h"

std::map<std::string, std::vector<struct jump_entry*>>* get_entry_map();

void static_key_register(struct jump_entry* entry);

#endif /* _STATIC_KEY_MAP_H */
