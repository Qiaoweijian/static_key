#include"static_key_map.h"

std::map<std::string, std::vector<struct jump_entry*>>* get_entry_map()
{
    static std::map<std::string, std::vector<struct jump_entry*>>map;
    return &map;
}

void static_key_register(struct jump_entry* entry)
{
    std::string name = *(char**)(entry->key & ~JUMP_TYPE_MASK);
    auto& map = *get_entry_map();
    auto& entry_vec = map[name];
    entry_vec.push_back(entry);
}
