#ifndef _STATIC_KEY_STRUCT_H
#define _STATIC_KEY_STRUCT_H

#include<stdint.h>

#define JUMP_TYPE_FALSE 0UL
#define JUMP_TYPE_TRUE  1UL
#define JUMP_TYPE_MASK  3UL

struct jump_entry
{
    uint64_t code;
    uint64_t target;
    uint64_t key;
};

struct static_key
{
    uint8_t  init_status;
    uint8_t  enabled;
    uint64_t name;
};

struct static_key_true
{
    struct static_key key;
};

struct static_key_false
{
    struct static_key key;
};

#endif /* _STATIC_KEY_STRUCT_H */
