#include "console.h"
#include "time.h"
#include "libs/string.h"
#include "mouse.h"

void test()
{
    printf("\n\nTEST");
}

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic)
{
    init_mouse();

    clear();
    cursor_pos();
    disable_cursor();

    while(1)
    {
        clear();
        update_mouse();

        printf_button("CORE OS", 1, 1, test);

        cursor_pos(mouse_x, mouse_y);
        printf("#", 0xFF);

        sleep(20);
    }
}