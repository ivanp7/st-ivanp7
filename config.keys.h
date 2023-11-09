static int keyboard_language = 0;
static int keyboard_english_layout = 0;

/**********************/
/* 9 <= keycode <= 22 */
static char *keyboard_digit_row[2] = {
    "\x1B""1234567890-=\b", "\x1B""!@#$%^&*()_+\b"
};
static char *keyboard_digit_row_ctrl = "\x1B""1\x00\x1B\x1C\x1D\x1E\x1F\x7F""90-=\x08";

/***********************/
/* 23 <= keycode <= 35 */
static char *keyboard_top_rows[3][2] = {
    { "\tqwertyuiop[]", "\tQWERTYUIOP{}" },
    { "\tqwfpgjluy;[]", "\tQWFPGJLUY:{}" },
    { "\tйцукенгшщзхъ", "\tЙЦУКЕНГШЩЗХЪ" }
};
static char **keyboard_top_row = keyboard_top_rows[0];

static char *keyboard_top_rows_ctrl[2] = {
    "\x09\x11\x17\x05\x12\x14\x19\x15\x09\x0F\x10\x1B\x1D",
    "\x09\x11\x17\x06\x10\x07\x0A\x0C\x15\x19;\x1B\x1D"
};

/***********************/
/* 38 <= keycode <= 49 */
static char *keyboard_middle_rows[3][2] = {
    { "asdfghjkl;'`", "ASDFGHJKL:\"~" },
    { "arstdhneio'`", "ARSTDHNEIO\"~" },
    { "фывапролджэё", "ФЫВАПРОЛДЖЭЁ" }
};
static char **keyboard_middle_row = keyboard_middle_rows[0];

static char *keyboard_middle_rows_ctrl[2] = {
    "\x01\x13\x04\x06\x07\x08\x0A\x0B\x0C;'`",
    "\x01\x12\x13\x14\x04\x08\x0E\x05\x09\x0F'`"
};

/***********************/
/* 51 <= keycode <= 61 */
static char *keyboard_bottom_rows[3][2] = {
    { "\\zxcvbnm,./", "|ZXCVBNM<>?" },
    { "\\zxcvbkm,./", "|ZXCVBKM<>?" },
    { "\\ячсмитьбю/", "|ЯЧСМИТЬБЮ?" }
};
static char **keyboard_bottom_row = keyboard_bottom_rows[0];

static char *keyboard_bottom_rows_ctrl[2] = {
    "\x1C\x1A\x18\x03\x16\x02\x0E\x0D,.\x1F",
    "\x1C\x1A\x18\x03\x16\x02\x0B\x0D,.\x1F"
};

/*****************/
/* keycode == 65 */
static char *keyboard_space = " ";

/******************************************************************************/

static void
switch_language(const Arg *arg)
{
    keyboard_language = 1 - keyboard_language;

    if (keyboard_language == 0)
    {
        keyboard_top_row = keyboard_top_rows[keyboard_english_layout];
        keyboard_middle_row = keyboard_middle_rows[keyboard_english_layout];
        keyboard_bottom_row = keyboard_bottom_rows[keyboard_english_layout];

        defaultcs = defaultcs_mode[keyboard_english_layout];
        redraw(); // cursor
    }
    else
    {
        keyboard_top_row = keyboard_top_rows[2];
        keyboard_middle_row = keyboard_middle_rows[2];
        keyboard_bottom_row = keyboard_bottom_rows[2];

        defaultcs = defaultcs_mode[2];
        redraw(); // cursor
    }
}

static void
switch_layout(const Arg *arg)
{
    keyboard_english_layout = 1 - keyboard_english_layout;

    if (keyboard_language == 0)
    {
        keyboard_top_row = keyboard_top_rows[keyboard_english_layout];
        keyboard_middle_row = keyboard_middle_rows[keyboard_english_layout];
        keyboard_bottom_row = keyboard_bottom_rows[keyboard_english_layout];

        defaultcs = defaultcs_mode[keyboard_english_layout];
        redraw(); // cursor
    }
}

/******************************************************************************/

static size_t
char_length(char signed_c)
{
    unsigned char c = signed_c;
    if (c >> 7 == 0x0)
        return 1;
    else if (c >> 5 == 0x6)
        return 2;
    else if (c >> 4 == 0xE)
        return 3;
    else if (c >> 3 == 0x1E)
        return 4;
    else if (c >> 2 == 0x3E)
        return 5;
    else if (c >> 1 == 0x7E)
        return 6;
    else
        return 0; // error
}

