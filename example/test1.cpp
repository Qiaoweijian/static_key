#include<iostream>
#include"test1.h"
#include"static_key.h"
#include"static_key_map.h"
#include"register_static_key.h"

DECLARE_JUMP_TABLE_SECTION;  

namespace Test1
{
    REGISTER_STATIC_KEY;
    static DEFINE_STATIC_KEY_FALSE(key, "BCD");

    void pri()
    {
        if (static_branch_unlikely(&key))
        {
            std::cout << "Test : unlikely" << std::endl;
        }
        else
        {
            std::cout << "Test : likely" << std::endl;
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
