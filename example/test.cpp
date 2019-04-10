#include<iostream>
#include"test.h"
#include"static_key.h"
#include"static_key_map.h"
#include"register_static_key.h"

DECLARE_JUMP_TABLE_SECTION;  

namespace Test
{
    REGISTER_STATIC_KEY;
    static DEFINE_STATIC_KEY_TRUE(key, "ABC");

    void pri()
    {
        if (static_branch_likely(&key))
        {
            std::cout << "Test : likely" << std::endl;
        }
        else
        {
            std::cout << "Test : unlikely" << std::endl;
        }
    }

    void unlikely()
    {
        std::cout << "\t\tchange to unlikely" << std::endl;
        branch_change_to_unlikely(key);
    }

    void likely()
    {
        std::cout << "\t\tchange to likely" << std::endl;
        branch_change_to_likely(key);
    }

    void func()
    {
        pri();

        unlikely();
        pri();

        likely();
        pri();

        likely();
        pri();

        unlikely();
        pri();
    }
}
