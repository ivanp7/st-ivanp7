/* ************************************************ */
/* System keyboard layout independent configuration */
/* ************************************************ */

// Not all key codes are mapped here:
// key codes 0-8 are unused
// key code 37 is Control_L
// key code 50 is Shift_L
// key code 62 is Shift_R
// key code 63 is KP_Multiply
// key code 64 is Alt_L
// key code 66 is Caps_Lock
// key codes 67-76 are F1-F10
// key code 77 is Num_Lock
// key code 78 is Scroll_Lock
// the rest

/******************************************************************************/

#define KEYBOARD_DIGIT_ROW_KCODE_MIN 9
#define KEYBOARD_DIGIT_ROW_KCODE_MAX 23
#define KEYBOARD_DIGIT_ROW_KCODE_NUM \
    (KEYBOARD_DIGIT_ROW_KCODE_MAX-KEYBOARD_DIGIT_ROW_KCODE_MIN+1)

static const char *keyboard_digit_row[KEYBOARD_DIGIT_ROW_KCODE_NUM][2] = {
    // { normal, shift }
    { "\x1B", "\x1B" }, // 9: Escape

    { "1", "!" }, // 10: '1'
    { "2", "@" }, // 11: '2'
    { "3", "#" }, // 12: '3'
    { "4", "$" }, // 13: '4'
    { "5", "%" }, // 14: '5'
    { "6", "^" }, // 15: '6'
    { "7", "&" }, // 16: '7'
    { "8", "*" }, // 17: '8'
    { "9", "(" }, // 18: '9'
    { "0", ")" }, // 19: '0'
    { "-", "_" }, // 20: '-'
    { "=", "+" }, // 21: '='

    { "\b", "\b" }, // 22: Backspace
    { "\t", "\t" }, // 23: Tab
};

static const char *keyboard_digit_row_alt[KEYBOARD_DIGIT_ROW_KCODE_NUM][2] = {
    // { alt, alt-shift }
    { "\x1B", "\x1B" }, // 9: Escape

    { "1", "!" }, // 10: '1'
    { "2", "@" }, // 11: '2'
    { "3", "#" }, // 12: '3'
    { "4", "$" }, // 13: '4'
    { "5", "%" }, // 14: '5'
    { "6", "^" }, // 15: '6'
    { "7", "&" }, // 16: '7'
    { "8", "*" }, // 17: '8'
    { "9", "(" }, // 18: '9'
    { "0", ")" }, // 19: '0'
    { "-", "_" }, // 20: '-'
    { "=", "+" }, // 21: '='

    { "\b", "\b" }, // 22: Backspace
    { "\t", "\t" }, // 23: Tab
};

static const char keyboard_digit_row_ctrl[KEYBOARD_DIGIT_ROW_KCODE_NUM] = {
    '\x1B', // 9: Escape

    '1', // 10: '1'
    '\x00', // 11: '2'
    '\x1B', // 12: '3'
    '\x1C', // 13: '4'
    '\x1D', // 14: '5'
    '\x1E', // 15: '6'
    '\x1F', // 16: '7'
    '\x7F', // 17: '8'
    '9', // 18: '9'
    '0', // 19: '0'
    '-', // 20: '-'
    '=', // 21: '='

    '\x08', // 22: Backspace
    '\x09', // 23: Tab
};

/******************************************************************************/

#define KEYBOARD_TOP_ROW_KCODE_MIN 24
#define KEYBOARD_TOP_ROW_KCODE_MAX 36
#define KEYBOARD_TOP_ROW_KCODE_NUM \
    (KEYBOARD_TOP_ROW_KCODE_MAX-KEYBOARD_TOP_ROW_KCODE_MIN+1)

