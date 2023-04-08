static size_t
char_length(char signed_c)
{
    unsigned char c = (unsigned char)signed_c;
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

static int layout = 0; // 0 -- qwerty, 1 -- colemak
static int language = 0; // 0 -- english, 1 -- russian

static void
update_cursor()
{
    if (language == 0)
        defaultcs = defaultcs_mode[layout];
    else
        defaultcs = defaultcs_mode[2];
    redraw();
}

static void
switch_language(const Arg *arg)
{
    language = 1 - language;
    update_cursor();
}

static void
switch_layout(const Arg *arg)
{
    layout = 1 - layout;
    update_cursor();
}

/******************************************************************************/

static char *keyboard_digit_row[3] = { /* 9 <= keycode <= 22 */
    "\x1B""1234567890-=\b", "\x1B!@#$%^&*()_+\b", "\x1B""1\x00\x1B\x1C\x1D\x1E\x1F\x7F""90-=\x08"
};

static char *keyboard_top_row[3][3] = { /* 23 <= keycode <= 35 */
    { "\tqwertyuiop[]", "\tQWERTYUIOP{}", "\t\x11\x17\x05\x12\x14\x19\x15\x09\x0F\x10\x1B\x1D" },
    { "\tqwfpgjluy;[]", "\tQWFPGJLUY:{}", "\t\x11\x17\x06\x10\x07\x0A\x0C\x15\x19;\x1B\x1D" },
    { "\tйцукенгшщзхъ", "\tЙЦУКЕНГШЩЗХЪ", "" }
};

static char *keyboard_middle_row[3][3] = { /* 38 <= keycode <= 49 */
    { "asdfghjkl;'`", "ASDFGHJKL:\"~", "\x01\x13\x04\x06\x07\x08\x0A\x0B\x0C;'`" },
    { "arstdhneio'`", "ARSTDHNEIO\"~", "\x01\x12\x13\x14\x04\x08\x0E\x05\x09\x0F'`" },
    { "фывапролджэё", "ФЫВАПРОЛДЖЭЁ", "" }
};

static char *keyboard_bottom_row[3][3] = { /* 51 <= keycode <= 61 */
    { "\\zxcvbnm,./", "|ZXCVBNM<>?", "\x1C\x1A\x18\x03\x16\x02\x0E\x0D,.\x1F" },
    { "\\zxcvbkm,./", "|ZXCVBKM<>?", "\x1C\x1A\x18\x03\x16\x02\x0B\x0D,.\x1F" },
    { "\\ячсмитьбю/", "|ЯЧСМИТЬБЮ?", "" }
};

static char *keyboard_space = " ";

static void
write_selfinsert_char(int keycode, int index)
{
    int mode;
    if (index < 2)
    {
        if (language == 0)
            mode = layout;
        else
            mode = 2;
    }
    else
        mode = layout;

    char *chrs;
    if ((9 <= keycode) && (keycode <= 22))
    {
        chrs = keyboard_digit_row[index];
        keycode -= 9;
    }
    else if ((23 <= keycode) && (keycode <= 35))
    {
        chrs = keyboard_top_row[mode][index];
        keycode -= 23;
    }
    else if ((38 <= keycode) && (keycode <= 49))
    {
        chrs = keyboard_middle_row[mode][index];
        keycode -= 38;
    }
    else if ((51 <= keycode) && (keycode <= 61))
    {
        chrs = keyboard_bottom_row[mode][index];
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
write_selfinsert_char_arg(const Arg *arg)
{
    write_selfinsert_char(arg->i, 0);
}

static void
write_selfinsert_char_arg_shift(const Arg *arg)
{
    write_selfinsert_char(arg->i, 1);
}

static void
write_selfinsert_char_arg_ctrl(const Arg *arg)
{
    write_selfinsert_char(arg->i, 2);
}

/******************************************************************************/

#define DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(mod, keycode) \
    { mod,                    keycode, write_selfinsert_char_arg,       {.i = keycode} }, \
    { mod|ShiftMask,          keycode, write_selfinsert_char_arg_shift, {.i = keycode} }

#define DEF_SELFINSERT_KEY_NOCTRL(keycode) \
    DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(0,        keycode), \
    DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(LockMask, keycode), \
    DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(MODKEY,          keycode), \
    DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(MODKEY|LockMask, keycode)

#define DEF_SELFINSERT_KEY_NOCTRL_WITH_ALT(keycode, alt_chr, alt_shift_chr) \
    DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(0,        keycode), \
    DEF_SELFINSERT_KEY_NOCTRL_NOLOCK(LockMask, keycode), \
    { MODKEY,                    keycode, write_char_arg, {.s = alt_chr} }, \
    { MODKEY|LockMask,           keycode, write_char_arg, {.s = alt_chr} }, \
    { MODKEY|ShiftMask,          keycode, write_char_arg, {.s = alt_shift_chr} }, \
    { MODKEY|ShiftMask|LockMask, keycode, write_char_arg, {.s = alt_shift_chr} }

/******************************************************************************/

#define DEF_SELFINSERT_KEY_NOLOCK(mod, keycode) \
    { mod,                    keycode, write_selfinsert_char_arg,       {.i = keycode} }, \
    { mod|ShiftMask,          keycode, write_selfinsert_char_arg_shift, {.i = keycode} }, \
    { mod|ControlMask,           keycode, write_selfinsert_char_arg_ctrl,  {.i = keycode} }, \
    { mod|ControlMask|ShiftMask, keycode, write_selfinsert_char_arg_ctrl,  {.i = keycode} }

#define DEF_SELFINSERT_KEY(keycode) \
    DEF_SELFINSERT_KEY_NOLOCK(0,        keycode), \
    DEF_SELFINSERT_KEY_NOLOCK(LockMask, keycode), \
    DEF_SELFINSERT_KEY_NOLOCK(MODKEY,          keycode), \
    DEF_SELFINSERT_KEY_NOLOCK(MODKEY|LockMask, keycode)

#define DEF_SELFINSERT_KEY_WITH_ALT(keycode, alt_chr, alt_shift_chr) \
    DEF_SELFINSERT_KEY_NOLOCK(0,        keycode), \
    DEF_SELFINSERT_KEY_NOLOCK(LockMask, keycode), \
    { MODKEY,                    keycode, write_char_arg, {.s = alt_chr} }, \
    { MODKEY|LockMask,           keycode, write_char_arg, {.s = alt_chr} }, \
    { MODKEY|ShiftMask,          keycode, write_char_arg, {.s = alt_shift_chr} }, \
    { MODKEY|ShiftMask|LockMask, keycode, write_char_arg, {.s = alt_shift_chr} }

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

#define DEF_VARINSERT_KEY_WITH_ALT(keycode, var, shift_var) \
    DEF_SELFINSERT_KEY_NOLOCK(0,        keycode), \
    DEF_SELFINSERT_KEY_NOLOCK(LockMask, keycode), \
    { MODKEY,                    keycode, write_var_arg, {.s = var} }, \
    { MODKEY|LockMask,           keycode, write_var_arg, {.s = var} }, \
    { MODKEY|ShiftMask,          keycode, write_var_arg, {.s = shift_var} }, \
    { MODKEY|ShiftMask|LockMask, keycode, write_var_arg, {.s = shift_var} }

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

#define DEF_FUNCTION(mod, keycode, fun, arg) \
    { mod, keycode, fun, arg }, \
    { mod|LockMask, keycode, fun, arg }

static Shortcut shortcuts[] = {
    /*            mask                  keycode                 function        argument */
    DEF_FUNCTION( XK_ANY_MOD,           127 /*XK_Break*/,       sendbreak,      {.i =  0} ),
    DEF_FUNCTION( ControlMask,          78 /*XK_Scroll_Lock*/,  toggleprinter,  {.i =  0} ),
    DEF_FUNCTION( ShiftMask,            78 /*XK_Scroll_Lock*/,  printscreen,    {.i =  0} ),
    DEF_FUNCTION( XK_ANY_MOD,           78 /*XK_Scroll_Lock*/,  printsel,       {.i =  0} ),

    DEF_FUNCTION( ShiftMask,            118 /*XK_Insert*/,      clippaste,      {.i =  0} ),
    DEF_FUNCTION( MODKEY|ControlMask,   54 /*XK_c*/,            clipcopy,       {.i =  0} ),
    DEF_FUNCTION( MODKEY|ControlMask,   55 /*XK_v*/,            clippaste,      {.i =  0} ),
    DEF_FUNCTION( MODKEY|ControlMask,   33 /*XK_p*/,            selpaste,       {.i =  0} ),

    DEF_FUNCTION( MODKEY|ControlMask,   111 /*XK_Up*/,          kscrollup,      {.i = +10} ),
    DEF_FUNCTION( MODKEY|ControlMask,   116 /*XK_Down*/,        kscrolldown,    {.i = +10} ),
    DEF_FUNCTION( MODKEY|ControlMask,   113 /*XK_Left*/,        kscrollup,      {.i = -1} ),
    DEF_FUNCTION( MODKEY|ControlMask,   114 /*XK_Right*/,       kscrolldown,    {.i = -1} ),

    DEF_FUNCTION( MODKEY,               110 /*XK_Home*/,        changefontsize, {.i =  0} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  111 /*XK_Up*/,          changefontsize, {.i = +1} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  116 /*XK_Down*/,        changefontsize, {.i = -1} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  113 /*XK_Left*/,        changealpha,    {.f = -0.05} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  114 /*XK_Right*/,       changealpha,    {.f = +0.05} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  59  /*XK_comma*/,       changealphaOffset, {.f = -0.05} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  60  /*XK_period*/,      changealphaOffset, {.f = +0.05} ),

    /* Input */
    DEF_FUNCTION( 0,                    108 /*XK_Alt_R*/,       switch_language, {} ),
    DEF_FUNCTION( MODKEY,               135  /*XK_Menu*/,       switch_layout, {} ),

    // digit row
    DEF_SELFINSERT_KEY_WITH_ALT(10, "1", "!"), // 1
    DEF_SELFINSERT_KEY_WITH_ALT(11, "2", "@"), // 2
    DEF_SELFINSERT_KEY_WITH_ALT(12, "3", "#"), // 3
    DEF_SELFINSERT_KEY_WITH_ALT(13, "4", "$"), // 4
    DEF_SELFINSERT_KEY_WITH_ALT(14, "5", "%"), // 5
    DEF_SELFINSERT_KEY_WITH_ALT(15, "6", "^"), // 6
    DEF_SELFINSERT_KEY_WITH_ALT(16, "7", "&"), // 7
    DEF_SELFINSERT_KEY_WITH_ALT(17, "8", "*"), // 8
    DEF_SELFINSERT_KEY_WITH_ALT(18, "9", "("), // 9
    DEF_SELFINSERT_KEY_WITH_ALT(19, "0", ")"), // 0
    DEF_SELFINSERT_KEY_WITH_ALT(20, "-", "_"), // -
    DEF_SELFINSERT_KEY_WITH_ALT(21, "=", "+"), // =
    DEF_SELFINSERT_KEY(22), // Backspace

    // top row
    DEF_SELFINSERT_KEY(23), // Tab
    DEF_SELFINSERT_KEY_WITH_ALT(24, "`", "~"), // q
    DEF_VARINSERT_KEY_WITH_ALT(25, "ST_W0", "ST_W1"), // w
    DEF_VARINSERT_KEY_WITH_ALT(26, "ST_E0", "ST_E1"), // e
    DEF_VARINSERT_KEY_WITH_ALT(27, "ST_R0", "ST_R1"), // r
    DEF_VARINSERT_KEY_WITH_ALT(28, "ST_T0", "ST_T1"), // t
    DEF_VARINSERT_KEY_WITH_ALT(29, "ST_Y0", "ST_Y1"), // y
    DEF_SELFINSERT_KEY_WITH_ALT(30, "\\", "|"), // u
    DEF_SELFINSERT_KEY_WITH_ALT(31, "-", "_"), // i
    DEF_SELFINSERT_KEY_WITH_ALT(32, "=", "+"), // o
    DEF_SELFINSERT_KEY_WITH_ALT(33, ";", ":"), // p
    DEF_SELFINSERT_KEY_WITH_ALT(34, "[", "{"), // [
    DEF_SELFINSERT_KEY_WITH_ALT(35, "]", "}"), // ]

    // middle row
    DEF_SELFINSERT_KEY_WITH_ALT(38, "1", "!"), // a
    DEF_SELFINSERT_KEY_WITH_ALT(39, "2", "@"), // s
    DEF_SELFINSERT_KEY_WITH_ALT(40, "3", "#"), // d
    DEF_SELFINSERT_KEY_WITH_ALT(41, "4", "$"), // f
    DEF_SELFINSERT_KEY_WITH_ALT(42, "5", "%"), // g
    DEF_SELFINSERT_KEY_WITH_ALT(43, "6", "^"), // h
    DEF_SELFINSERT_KEY_WITH_ALT(44, "7", "&"), // j
    DEF_SELFINSERT_KEY_WITH_ALT(45, "8", "*"), // k
    DEF_SELFINSERT_KEY_WITH_ALT(46, "9", "("), // l
    DEF_SELFINSERT_KEY_WITH_ALT(47, "0", ")"), // ;
    DEF_SELFINSERT_KEY_WITH_ALT(48, "'", "\""), // '
    DEF_SELFINSERT_KEY_WITH_ALT(49, "`", "~"), // Tilde

    // bottom row
    DEF_SELFINSERT_KEY_WITH_ALT(51, "\\", "|"), // Backslash
    DEF_VARINSERT_KEY_WITH_ALT(52, "ST_Z0", "ST_Z1"), // z
    DEF_VARINSERT_KEY_WITH_ALT(53, "ST_X0", "ST_X1"), // x
    DEF_VARINSERT_KEY_WITH_ALT(54, "ST_C0", "ST_C1"), // c
    DEF_SELFINSERT_KEY_WITH_ALT(55, "5", "%"), // v
    DEF_VARINSERT_KEY_WITH_ALT(56, "ST_B0", "ST_B1"), // b
    DEF_VARINSERT_KEY_WITH_ALT(57, "ST_N0", "ST_N1"), // n
    DEF_SELFINSERT_KEY_WITH_ALT(58, "6", "^"), // m
    DEF_SELFINSERT_KEY_WITH_ALT(59, ",", "<"), // ,
    DEF_SELFINSERT_KEY_WITH_ALT(60, ".", ">"), // .
    DEF_SELFINSERT_KEY_WITH_ALT(61, "/", "?"), // Slash

    // space
    DEF_SELFINSERT_KEY_NOCTRL(65), // Space
};