static void
write_char(const char *chrs, int skip)
{
    while (skip > 0)
    {
        chrs += char_length(*chrs);
        skip--;
    }

    ttywrite(chrs, char_length(*chrs), 1);
}

static void
write_char_arg(const Arg *arg)
{
    write_char(arg->s, 0);
}

/******************************************************************************/

static void
insert_key(int keycode, int shift)
{
    char *chrs;

    if ((9 <= keycode) && (keycode <= 22))
    {
        chrs = keyboard_digit_row[shift];
        keycode -= 9;
    }
    else if ((23 <= keycode) && (keycode <= 35))
    {
        chrs = keyboard_top_row[shift];
        keycode -= 23;
    }
    else if ((38 <= keycode) && (keycode <= 49))
    {
        chrs = keyboard_middle_row[shift];
        keycode -= 38;
    }
    else if ((51 <= keycode) && (keycode <= 61))
    {
        chrs = keyboard_bottom_row[shift];
        keycode -= 51;
    }
    else if (keycode == 65)
    {
        chrs = keyboard_space;
        keycode -= 65;
    }
    else
        return;

    write_char(chrs, keycode);
}

static void
insert_key_ctrl(int keycode)
{
    char *chrs;

    if ((9 <= keycode) && (keycode <= 22))
    {
        chrs = keyboard_digit_row_ctrl;
        keycode -= 9;
    }
    else if ((23 <= keycode) && (keycode <= 35))
    {
        chrs = keyboard_top_rows_ctrl[keyboard_english_layout];
        keycode -= 23;
    }
    else if ((38 <= keycode) && (keycode <= 49))
    {
        chrs = keyboard_middle_rows_ctrl[keyboard_english_layout];
        keycode -= 38;
    }
    else if ((51 <= keycode) && (keycode <= 61))
    {
        chrs = keyboard_bottom_rows_ctrl[keyboard_english_layout];
        keycode -= 51;
    }
    else
        return;

    write_char(chrs, keycode);
}

static void
insert_key_arg(const Arg *arg)
{
    insert_key(arg->i, 0);
}

static void
insert_key_shift_arg(const Arg *arg)
{
    insert_key(arg->i, 1);
}

static void
insert_key_ctrl_arg(const Arg *arg)
{
    insert_key_ctrl(arg->i);
}

/******************************************************************************/