static const char *keyboard_top_row[3][KEYBOARD_TOP_ROW_KCODE_NUM][2] = {
    // qwerty
    {
        // { normal, shift }
        { "q", "Q" }, // 24: 'q'
        { "w", "W" }, // 25: 'w'
        { "e", "E" }, // 26: 'e'
        { "r", "R" }, // 27: 'r'
        { "t", "T" }, // 28: 't'
        { "y", "Y" }, // 29: 'y'
        { "u", "U" }, // 30: 'u'
        { "i", "I" }, // 31: 'i'
        { "o", "O" }, // 32: 'o'
        { "p", "P" }, // 33: 'p'
        { "[", "{" }, // 34: '['
        { "]", "}" }, // 35: ']'

        { "\r", "\r" }, // 36: Enter
    },

    // colemak
    {
        // { normal, shift }
        { "q", "Q" }, // 24: 'q'
        { "w", "W" }, // 25: 'w'
        { "f", "F" }, // 26: 'e'
        { "p", "P" }, // 27: 'r'
        { "g", "G" }, // 28: 't'
        { "j", "J" }, // 29: 'y'
        { "l", "L" }, // 30: 'u'
        { "u", "U" }, // 31: 'i'
        { "y", "Y" }, // 32: 'o'
        { ";", ":" }, // 33: 'p'
        { "[", "{" }, // 34: '['
        { "]", "}" }, // 35: ']'

        { "\r", "\r" }, // 36: Enter
    },

    // йцукен
    {
        // { normal, shift }
        { "й", "Й" }, // 24: 'q'
        { "ц", "Ц" }, // 25: 'w'
        { "у", "У" }, // 26: 'e'
        { "к", "К" }, // 27: 'r'
        { "е", "Е" }, // 28: 't'
        { "н", "Н" }, // 29: 'y'
        { "г", "Г" }, // 30: 'u'
        { "ш", "Ш" }, // 31: 'i'
        { "щ", "Щ" }, // 32: 'o'
        { "з", "З" }, // 33: 'p'
        { "х", "Х" }, // 34: '['
        { "ъ", "Ъ" }, // 35: ']'

        { "\r", "\r" }, // 36: Enter
    },
};

static const char *keyboard_top_row_alt[KEYBOARD_TOP_ROW_KCODE_NUM][2] = {
    // { alt, alt-shift }
    { "`", "~" }, // 24: 'q'
    { "", "" }, // 25: 'w'
    { "", "" }, // 26: 'e'
    { "", "" }, // 27: 'r'
    { "", "" }, // 28: 't'
    { "", "" }, // 29: 'y'
    { "\\", "|" }, // 30: 'u'
    { "-", "_" }, // 31: 'i'
    { "=", "+" }, // 32: 'o'
    { ";", ":" }, // 33: 'p'
    { "[", "{" }, // 34: '['
    { "]", "}" }, // 35: ']'

    { "\r", "\r" }, // 36: Enter
};

static const char keyboard_top_row_ctrl[2][KEYBOARD_TOP_ROW_KCODE_NUM] = {
    // qwerty
    {
        '\x11', // 24: 'q'
        '\x17', // 25: 'w'
        '\x05', // 26: 'e'
        '\x12', // 27: 'r'
        '\x14', // 28: 't'
        '\x19', // 29: 'y'
        '\x15', // 30: 'u'
        '\x09', // 31: 'i'
        '\x0F', // 32: 'o'
        '\x10', // 33: 'p'
        '\x1B', // 34: '['
        '\x1D', // 35: ']'

        '\x0D', // 36: Enter
    },

    // colemak
    {
        '\x11', // 24: 'q'
        '\x17', // 25: 'w'
        '\x06', // 26: 'e'
        '\x10', // 27: 'r'
        '\x07', // 28: 't'
        '\x0A', // 29: 'y'
        '\x0C', // 30: 'u'
        '\x15', // 31: 'i'
        '\x19', // 32: 'o'
        ';', // 33: 'p'
        '\x1B', // 34: '['
        '\x1D', // 35: ']'

        '\x0D', // 36: Enter
    },
};

/******************************************************************************/

#define KEYBOARD_MIDDLE_ROW_KCODE_MIN 38
#define KEYBOARD_MIDDLE_ROW_KCODE_MAX 49
#define KEYBOARD_MIDDLE_ROW_KCODE_NUM \
    (KEYBOARD_MIDDLE_ROW_KCODE_MAX-KEYBOARD_MIDDLE_ROW_KCODE_MIN+1)

