#ifndef _STATIC_KEY_H
#define _STATIC_KEY_H

#include<type_traits>
#include"jump_label.h"

#define STATIC_KEY_INIT_TRUE(p) \
        {.init_status = JUMP_TYPE_TRUE, \
         .enabled = JUMP_TYPE_TRUE, \
         .name = p  \
        }

#define STATIC_KEY_INIT_FALSE(p) \
        {.init_status = JUMP_TYPE_FALSE, \
         .enabled = JUMP_TYPE_FALSE, \
         .name = p  \
        }

#define STATIC_KEY_TRUE_INIT(p) (struct static_key_true) {.key = STATIC_KEY_INIT_TRUE(p),}
#define STATIC_KEY_FALSE_INIT(p) (struct static_key_false) {.key = STATIC_KEY_INIT_FALSE(p),}

#define DEFINE_STATIC_KEY_TRUE(name, str)   \
        struct static_key_true name = STATIC_KEY_TRUE_INIT((uint64_t)&str[0])
#define DEFINE_STATIC_KEY_FALSE(name, str)   \
        struct static_key_false name = STATIC_KEY_FALSE_INIT((uint64_t)&str[0])

#define DECLARE_STATIC_KEY_TRUE(name)   \
        extern struct static_key_true name
#define DECLARE_STATIC_KEY_FALSE(name)   \
        extern struct static_key_false name

#define static_branch_likely(x) \
        ({  \
            static_assert(std::is_same<std::remove_reference<decltype(*x)>::type, struct static_key_true>::value, "(*x)'s type must be static_key_true");   \
            bool branch = !arch_static_branch(&(x)->key.name, true); \
            branch; \
        })
#define static_branch_unlikely(x) \
        ({  \
            static_assert(std::is_same<std::remove_reference<decltype(*x)>::type, struct static_key_false>::value, "(*x)'s type must be static_key_false");   \
            bool branch = arch_static_branch(&(x)->key.name, false); \
            branch; \
        })

template<typename T>
void branch_change_to_likely(T& key);

template<typename T>
void branch_change_to_unlikely(T& key);

#endif /* _STATIC_KEY_H */