static void
write_var_arg(const Arg *arg)
{
    char *str = getenv(arg->s);
    if (!str)
        return;

    while (*str != '\0')
    {
        write_char(str, 0);
        str += char_length(*str);
    }
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
    { XK_NO_MOD, keycode, insert_key_arg,       {.i = keycode} }

#define KEY_INSERT_0S(keycode) \
    { XK_NO_MOD, keycode, insert_key_arg,       {.i = keycode} }, \
    { ShiftMask, keycode, insert_key_shift_arg, {.i = keycode} }

#define KEY_INSERT_0SC(keycode) \
    KEY_INSERT_0S(keycode), \
    { ControlMask,           keycode, insert_key_ctrl_arg,  {.i = keycode} }, \
    { ControlMask|ShiftMask, keycode, insert_key_ctrl_arg,  {.i = keycode} }

/******************************************************************************/

#define KEY_INSERT_0_ALT_CHR(keycode, alt_chr) \
    KEY_INSERT_0(keycode), \
    { MODKEY, keycode, write_char_arg, {.s = alt_chr} }

#define KEY_INSERT_0S_ALT_CHR(keycode, alt_chr, alt_shift_chr) \
    KEY_INSERT_0S(keycode), \
    { MODKEY,           keycode, write_char_arg, {.s = alt_chr} }, \
    { MODKEY|ShiftMask, keycode, write_char_arg, {.s = alt_shift_chr} }

#define KEY_INSERT_0SC_ALT_CHR(keycode, alt_chr, alt_shift_chr) \
    KEY_INSERT_0SC(keycode), \
    { MODKEY,           keycode, write_char_arg, {.s = alt_chr} }, \
    { MODKEY|ShiftMask, keycode, write_char_arg, {.s = alt_shift_chr} }

#define KEY_INSERT_0SC_ALT_ENV(keycode, var, shift_var) \
    KEY_INSERT_0SC(keycode), \
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
    KEY_INSERT_0SC_ALT_CHR(10, "1", "!"), // 1
    KEY_INSERT_0SC_ALT_CHR(11, "2", "@"), // 2
    KEY_INSERT_0SC_ALT_CHR(12, "3", "#"), // 3
    KEY_INSERT_0SC_ALT_CHR(13, "4", "$"), // 4
    KEY_INSERT_0SC_ALT_CHR(14, "5", "%"), // 5
    KEY_INSERT_0SC_ALT_CHR(15, "6", "^"), // 6
    KEY_INSERT_0SC_ALT_CHR(16, "7", "&"), // 7
    KEY_INSERT_0SC_ALT_CHR(17, "8", "*"), // 8
    KEY_INSERT_0SC_ALT_CHR(18, "9", "("), // 9
    KEY_INSERT_0SC_ALT_CHR(19, "0", ")"), // 0
    KEY_INSERT_0SC_ALT_CHR(20, "-", "_"), // -
    KEY_INSERT_0SC_ALT_CHR(21, "=", "+"), // =
    KEY_INSERT_0S_ALT_CHR(22, "\b", "\b"), // Backspace

    // top row
    KEY_INSERT_0_ALT_CHR(23, "\t"), // Tab
    KEY_INSERT_0SC_ALT_CHR(24, "`", "~"), // q
    KEY_INSERT_0SC_ALT_ENV(25, "ST_W0", "ST_W1"), // w
    KEY_INSERT_0SC_ALT_ENV(26, "ST_E0", "ST_E1"), // e
    KEY_INSERT_0SC_ALT_ENV(27, "ST_R0", "ST_R1"), // r
    KEY_INSERT_0SC_ALT_ENV(28, "ST_T0", "ST_T1"), // t
    KEY_INSERT_0SC_ALT_ENV(29, "ST_Y0", "ST_Y1"), // y
    KEY_INSERT_0SC_ALT_CHR(30, "\\", "|"), // u
    KEY_INSERT_0SC_ALT_CHR(31, "-", "_"), // i
    KEY_INSERT_0SC_ALT_CHR(32, "=", "+"), // o
    KEY_INSERT_0SC_ALT_CHR(33, ";", ":"), // p
    KEY_INSERT_0SC_ALT_CHR(34, "[", "{"), // [
    KEY_INSERT_0SC_ALT_CHR(35, "]", "}"), // ]

    // middle row
    KEY_INSERT_0SC_ALT_CHR(38, "1", "!"), // a
    KEY_INSERT_0SC_ALT_CHR(39, "2", "@"), // s
    KEY_INSERT_0SC_ALT_CHR(40, "3", "#"), // d
    KEY_INSERT_0SC_ALT_CHR(41, "4", "$"), // f
    KEY_INSERT_0SC_ALT_CHR(42, "5", "%"), // g
    KEY_INSERT_0SC_ALT_CHR(43, "6", "^"), // h
    KEY_INSERT_0SC_ALT_CHR(44, "7", "&"), // j
    KEY_INSERT_0SC_ALT_CHR(45, "8", "*"), // k
    KEY_INSERT_0SC_ALT_CHR(46, "9", "("), // l
    KEY_INSERT_0SC_ALT_CHR(47, "0", ")"), // ;
    KEY_INSERT_0SC_ALT_CHR(48, "'", "\""), // '
    KEY_INSERT_0SC_ALT_CHR(49, "`", "~"), // Tilde

    // bottom row
    KEY_INSERT_0SC_ALT_CHR(51, "\\", "|"), // Backslash
    KEY_INSERT_0SC_ALT_ENV(52, "ST_Z0", "ST_Z1"), // z
    KEY_INSERT_0SC_ALT_ENV(53, "ST_X0", "ST_X1"), // x
    KEY_INSERT_0SC_ALT_ENV(54, "ST_C0", "ST_C1"), // c
    KEY_INSERT_0SC_ALT_CHR(55, "5", "%"), // v
    KEY_INSERT_0SC_ALT_ENV(56, "ST_B0", "ST_B1"), // b
    KEY_INSERT_0SC_ALT_ENV(57, "ST_N0", "ST_N1"), // n
    KEY_INSERT_0SC_ALT_CHR(58, "6", "^"), // m
    KEY_INSERT_0SC_ALT_CHR(59, ",", "<"), // ,
    KEY_INSERT_0SC_ALT_CHR(60, ".", ">"), // .
    KEY_INSERT_0SC_ALT_CHR(61, "/", "?"), // Slash

    // space
    KEY_INSERT_0S_ALT_CHR(65, " ", " "), // Space
};