static const char *keyboard_middle_row[3][KEYBOARD_MIDDLE_ROW_KCODE_NUM][2] = {
    // qwerty
    {
        // { normal, shift }
        { "a", "A" }, // 38: 'a'
        { "s", "S" }, // 39: 's'
        { "d", "D" }, // 40: 'd'
        { "f", "F" }, // 41: 'f'
        { "g", "G" }, // 42: 'g'
        { "h", "H" }, // 43: 'h'
        { "j", "J" }, // 44: 'j'
        { "k", "K" }, // 45: 'k'
        { "l", "L" }, // 46: 'l'
        { ";", ":" }, // 47: ';'
        { "'", "\"" }, // 48: '''
        { "`", "~" }, // 49: '`'
    },

    // colemak
    {
        // { normal, shift }
        { "a", "A" }, // 38: 'a'
        { "r", "R" }, // 39: 's'
        { "s", "S" }, // 40: 'd'
        { "t", "T" }, // 41: 'f'
        { "d", "D" }, // 42: 'g'
        { "h", "H" }, // 43: 'h'
        { "n", "N" }, // 44: 'j'
        { "e", "E" }, // 45: 'k'
        { "i", "I" }, // 46: 'l'
        { "o", "O" }, // 47: ';'
        { "'", "\"" }, // 48: '''
        { "`", "~" }, // 49: '`'
    },

    // йцукен
    {
        // { normal, shift }
        { "ф", "Ф" }, // 38: 'a'
        { "ы", "Ы" }, // 39: 's'
        { "в", "В" }, // 40: 'd'
        { "а", "А" }, // 41: 'f'
        { "п", "П" }, // 42: 'g'
        { "р", "Р" }, // 43: 'h'
        { "о", "О" }, // 44: 'j'
        { "л", "Л" }, // 45: 'k'
        { "д", "Д" }, // 46: 'l'
        { "ж", "Ж" }, // 47: ';'
        { "э", "Э" }, // 48: '''
        { "ё", "Ё" }, // 49: '`'
    },
};

static const char *keyboard_middle_row_alt[KEYBOARD_MIDDLE_ROW_KCODE_NUM][2] = {
    // { alt, alt-shift }
    { "1", "!" }, // 38: 'a'
    { "2", "@" }, // 39: 's'
    { "3", "#" }, // 40: 'd'
    { "4", "$" }, // 41: 'f'
    { "5", "%" }, // 42: 'g'
    { "6", "^" }, // 43: 'h'
    { "7", "&" }, // 44: 'j'
    { "8", "*" }, // 45: 'k'
    { "9", "(" }, // 46: 'l'
    { "0", ")" }, // 47: ';'
    { "'", "\"" }, // 48: '''
    { "`", "~" }, // 49: '`'
};

static const char keyboard_middle_row_ctrl[2][KEYBOARD_MIDDLE_ROW_KCODE_NUM] = {
    // qwerty
    {
        '\x01', // 38: 'a'
        '\x13', // 39: 's'
        '\x04', // 40: 'd'
        '\x06', // 41: 'f'
        '\x07', // 42: 'g'
        '\x08', // 43: 'h'
        '\x0A', // 44: 'j'
        '\x0B', // 45: 'k'
        '\x0C', // 46: 'l'
        ';', // 47: ';'
        '\'', // 48: '''
        '\x00', // 49: '`'
    },

    // colemak
    {
        '\x01', // 38: 'a'
        '\x12', // 39: 's'
        '\x13', // 40: 'd'
        '\x14', // 41: 'f'
        '\x04', // 42: 'g'
        '\x08', // 43: 'h'
        '\x0E', // 44: 'j'
        '\x05', // 45: 'k'
        '\x09', // 46: 'l'
        '\x0F', // 47: ';'
        '\'', // 48: '''
        '\x00', // 49: '`'
    },
};

/******************************************************************************/

#define KEYBOARD_BOTTOM_ROW_KCODE_MIN 51
#define KEYBOARD_BOTTOM_ROW_KCODE_MAX 61
#define KEYBOARD_BOTTOM_ROW_KCODE_NUM \
    (KEYBOARD_BOTTOM_ROW_KCODE_MAX-KEYBOARD_BOTTOM_ROW_KCODE_MIN+1)

