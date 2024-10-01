#include "console_utils.h"
#include "time.h"

bool holding_key = false;
char command[256];
int command_length = 0;

void finalize_command(char* cmd)
{
    printf(cmd, 15);
    cmd = nullptr;
}

void manage_commands()
{
    char key = read_key();
    if (key != 0)
    {
        if (!holding_key)
        {
            if (key == '\n')
            {
                command[command_length] = '\0';
                finalize_command(command);
                command_length = 0;
                if (current_y == 24)
                {
                    clear();
                    set_cursor_position(0, 0);
                }
                else
                {
                    set_cursor_position(0, current_y + 1);
                    printf("> ", 0xA);
                }
            }
            else if (key == '\r')
            {
                if (command_length > 0)
                {
                    command_length--;
                    delete_char(current_x - 1, current_y);
                    current_x--;
                    set_cursor_position(current_x, current_y);
                }
            }
            else
            {
                if (command_length < sizeof(command) - 1)
                {
                    command[command_length++] = key;
                    printf("%c", 15, key);
                }
            }
            holding_key = true;
        }
    }
    else
    {
        holding_key = false;
    }
}

int8 last_mouse_x = 0;
int8 last_mouse_y = 0;
int8 mouse_x = 40;
int8 mouse_y = 12;
uint8 mouse_buttons = 0;

void update_mouse()
{
    MousePacket mouse = read_mouse();      

    if (mouse.x_movement != 0 || mouse.y_movement != 0 || mouse.buttons != 0)
    {
        mouse_x += mouse.x_movement;
        mouse_y += mouse.y_movement;

        if (mouse_x < 0) mouse_x = 0;
        if (mouse_x > 79) mouse_x = 79;
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_y > 24) mouse_y = 24;

        mouse_buttons = mouse.buttons;
    }
}

void restart()
{
    asm volatile(
        "int $0x19"
    );
}

void manage_desktop()
{
    update_mouse();
    clear();

    printf_button("RESTART", 73, 0, 7, 12, restart, mouse_x, mouse_y, mouse_buttons);

    read_key();
    disable_cursor();
    printf_at("#", mouse_x, mouse_y, 14);
    sleep(10);  
}

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic)
{
    clear();
    init_mouse();  
    while (true)
    {
        manage_desktop();
    }
}
