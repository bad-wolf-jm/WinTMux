#pragma once

enum sgr_parameter
{
    // clang-format off
    reset            = 0, // Reset or normal	All attributes become turned off
    bold             = 1, // Bold or increased intensity	As with faint, the color change is a PC (SCO / CGA) invention.[25][better source needed]
    faint            = 2, // Faint, decreased intensity, or dim	May be implemented as a light font weight like bold.[26]
    italic           = 3, // Italic	Not widely supported. Sometimes treated as inverse or blink.[25]
    underline        = 4, // Underline	Style extensions exist for Kitty, VTE, mintty, iTerm2 and Konsole.[27][28][29]
    slow_blink       = 5, // Slow blink	Sets blinking to less than 150 times per minute
    fast_blink       = 6, // Rapid blink	MS-DOS ANSI.SYS, 150+ per minute; not widely supported
    invert_colors    = 7, // Reverse video or invert	Swap foreground and background colors; inconsistent emulation[30][dubious – discuss]
    hide             = 8,  // Conceal or hide	Not widely supported.
    crossed_out      = 9,  // Crossed-out, or strike	Characters legible but marked as if for deletion. Not supported in Terminal.app.
    default_font     = 10, // Primary (default) font
    alternate_font_1 = 11, // 	Alternative font	Select alternative font n − 10
    alternate_font_2 = 12, // 	Alternative font	Select alternative font n − 10
    alternate_font_3 = 13, // 	Alternative font	Select alternative font n − 10
    alternate_font_4 = 14, // 	Alternative font	Select alternative font n − 10
    alternate_font_5 = 15, // 	Alternative font	Select alternative font n − 10
    alternate_font_6 = 16, // 	Alternative font	Select alternative font n − 10
    alternate_font_7 = 17, // 	Alternative font	Select alternative font n − 10
    alternate_font_8 = 18, // 	Alternative font	Select alternative font n − 10
    alternate_font_9 = 19, // 	Alternative font	Select alternative font n − 10
    = 20,                  // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22, // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23, // Neither italic, nor blackletter
    = 24, // Not underlined	Neither singly nor doubly underlined
    = 25, // Not blinking	Turn blinking off
    = 26, // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 20, // Fraktur (Gothic)	Rarely supported
    = 21, // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
          // several terminals, including in the Linux kernel's console before version 4.17.[31]
    = 22,     // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    = 23,     // Neither italic, nor blackletter
    = 24,     // Not underlined	Neither singly nor doubly underlined
    = 25,     // Not blinking	Turn blinking off
    = 26,     // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    = 27,     // Not reversed
    = 28,     // Reveal	Not concealed
    = 29,     // Not crossed out
    = 30–37   // 	Set foreground color
    = 38,     // Set foreground color	Next arguments are 5;n or 2;r;g;b
    = 39,     // Default foreground color	Implementation defined (according to standard)
    = 40–47   // 	Set background color
    = 48,     // Set background color	Next arguments are 5;n or 2;r;g;b
    = 49,     // Default background color	Implementation defined (according to standard)
    = 50,     // Disable proportional spacing	T.61 and T.416
    = 51,     // Framed	Implemented as "emoji variation selector" in mintty.[32]
    = 52,     // Encircled
    = 53,     // Overlined	Not supported in Terminal.app
    = 54,     // Neither framed nor encircled
    = 55,     // Not overlined
    = 58,     // Set underline color	Not in standard; implemented in Kitty, VTE, mintty, and iTerm2.[27][28] Next arguments are 5;n or
              // 2;r;g;b.
    = 59,     // Default underline color	Not in standard; implemented in Kitty, VTE, mintty, and iTerm2.[27][28]
    = 60,     // Ideogram underline or right side line	Rarely supported
    = 61,     // Ideogram double underline, or double line on the right side
    = 62,     // Ideogram overline or left side line
    = 63,     // Ideogram double overline, or double line on the left side
    = 64,     // Ideogram stress marking
    = 65,     // No ideogram attributes	Reset the effects of all of 60–64
    = 73,     // Superscript	Implemented only in mintty[32]
    = 74,     // Subscript
    = 75,     // Neither superscript nor subscript
    = 90–97   //	Set bright foreground color	Not in standard; originally implemented by aixterm[16]

    = 100–107 //	Set bright background color
              
//clang-format on
};