static const char *keyboard_bottom_row[3][KEYBOARD_BOTTOM_ROW_KCODE_NUM][2] = {
    // qwerty
    {
        // { normal, shift }
        { "\\", "|" }, // 51: '\'
        { "z", "Z" }, // 52: 'z'
        { "x", "X" }, // 53: 'x'
        { "c", "C" }, // 54: 'c'
        { "v", "V" }, // 55: 'v'
        { "b", "B" }, // 56: 'b'
        { "n", "N" }, // 57: 'n'
        { "m", "M" }, // 58: 'm'
        { ",", "<" }, // 59: ','
        { ".", ">" }, // 60: '.'
        { "/", "?" }, // 61: '/'
    },

    // colemak
    {
        // { normal, shift }
        { "\\", "|" }, // 51: '\'
        { "z", "Z" }, // 52: 'z'
        { "x", "X" }, // 53: 'x'
        { "c", "C" }, // 54: 'c'
        { "v", "V" }, // 55: 'v'
        { "b", "B" }, // 56: 'b'
        { "k", "K" }, // 57: 'n'
        { "m", "M" }, // 58: 'm'
        { ",", "<" }, // 59: ','
        { ".", ">" }, // 60: '.'
        { "/", "?" }, // 61: '/'
    },

    // йцукен
    {
        // { normal, shift }
        { "\\", "|" }, // 51: '\'
        { "я", "Я" }, // 52: 'z'
        { "ч", "Ч" }, // 53: 'x'
        { "с", "С" }, // 54: 'c'
        { "м", "М" }, // 55: 'v'
        { "и", "И" }, // 56: 'b'
        { "т", "Т" }, // 57: 'n'
        { "ь", "Ь" }, // 58: 'm'
        { "б", "Б" }, // 59: ','
        { "ю", "Ю" }, // 60: '.'
        { "/", "?" }, // 61: '/'
    },
};

static const char *keyboard_bottom_row_alt[KEYBOARD_BOTTOM_ROW_KCODE_NUM][2] = {
    // { alt, alt-shift }
    { "\\", "|" }, // 51: '\'
    { "", "" }, // 52: 'z'
    { "", "" }, // 53: 'x'
    { "", "" }, // 54: 'c'
    { "5", "%" }, // 55: 'v'
    { "", "" }, // 56: 'b'
    { "", "" }, // 57: 'n'
    { "6", "^" }, // 58: 'm'
    { ",", "<" }, // 59: ','
    { ".", ">" }, // 60: '.'
    { "/", "?" }, // 61: '/'
};

static const char keyboard_bottom_row_ctrl[2][KEYBOARD_BOTTOM_ROW_KCODE_NUM] = {
    // qwerty
    {
        '\x1C', // 51: '\'
        '\x1A', // 52: 'z'
        '\x18', // 53: 'x'
        '\x03', // 54: 'c'
        '\x16', // 55: 'v'
        '\x02', // 56: 'b'
        '\x0E', // 57: 'n'
        '\x0D', // 58: 'm'
        ',', // 59: ','
        '.', // 60: '.'
        '\x1F', // 61: '/'
    },

    // colemak
    {
        '\x1C', // 51: '\'
        '\x1A', // 52: 'z'
        '\x18', // 53: 'x'
        '\x03', // 54: 'c'
        '\x16', // 55: 'v'
        '\x02', // 56: 'b'
        '\x0B', // 57: 'n'
        '\x0D', // 58: 'm'
        ',', // 59: ','
        '.', // 60: '.'
        '\x1F', // 61: '/'
    },
};

/******************************************************************************/

#define KEYBOARD_SPACE_ROW_KCODE_MIN 65
#define KEYBOARD_SPACE_ROW_KCODE_MAX 65
#define KEYBOARD_SPACE_ROW_KCODE_NUM \
    (KEYBOARD_SPACE_ROW_KCODE_MAX-KEYBOARD_SPACE_ROW_KCODE_MIN+1)

static const char *keyboard_space_row[KEYBOARD_SPACE_ROW_KCODE_NUM][2] = {
    // { normal, shift }
    { " ", " " }, // 65: Space
};

static const char *keyboard_space_row_alt[KEYBOARD_SPACE_ROW_KCODE_NUM][2] = {
    // { alt, alt-shift }
    { " ", " " }, // 65: Space
};

static const char keyboard_space_row_ctrl[KEYBOARD_SPACE_ROW_KCODE_NUM] = {
    '\x00', // 65: Space
};

