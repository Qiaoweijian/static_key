#ifndef _REGISTER_STATIC_KEY_H
#define _REGISTER_STATIC_KEY_H

#define DECLARE_JUMP_TABLE_SECTION  \
    extern struct jump_entry __start___jump_table[] __attribute__((visibility("hidden")));  \
    extern struct jump_entry __stop___jump_table[] __attribute__((visibility("hidden")));

#define REGISTER_STATIC_KEY \
    struct jump_entry* get_entry_start()    \
    {   \
        return &__start___jump_table[0];    \
    }   \
    \
    struct jump_entry* get_entry_stop() \
    {   \
        return &__stop___jump_table[0]; \
    }   \
    \
    int register_key() \
    {   \
        auto start = get_entry_start(); \
        auto end = get_entry_stop();    \
        while (start != end)    \
        {   \
            static_key_register(start++);   \
        }   \
        return 0;   \
    }   \
    \
    static int key_init = register_key();

#endif /* _REGISTER_STATIC_KEY_H */
