#include<sys/mman.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
#include"static_key.h"
#include"static_key_map.h"

union jump_code_union
{
    char code[5];
    struct
    {
        char jump;
        int offset;
    }__attribute__((packed));
};

enum jump_label_type
{
    JUMP_LABEL_NOP = 0,
    JUMP_LABEL_JMP,
};

void static_key_mov(struct static_key& key)
{
    static const unsigned char nop[] = {0x0f,0x1f,0x44,0x00,0};
    static auto pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize == -1)
    {
        std::cout << "Get pagesize error" << std::endl;
        return;
    }

    auto name = key.name;
    auto enabled =  key.enabled;
    auto type = (enum jump_label_type)(key.init_status ^ enabled);
    auto entry_itr = get_entry_map()->find((char*)name);
    if (entry_itr != get_entry_map()->end())
    {
        for (auto& entry : entry_itr->second)
        {
            auto dest_addr = entry->code & ~(pagesize - 1);
            if (enabled ^ (entry->key & JUMP_TYPE_MASK))
            {
                if (mprotect((void*)dest_addr, 2 * pagesize, PROT_READ | PROT_WRITE | PROT_EXEC) == -1)
                {
                    std::cout << "mprotect error" << std::endl;
                    continue;
                }

                if (type == JUMP_LABEL_JMP)
                {
                    union jump_code_union code;
                    code.jump = 0xe9;
                    code.offset = entry->target - (entry->code + 5);
                    memcpy((void*)entry->code, &code, 5);
                }
                else
                {
                    memcpy((void*)entry->code, &nop[0], 5);
                }

                entry->key &= ~JUMP_TYPE_MASK;
                entry->key |= enabled;
            }
        }
    }
}

void __always_inline static_key_enable(struct static_key& key)
{
    if (key.enabled == JUMP_TYPE_TRUE)
    {
        return;
    }
    key.enabled = JUMP_TYPE_TRUE;
    static_key_mov(key);
}

void __always_inline static_key_disable(struct static_key& key)
{
    if (key.enabled == JUMP_TYPE_FALSE)
    {
        return;
    }
    key.enabled = JUMP_TYPE_FALSE;
    static_key_mov(key);
}

template<>
void branch_change_to_likely<struct static_key_true>(struct static_key_true& key)
{
    static_key_enable(key.key);
}

template<>
void branch_change_to_likely<struct static_key_false>(struct static_key_false& key)
{
    static_key_disable(key.key);
}

template<>
void branch_change_to_unlikely<struct static_key_true>(struct static_key_true& key)
{
    static_key_disable(key.key);
}

template<>
void branch_change_to_unlikely<struct static_key_false>(struct static_key_false& key)
{
    static_key_enable(key.key);
}