/******************************************************************************/
/******************************************************************************/

static int keyboard_language = 0;
static int keyboard_english_layout = 0;

static void
switch_language(const Arg *arg)
{
    keyboard_language = 1 - keyboard_language;

    if (keyboard_language == 0)
        defaultcs = defaultcs_mode[keyboard_english_layout];
    else
        defaultcs = defaultcs_mode[2];

    redraw(); // cursor
}

static void
switch_layout(const Arg *arg)
{
    keyboard_english_layout = 1 - keyboard_english_layout;

    if (keyboard_language == 0)
    {
        defaultcs = defaultcs_mode[keyboard_english_layout];

        redraw(); // cursor
    }
}

/******************************************************************************/

static void
write_key(int keycode, int shift)
{
    int layout = 2*keyboard_language + keyboard_english_layout;
    if (layout == 3)
        layout = 2;

    const char *buf;

    if ((KEYBOARD_DIGIT_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_DIGIT_ROW_KCODE_MAX))
        buf = keyboard_digit_row[keycode - KEYBOARD_DIGIT_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_TOP_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_TOP_ROW_KCODE_MAX))
        buf = keyboard_top_row[layout][keycode - KEYBOARD_TOP_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_MIDDLE_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_MIDDLE_ROW_KCODE_MAX))
        buf = keyboard_middle_row[layout][keycode - KEYBOARD_MIDDLE_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_BOTTOM_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_BOTTOM_ROW_KCODE_MAX))
        buf = keyboard_bottom_row[layout][keycode - KEYBOARD_BOTTOM_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_SPACE_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_SPACE_ROW_KCODE_MAX))
        buf = keyboard_space_row[keycode - KEYBOARD_SPACE_ROW_KCODE_MIN][shift];
    else
        return;

    ttywrite(buf, strlen(buf), 0);
}

static void
write_key_alt(int keycode, int shift)
{
    const char *buf;

    if ((KEYBOARD_DIGIT_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_DIGIT_ROW_KCODE_MAX))
        buf = keyboard_digit_row_alt[keycode - KEYBOARD_DIGIT_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_TOP_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_TOP_ROW_KCODE_MAX))
        buf = keyboard_top_row_alt[keycode - KEYBOARD_TOP_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_MIDDLE_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_MIDDLE_ROW_KCODE_MAX))
        buf = keyboard_middle_row_alt[keycode - KEYBOARD_MIDDLE_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_BOTTOM_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_BOTTOM_ROW_KCODE_MAX))
        buf = keyboard_bottom_row_alt[keycode - KEYBOARD_BOTTOM_ROW_KCODE_MIN][shift];
    else if ((KEYBOARD_SPACE_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_SPACE_ROW_KCODE_MAX))
        buf = keyboard_space_row_alt[keycode - KEYBOARD_SPACE_ROW_KCODE_MIN][shift];
    else
        return;

    ttywrite(buf, strlen(buf), 0);
}

static void
write_key_ctrl(int keycode)
{
    int layout = keyboard_english_layout;

    const char *buf;

    if ((KEYBOARD_DIGIT_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_DIGIT_ROW_KCODE_MAX))
        buf = &keyboard_digit_row_ctrl[keycode - KEYBOARD_DIGIT_ROW_KCODE_MIN];
    else if ((KEYBOARD_TOP_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_TOP_ROW_KCODE_MAX))
        buf = &keyboard_top_row_ctrl[layout][keycode - KEYBOARD_TOP_ROW_KCODE_MIN];
    else if ((KEYBOARD_MIDDLE_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_MIDDLE_ROW_KCODE_MAX))
        buf = &keyboard_middle_row_ctrl[layout][keycode - KEYBOARD_MIDDLE_ROW_KCODE_MIN];
    else if ((KEYBOARD_BOTTOM_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_BOTTOM_ROW_KCODE_MAX))
        buf = &keyboard_bottom_row_ctrl[layout][keycode - KEYBOARD_BOTTOM_ROW_KCODE_MIN];
    else if ((KEYBOARD_SPACE_ROW_KCODE_MIN <= keycode) && (keycode <= KEYBOARD_SPACE_ROW_KCODE_MAX))
        buf = &keyboard_space_row_ctrl[keycode - KEYBOARD_SPACE_ROW_KCODE_MIN];
    else
        return;

    ttywrite(buf, 1, 0);
}

