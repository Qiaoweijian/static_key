#ifndef _JUMP_LABEL_H
#define _JUMP_LABEL_H

#include<stdint.h>

#ifdef __arm__


#else

/* cc -ftree-ter */
static __always_inline bool arch_static_branch(uint64_t* name, bool branch)
{
    do
    {
        asm goto("1:"
                ".byte 0x0f,0x1f,0x44,0x00,0 \n\t"
                ".pushsection __jump_table, \"aw\" \n\t"
                ".balign 8 \n\t"
                ".quad 1b, %l[l_yes], %c0 + %c1 \n\t"
                ".popsection \n\t"
                : : "i"(name), "i"(branch) : : l_yes);
        asm("");
    }while(0);
    return false;
l_yes:
    return true;
}

#endif /* __arm__ */

#endif /* _JUMP_LABEL_H */
