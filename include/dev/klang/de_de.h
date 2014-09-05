#ifndef KEYBOARD_KEYTABLE_H
#define KEYBOARD_KEYTABLE_H

wchar_t m_unshifted[] =
{
    KEY_UNKNOWN, ASCII_ESC, '1', '2',   /* 0x00 - 0x03 */
    '3', '4', '5', '6',                 /* 0x04 - 0x07 */
    '7', '8', '9', '0',                 /* 0x08 - 0x0B */
    '-', '=', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'q', 'w', 'e', 'r',                 /* 0x10 - 0x13 */
    't', 'z', 'u', 'i',                 /* 0x14 - 0x17 */
    'o', 'p', 246, ']',                 /* 0x18 - 0x1B */
    '\n', KEY_LCTRL, 'a', 's',          /* 0x1C - 0x1F */
    'd', 'f', 'g', 'h',                 /* 0x20 - 0x23 */
    'j', 'k', 'l', ';',                 /* 0x24 - 0x27 */
    '\'', '`', KEY_LSHIFT, '\\',        /* 0x28 - 0x2B */
    'y', 'x', 'c', 'v',                 /* 0x2C - 0x2F */
    'b', 'n', 'm', ',',                 /* 0x30 - 0x33 */
    '.', '/', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,  /* 0x54 - 0x57 */
};		
#define SCAN_TABLE_SIZE (sizeof(m_unshifted) / sizeof(unsigned char))
unsigned short m_shifted[]={
    KEY_UNKNOWN, ASCII_ESC, '!', '@',   /* 0x00 - 0x03 */
    '#', '$', '%', '^',                 /* 0x04 - 0x07 */
    '&', '*', '(', ')',                 /* 0x08 - 0x0B */
    '_', '+', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'Q', 'W', 'E', 'R',                 /* 0x10 - 0x13 */
    'T', 'Z', 'U', 'I',                 /* 0x14 - 0x17 */
    'O', 'P', '{', '}',                 /* 0x18 - 0x1B */
    '\n', KEY_LCTRL, 'A', 'S',          /* 0x1C - 0x1F */
    'D', 'F', 'G', 'H',                 /* 0x20 - 0x23 */
    'J', 'K', 'L', ':',                 /* 0x24 - 0x27 */
    '"', '~', KEY_LSHIFT, '|',          /* 0x28 - 0x2B */
    'Y', 'X', 'C', 'V',                 /* 0x2C - 0x2F */
    'B', 'N', 'M', '<',                 /* 0x30 - 0x33 */
    '>', '?', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,  /* 0x54 - 0x57 */
};
unsigned short m_caps[] =
{
    KEY_UNKNOWN, ASCII_ESC, '1', '2',   /* 0x00 - 0x03 */
    '3', '4', '5', '6',                 /* 0x04 - 0x07 */
    '7', '8', '9', '0',                 /* 0x08 - 0x0B */
    '-', '=', ASCII_BS, '\t',           /* 0x0C - 0x0F */
    'Q', 'W', 'E', 'R',                 /* 0x10 - 0x13 */
    'T', 'Z', 'U', 'I',                 /* 0x14 - 0x17 */
    'O', 'P', '[', ']',                 /* 0x18 - 0x1B */
    '\n', KEY_LCTRL, 'A', 'S',          /* 0x1C - 0x1F */
    'D', 'F', 'G', 'H',                 /* 0x20 - 0x23 */
    'J', 'K', 'L', ';',                 /* 0x24 - 0x27 */
    '\'', '`', KEY_LSHIFT, '\\',        /* 0x28 - 0x2B */
    'Y', 'X', 'C', 'V',                 /* 0x2C - 0x2F */
    'B', 'N', 'M', ',',                 /* 0x30 - 0x33 */
    '.', '/', KEY_RSHIFT, KEY_PRINTSCRN, /* 0x34 - 0x37 */
    KEY_LALT, ' ', KEY_CAPSLOCK, KEY_F1, /* 0x38 - 0x3B */
    KEY_F2, KEY_F3, KEY_F4, KEY_F5,     /* 0x3C - 0x3F */
    KEY_F6, KEY_F7, KEY_F8, KEY_F9,     /* 0x40 - 0x43 */
    KEY_F10, KEY_NUMLOCK, KEY_SCRLOCK, KEY_KPHOME,  /* 0x44 - 0x47 */
    KEY_KPUP, KEY_KPPGUP, KEY_KPMINUS, KEY_KPLEFT,  /* 0x48 - 0x4B */
    KEY_KPCENTER, KEY_KPRIGHT, KEY_KPPLUS, KEY_KPEND,  /* 0x4C - 0x4F */
    KEY_KPDOWN, KEY_KPPGDN, KEY_KPINSERT, KEY_KPDEL,  /* 0x50 - 0x53 */
    KEY_SYSREQ, KEY_UNKNOWN, KEY_UNKNOWN, KEY_UNKNOWN,  /* 0x54 - 0x57 */
};

#endif