static void
write_key_arg(const Arg *arg)
{
    write_key(arg->i, 0);
}

static void
write_key_shift_arg(const Arg *arg)
{
    write_key(arg->i, 1);
}

static void
write_key_alt_arg(const Arg *arg)
{
    write_key_alt(arg->i, 0);
}

static void
write_key_alt_shift_arg(const Arg *arg)
{
    write_key_alt(arg->i, 1);
}

static void
write_key_ctrl_arg(const Arg *arg)
{
    write_key_ctrl(arg->i);
}

/******************************************************************************/

static void
write_var_arg(const Arg *arg)
{
    const char *str = getenv(arg->s);
    if (str)
        ttywrite(str, strlen(str), 0);
}

/******************************************************************************/

static void
changefontsize(const Arg *arg)
{
    static const int num_font_sizes = sizeof(font_sizes) / sizeof(font_sizes[0]);
    static int font_size_idx = DEFAULT_FONT_SIZE_IDX;

    if (arg->i != 0)
        font_size_idx += arg->i;
    else
        font_size_idx = DEFAULT_FONT_SIZE_IDX;

    if (font_size_idx < 0)
        font_size_idx = 0;
    else if (font_size_idx >= num_font_sizes)
        font_size_idx = num_font_sizes - 1;

    Arg newarg = {.f = font_sizes[font_size_idx]};
    zoomabs(&newarg);
}

/******************************************************************************/

#define KEY_INSERT_0(keycode) \
    { XK_NO_MOD,                keycode, write_key_arg,             {.i = keycode} }
#define KEY_INSERT_S(keycode) \
    { ShiftMask,                keycode, write_key_shift_arg,       {.i = keycode} }
#define KEY_INSERT_A(keycode) \
    { MODKEY,                   keycode, write_key_alt_arg,         {.i = keycode} }
#define KEY_INSERT_AS(keycode) \
    { MODKEY|ShiftMask,         keycode, write_key_alt_shift_arg,   {.i = keycode} }
#define KEY_INSERT_C(keycode) \
    { ControlMask,              keycode, write_key_ctrl_arg,        {.i = keycode} }, \
    { ControlMask|ShiftMask,    keycode, write_key_ctrl_arg,        {.i = keycode} }

/******************************************************************************/

#define KEY_INSERT(keycode) \
    KEY_INSERT_0(keycode), \
    KEY_INSERT_S(keycode), \
    KEY_INSERT_A(keycode), \
    KEY_INSERT_AS(keycode), \
    KEY_INSERT_C(keycode)

#define KEY_INSERT_NOSHIFT(keycode) \
    KEY_INSERT_0(keycode), \
    KEY_INSERT_A(keycode), \
    KEY_INSERT_C(keycode)

#define KEY_INSERT_NOALT(keycode) \
    KEY_INSERT_0(keycode), \
    KEY_INSERT_S(keycode), \
    KEY_INSERT_C(keycode)

#define KEY_INSERT_ALT_ENV(keycode, var, shift_var) \
    KEY_INSERT_NOALT(keycode), \
    { MODKEY,           keycode, write_var_arg, {.s = var} }, \
    { MODKEY|ShiftMask, keycode, write_var_arg, {.s = shift_var} }

/******************************************************************************/

