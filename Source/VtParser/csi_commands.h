#pragma once

enum csi_command
{
    move             = 'H',
    move_1           = 'f',
    move_up          = 'A',
    move_up_bol      = 'F',
    move_down        = 'B',
    move_down_bol    = 'E',
    move_right       = 'C',
    move_left        = 'D',
    move_to_column   = 'G',
    move_one_line_up = 'M',
    save_position    = 's',
    restore_position = 'u',
    erase_screen     = 'J',
    erase_line       = 'K'
};