static Shortcut shortcuts[] = {
    /*            mask                  keycode                 function        argument */
    { XK_ANY_MOD,           127 /*XK_Break*/,       sendbreak,      {.i =  0} },
    { ControlMask,           78 /*XK_Scroll_Lock*/, toggleprinter,  {.i =  0} },
    { ShiftMask,             78 /*XK_Scroll_Lock*/, printscreen,    {.i =  0} },
    { XK_ANY_MOD,            78 /*XK_Scroll_Lock*/, printsel,       {.i =  0} },

    { ShiftMask,            118 /*XK_Insert*/,      clippaste,      {.i =  0} },
    { MODKEY|ControlMask,    54 /*XK_c*/,           clipcopy,       {.i =  0} },
    { MODKEY|ControlMask,    55 /*XK_v*/,           clippaste,      {.i =  0} },
    { MODKEY|ControlMask,    33 /*XK_p*/,           selpaste,       {.i =  0} },

    { MODKEY|ControlMask,   111 /*XK_Up*/,          kscrollup,      {.i = +10} },
    { MODKEY|ControlMask,   116 /*XK_Down*/,        kscrolldown,    {.i = +10} },
    { MODKEY|ControlMask,   113 /*XK_Left*/,        kscrollup,      {.i = -1} },
    { MODKEY|ControlMask,   114 /*XK_Right*/,       kscrolldown,    {.i = -1} },

    { MODKEY,               110 /*XK_Home*/,        changefontsize, {.i =  0} },
    { TERMMOD|ControlMask,  111 /*XK_Up*/,          changefontsize, {.i = +1} },
    { TERMMOD|ControlMask,  116 /*XK_Down*/,        changefontsize, {.i = -1} },
    { TERMMOD|ControlMask,  113 /*XK_Left*/,        changealpha,    {.f = -0.05} },
    { TERMMOD|ControlMask,  114 /*XK_Right*/,       changealpha,    {.f = +0.05} },
    { TERMMOD|ControlMask,   59 /*XK_comma*/,       changealphaOffset, {.f = -0.05} },
    { TERMMOD|ControlMask,   60 /*XK_period*/,      changealphaOffset, {.f = +0.05} },

    /* Input */
    { XK_NO_MOD,            108 /*XK_Alt_R*/,       switch_language, {0} },
    { MODKEY,               135 /*XK_Menu*/,        switch_layout,   {0} },

    // digit row
    KEY_INSERT(9), // Escape

    KEY_INSERT(10), // 1
    KEY_INSERT(11), // 2
    KEY_INSERT(12), // 3
    KEY_INSERT(13), // 4
    KEY_INSERT(14), // 5
    KEY_INSERT(15), // 6
    KEY_INSERT(16), // 7
    KEY_INSERT(17), // 8
    KEY_INSERT(18), // 9
    KEY_INSERT(19), // 0
    KEY_INSERT(20), // -
    KEY_INSERT(21), // =

    KEY_INSERT(22), // Backspace
    KEY_INSERT_NOSHIFT(23), // Tab

    // top row
    KEY_INSERT(24), // q
    KEY_INSERT_ALT_ENV(25, "ST_W0", "ST_W1"), // w
    KEY_INSERT_ALT_ENV(26, "ST_E0", "ST_E1"), // e
    KEY_INSERT_ALT_ENV(27, "ST_R0", "ST_R1"), // r
    KEY_INSERT_ALT_ENV(28, "ST_T0", "ST_T1"), // t
    KEY_INSERT_ALT_ENV(29, "ST_Y0", "ST_Y1"), // y
    KEY_INSERT(30), // u
    KEY_INSERT(31), // i
    KEY_INSERT(32), // o
    KEY_INSERT(33), // p
    KEY_INSERT(34), // [
    KEY_INSERT(35), // ]

    KEY_INSERT(36), // Enter

    // middle row
    KEY_INSERT(38), // a
    KEY_INSERT(39), // s
    KEY_INSERT(40), // d
    KEY_INSERT(41), // f
    KEY_INSERT(42), // g
    KEY_INSERT(43), // h
    KEY_INSERT(44), // j
    KEY_INSERT(45), // k
    KEY_INSERT(46), // l
    KEY_INSERT(47), // ;
    KEY_INSERT(48), // '
    KEY_INSERT(49), // `

    // bottom row
    KEY_INSERT(51), // Backslash
    KEY_INSERT_ALT_ENV(52, "ST_Z0", "ST_Z1"), // z
    KEY_INSERT_ALT_ENV(53, "ST_X0", "ST_X1"), // x
    KEY_INSERT_ALT_ENV(54, "ST_C0", "ST_C1"), // c
    KEY_INSERT(55), // v
    KEY_INSERT_ALT_ENV(56, "ST_B0", "ST_B1"), // b
    KEY_INSERT_ALT_ENV(57, "ST_N0", "ST_N1"), // n
    KEY_INSERT(58), // m
    KEY_INSERT(59), // ,
    KEY_INSERT(60), // .
    KEY_INSERT(61), // Slash

    // space row
    KEY_INSERT(65), // Space
};

