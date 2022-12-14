/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "xos4 Terminus:pixelsize=12:antialias=true:autohint=true";
static char *font2[] = { "xos4 Terminus:pixelsize=12:antialias=true:autohint=true" };
static int borderpx = 2;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: scroll and/or utmp
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
/* scroll program: to enable use a string like "scroll" */
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400 -ixon -ixoff";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 *
 * More advanced example: L" `'\"()[]{}"
 */
wchar_t *worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* allow certain non-interactive (insecure) window operations such as:
   setting the clipboard text */
int allowwindowops = 0;

/*
 * draw latency range in ms - from new content/keypress/etc until drawing.
 * within this range, st draws when content stops arriving (idle). mostly it's
 * near minlatency, but it waits longer for slow updates to avoid partial draw.
 * low minlatency will tear/flicker more, as it can "detect" idle too early.
 */
static double minlatency = 8;
static double maxlatency = 33;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 800;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 2;

/*
 * 1: render most of the lines/blocks characters without using the font for
 *    perfect alignment between cells (U2500 - U259F except dashes/diagonals).
 *    Bold affects lines thickness if boxdraw_bold is not 0. Italic is ignored.
 * 0: disable (render all U25XX glyphs normally from the font).
 */
const int boxdraw = 1;
const int boxdraw_bold = 0;

/* braille (U28XX):  1: render as adjacent "pixels",  0: use font */
const int boxdraw_braille = 1;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char *termname = "st-256color";

/*
 * spaces per tab
 *
 * When you are changing this value, don't forget to adapt the ??it?? value in
 * the st.info and appropriately install the st.info in the environment where
 * you use this st version.
 *
 *   it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` ??tab0?? should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 *   stty tabs
 */
unsigned int tabspaces = 4;

/* bg opacity */
float alpha = 0.8;
float alphaOffset = 0.0;
float alphaUnfocus;

/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
    /* 8 normal colors */
    [0] = "#2e3436", /* black   */
    [1] = "#cc0000", /* red     */
    [2] = "#4e9a06", /* green   */
    [3] = "#c4a000", /* yellow  */
    [4] = "#3465a4", /* blue    */
    [5] = "#75507b", /* magenta */
    [6] = "#06989a", /* cyan    */
    [7] = "#d3d7cf", /* white   */

    /* 8 bright colors */
    [8]  = "#555753", /* black   */
    [9]  = "#ef2929", /* red     */
    [10] = "#8ae234", /* green   */
    [11] = "#fce94f", /* yellow  */
    [12] = "#729fcf", /* blue    */
    [13] = "#ad7fa8", /* magenta */
    [14] = "#34e2e2", /* cyan    */
    [15] = "#eeeeec", /* white   */

    /* special colors */
    [256] = "#2b2b2b", /* background */
    [257] = "#dedede", /* foreground */

    [258] = "#add8e6", /* cursor */
    [259] = "#0ef096", /* cursor, alternative layout */
    [260] = "#ffc7d5", /* cursor, alternative language */
};


/*
 * Default colors (colorname index)
 * foreground, background, cursor, reverse cursor
 */
unsigned int defaultfg = 257;
unsigned int defaultbg = 256;
static unsigned int defaultcs_mode[] = {258, 259, 260};
unsigned int defaultcs = 258;
unsigned int defaultrcs = 0;
unsigned int background = 256;

/*
 * Colors used, when the specific fg == defaultfg. So in reverse mode this
 * will reverse too. Another logic would only make the simple feature too
 * complex.
 */
static unsigned int defaultitalic = 7;
static unsigned int defaultunderline = 7;

/*
 * Default shape of cursor
 * 2: Block ("???")
 * 4: Underline ("_")
 * 6: Bar ("|")
 * 7: Snowman ("???")
 */
static unsigned int cursorshape = 2;

/*
 * Default columns and rows numbers
 */

static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Default colour and shape of the mouse cursor
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Force mouse select/shortcuts while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forcemousemod = ShiftMask;

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "font",         STRING,  &font },
    { "fontalt0",     STRING,  &font2[0] },
    { "color0",       STRING,  &colorname[0] },
    { "color1",       STRING,  &colorname[1] },
    { "color2",       STRING,  &colorname[2] },
    { "color3",       STRING,  &colorname[3] },
    { "color4",       STRING,  &colorname[4] },
    { "color5",       STRING,  &colorname[5] },
    { "color6",       STRING,  &colorname[6] },
    { "color7",       STRING,  &colorname[7] },
    { "color8",       STRING,  &colorname[8] },
    { "color9",       STRING,  &colorname[9] },
    { "color10",      STRING,  &colorname[10] },
    { "color11",      STRING,  &colorname[11] },
    { "color12",      STRING,  &colorname[12] },
    { "color13",      STRING,  &colorname[13] },
    { "color14",      STRING,  &colorname[14] },
    { "color15",      STRING,  &colorname[15] },
    { "background",   STRING,  &colorname[256] },
    { "foreground",   STRING,  &colorname[257] },
    { "cursorColor",  STRING,  &colorname[258] },
    { "cursorColorAltLayout",    STRING,  &colorname[259] },
    { "cursorColorAltLanguage",  STRING,  &colorname[260] },
    { "termname",     STRING,  &termname },
    { "shell",        STRING,  &shell },
    { "minlatency",   INTEGER, &minlatency },
    { "maxlatency",   INTEGER, &maxlatency },
    { "blinktimeout", INTEGER, &blinktimeout },
    { "bellvolume",   INTEGER, &bellvolume },
    { "tabspaces",    INTEGER, &tabspaces },
    { "borderpx",     INTEGER, &borderpx },
    { "cwscale",      FLOAT,   &cwscale },
    { "chscale",      FLOAT,   &chscale },
    { "alpha",        FLOAT,   &alpha },
    { "alphaOffset",  FLOAT,   &alphaOffset },
};

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
    /* mask                 button   function        argument       release */
    { XK_NO_MOD,            Button4, kscrollup,      {.i = 1} },
    { XK_NO_MOD,            Button5, kscrolldown,    {.i = 1} },
    { XK_ANY_MOD,           Button2, selpaste,       {.i = 0},      1 },
    { ShiftMask,            Button4, ttysend,        {.s = "\033[5;2~"} },
    { XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"} },
    { ShiftMask,            Button5, ttysend,        {.s = "\033[6;2~"} },
    { XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"} },
};

/* Internal keyboard shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (Mod1Mask|ShiftMask)

/* static char *openurlcmd[] = { "/bin/sh", "-c", "st-urlhandler -o", "externalpipe", NULL }; */
/* static char *copyurlcmd[] = { "/bin/sh", "-c", "st-urlhandler -c", "externalpipe", NULL }; */
/* static char *copyoutput[] = { "/bin/sh", "-c", "st-copyout", "externalpipe", NULL }; */

/******************************************************************************/

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
    { "\t????????????????????????", "\t????????????????????????", "" }
};

static char *keyboard_middle_row[3][3] = { /* 38 <= keycode <= 49 */
    { "asdfghjkl;'`", "ASDFGHJKL:\"~", "\x01\x13\x04\x06\x07\x08\x0A\x0B\x0C;'`" },
    { "arstdhneio'`", "ARSTDHNEIO\"~", "\x01\x12\x13\x14\x04\x08\x0E\x05\x09\x0F'`" },
    { "????????????????????????", "????????????????????????", "" }
};

static char *keyboard_bottom_row[3][3] = { /* 51 <= keycode <= 61 */
    { "\\zxcvbnm,./", "|ZXCVBNM<>?", "\x1C\x1A\x18\x03\x16\x02\x0E\x0D,.\x1F" },
    { "\\zxcvbkm,./", "|ZXCVBKM<>?", "\x1C\x1A\x18\x03\x16\x02\x0B\x0D,.\x1F" },
    { "\\??????????????????/", "|???????????????????", "" }
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

    DEF_FUNCTION( MODKEY,               110 /*XK_Home*/,        zoomreset,      {.f =  0} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  111 /*XK_Up*/,          zoom,           {.f = +1} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  116 /*XK_Down*/,        zoom,           {.f = -1} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  113 /*XK_Left*/,        changealpha,    {.f = -0.05} ),
    DEF_FUNCTION( TERMMOD|ControlMask,  114 /*XK_Right*/,       changealpha,    {.f = +0.05} ),

    /* { MODKEY,               XK_l,           externalpipe,   {.v = openurlcmd } }, */
    /* DEF_FUNCTION( MODKEY|ControlMask,   XK_y,            externalpipe,   {.v = copyurlcmd } ), */
    /* DEF_FUNCTION( MODKEY|ControlMask,   XK_o,            externalpipe,   {.v = copyoutput } ), */

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

/*
 * Special keys (change & recompile st.info accordingly)
 *
 * Mask value:
 * * Use XK_ANY_MOD to match the key no matter modifiers state
 * * Use XK_NO_MOD to match the key alone (no modifiers)
 * appkey value:
 * * 0: no value
 * * > 0: keypad application mode enabled
 * *   = 2: term.numlock = 1
 * * < 0: keypad application mode disabled
 * appcursor value:
 * * 0: no value
 * * > 0: cursor application mode enabled
 * * < 0: cursor application mode disabled
 *
 * Be careful with the order of the definitions because st searches in
 * this table sequentially, so any XK_ANY_MOD must be in the last
 * position for a key.
 */

/*
 * If you want keys other than the X11 function keys (0xFD00 - 0xFFFF)
 * to be mapped below, add them to this array.
 */
static KeySym mappedkeys[] = { -1 };

/*
 * State bits to ignore when matching key or button events.  By default,
 * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
 */
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * This is the huge key array which defines all compatibility to the Linux
 * world. Please decide about changes wisely.
 */
static Key key[] = {
    /* keysym           mask            string      appkey appcursor */
    { XK_KP_Home,       ShiftMask,      "\033[2J",       0,   -1},
    { XK_KP_Home,       ShiftMask,      "\033[1;2H",     0,   +1},
    { XK_KP_Home,       XK_ANY_MOD,     "\033[H",        0,   -1},
    { XK_KP_Home,       XK_ANY_MOD,     "\033[1~",       0,   +1},
    { XK_KP_Up,         XK_ANY_MOD,     "\033Ox",       +1,    0},
    { XK_KP_Up,         XK_ANY_MOD,     "\033[A",        0,   -1},
    { XK_KP_Up,         XK_ANY_MOD,     "\033OA",        0,   +1},
    { XK_KP_Down,       XK_ANY_MOD,     "\033Or",       +1,    0},
    { XK_KP_Down,       XK_ANY_MOD,     "\033[B",        0,   -1},
    { XK_KP_Down,       XK_ANY_MOD,     "\033OB",        0,   +1},
    { XK_KP_Left,       XK_ANY_MOD,     "\033Ot",       +1,    0},
    { XK_KP_Left,       XK_ANY_MOD,     "\033[D",        0,   -1},
    { XK_KP_Left,       XK_ANY_MOD,     "\033OD",        0,   +1},
    { XK_KP_Right,      XK_ANY_MOD,     "\033Ov",       +1,    0},
    { XK_KP_Right,      XK_ANY_MOD,     "\033[C",        0,   -1},
    { XK_KP_Right,      XK_ANY_MOD,     "\033OC",        0,   +1},
    { XK_KP_Prior,      ShiftMask,      "\033[5;2~",     0,    0},
    { XK_KP_Prior,      XK_ANY_MOD,     "\033[5~",       0,    0},
    { XK_KP_Begin,      XK_ANY_MOD,     "\033[E",        0,    0},
    { XK_KP_End,        ControlMask,    "\033[J",       -1,    0},
    { XK_KP_End,        ControlMask,    "\033[1;5F",    +1,    0},
    { XK_KP_End,        ShiftMask,      "\033[K",       -1,    0},
    { XK_KP_End,        ShiftMask,      "\033[1;2F",    +1,    0},
    { XK_KP_End,        XK_ANY_MOD,     "\033[4~",       0,    0},
    { XK_KP_Next,       ShiftMask,      "\033[6;2~",     0,    0},
    { XK_KP_Next,       XK_ANY_MOD,     "\033[6~",       0,    0},
    { XK_KP_Insert,     ShiftMask,      "\033[2;2~",    +1,    0},
    { XK_KP_Insert,     ShiftMask,      "\033[4l",      -1,    0},
    { XK_KP_Insert,     ControlMask,    "\033[L",       -1,    0},
    { XK_KP_Insert,     ControlMask,    "\033[2;5~",    +1,    0},
    { XK_KP_Insert,     XK_ANY_MOD,     "\033[4h",      -1,    0},
    { XK_KP_Insert,     XK_ANY_MOD,     "\033[2~",      +1,    0},
    { XK_KP_Delete,     ControlMask,    "\033[M",       -1,    0},
    { XK_KP_Delete,     ControlMask,    "\033[3;5~",    +1,    0},
    { XK_KP_Delete,     ShiftMask,      "\033[2K",      -1,    0},
    { XK_KP_Delete,     ShiftMask,      "\033[3;2~",    +1,    0},
    { XK_KP_Delete,     XK_ANY_MOD,     "\033[P",       -1,    0},
    { XK_KP_Delete,     XK_ANY_MOD,     "\033[3~",      +1,    0},
    { XK_KP_Multiply,   XK_ANY_MOD,     "\033Oj",       +2,    0},
    { XK_KP_Add,        XK_ANY_MOD,     "\033Ok",       +2,    0},
    { XK_KP_Enter,      XK_ANY_MOD,     "\033OM",       +2,    0},
    { XK_KP_Enter,      XK_ANY_MOD,     "\r",           -1,    0},
    { XK_KP_Subtract,   XK_ANY_MOD,     "\033Om",       +2,    0},
    { XK_KP_Decimal,    XK_ANY_MOD,     "\033On",       +2,    0},
    { XK_KP_Divide,     XK_ANY_MOD,     "\033Oo",       +2,    0},
    { XK_KP_0,          XK_ANY_MOD,     "\033Op",       +2,    0},
    { XK_KP_1,          XK_ANY_MOD,     "\033Oq",       +2,    0},
    { XK_KP_2,          XK_ANY_MOD,     "\033Or",       +2,    0},
    { XK_KP_3,          XK_ANY_MOD,     "\033Os",       +2,    0},
    { XK_KP_4,          XK_ANY_MOD,     "\033Ot",       +2,    0},
    { XK_KP_5,          XK_ANY_MOD,     "\033Ou",       +2,    0},
    { XK_KP_6,          XK_ANY_MOD,     "\033Ov",       +2,    0},
    { XK_KP_7,          XK_ANY_MOD,     "\033Ow",       +2,    0},
    { XK_KP_8,          XK_ANY_MOD,     "\033Ox",       +2,    0},
    { XK_KP_9,          XK_ANY_MOD,     "\033Oy",       +2,    0},
    { XK_Up,            ShiftMask,      "\033[1;2A",     0,    0},
    { XK_Up,            Mod1Mask,       "\033[1;3A",     0,    0},
    { XK_Up,         ShiftMask|Mod1Mask,"\033[1;4A",     0,    0},
    { XK_Up,            ControlMask,    "\033[1;5A",     0,    0},
    { XK_Up,      ShiftMask|ControlMask,"\033[1;6A",     0,    0},
    { XK_Up,       ControlMask|Mod1Mask,"\033[1;7A",     0,    0},
    { XK_Up,ShiftMask|ControlMask|Mod1Mask,"\033[1;8A",  0,    0},
    { XK_Up,            XK_ANY_MOD,     "\033[A",        0,   -1},
    { XK_Up,            XK_ANY_MOD,     "\033OA",        0,   +1},
    { XK_Down,          ShiftMask,      "\033[1;2B",     0,    0},
    { XK_Down,          Mod1Mask,       "\033[1;3B",     0,    0},
    { XK_Down,       ShiftMask|Mod1Mask,"\033[1;4B",     0,    0},
    { XK_Down,          ControlMask,    "\033[1;5B",     0,    0},
    { XK_Down,    ShiftMask|ControlMask,"\033[1;6B",     0,    0},
    { XK_Down,     ControlMask|Mod1Mask,"\033[1;7B",     0,    0},
    { XK_Down,ShiftMask|ControlMask|Mod1Mask,"\033[1;8B",0,    0},
    { XK_Down,          XK_ANY_MOD,     "\033[B",        0,   -1},
    { XK_Down,          XK_ANY_MOD,     "\033OB",        0,   +1},
    { XK_Left,          ShiftMask,      "\033[1;2D",     0,    0},
    { XK_Left,          Mod1Mask,       "\033[1;3D",     0,    0},
    { XK_Left,       ShiftMask|Mod1Mask,"\033[1;4D",     0,    0},
    { XK_Left,          ControlMask,    "\033[1;5D",     0,    0},
    { XK_Left,    ShiftMask|ControlMask,"\033[1;6D",     0,    0},
    { XK_Left,     ControlMask|Mod1Mask,"\033[1;7D",     0,    0},
    { XK_Left,ShiftMask|ControlMask|Mod1Mask,"\033[1;8D",0,    0},
    { XK_Left,          XK_ANY_MOD,     "\033[D",        0,   -1},
    { XK_Left,          XK_ANY_MOD,     "\033OD",        0,   +1},
    { XK_Right,         ShiftMask,      "\033[1;2C",     0,    0},
    { XK_Right,         Mod1Mask,       "\033[1;3C",     0,    0},
    { XK_Right,      ShiftMask|Mod1Mask,"\033[1;4C",     0,    0},
    { XK_Right,         ControlMask,    "\033[1;5C",     0,    0},
    { XK_Right,   ShiftMask|ControlMask,"\033[1;6C",     0,    0},
    { XK_Right,    ControlMask|Mod1Mask,"\033[1;7C",     0,    0},
    { XK_Right,ShiftMask|ControlMask|Mod1Mask,"\033[1;8C",0,   0},
    { XK_Right,         XK_ANY_MOD,     "\033[C",        0,   -1},
    { XK_Right,         XK_ANY_MOD,     "\033OC",        0,   +1},
    { XK_ISO_Left_Tab,  ShiftMask,      "\033[Z",        0,    0},
    { XK_Return,        Mod1Mask,       "\033\r",        0,    0},
    { XK_Return,        XK_ANY_MOD,     "\r",            0,    0},
    { XK_Insert,        ShiftMask,      "\033[4l",      -1,    0},
    { XK_Insert,        ShiftMask,      "\033[2;2~",    +1,    0},
    { XK_Insert,        ControlMask,    "\033[L",       -1,    0},
    { XK_Insert,        ControlMask,    "\033[2;5~",    +1,    0},
    { XK_Insert,        XK_ANY_MOD,     "\033[4h",      -1,    0},
    { XK_Insert,        XK_ANY_MOD,     "\033[2~",      +1,    0},
    { XK_Delete,        ControlMask,    "\033[M",       -1,    0},
    { XK_Delete,        ControlMask,    "\033[3;5~",    +1,    0},
    { XK_Delete,        ShiftMask,      "\033[2K",      -1,    0},
    { XK_Delete,        ShiftMask,      "\033[3;2~",    +1,    0},
    { XK_Delete,        XK_ANY_MOD,     "\033[P",       -1,    0},
    { XK_Delete,        XK_ANY_MOD,     "\033[3~",      +1,    0},
    { XK_BackSpace,     XK_NO_MOD,      "\177",          0,    0},
    { XK_BackSpace,     Mod1Mask,       "\033\177",      0,    0},
    { XK_Home,          ShiftMask,      "\033[2J",       0,   -1},
    { XK_Home,          ShiftMask,      "\033[1;2H",     0,   +1},
    { XK_Home,          XK_ANY_MOD,     "\033[H",        0,   -1},
    { XK_Home,          XK_ANY_MOD,     "\033[1~",       0,   +1},
    { XK_End,           ControlMask,    "\033[J",       -1,    0},
    { XK_End,           ControlMask,    "\033[1;5F",    +1,    0},
    { XK_End,           ShiftMask,      "\033[K",       -1,    0},
    { XK_End,           ShiftMask,      "\033[1;2F",    +1,    0},
    { XK_End,           XK_ANY_MOD,     "\033[4~",       0,    0},
    { XK_Prior,         ControlMask,    "\033[5;5~",     0,    0},
    { XK_Prior,         ShiftMask,      "\033[5;2~",     0,    0},
    { XK_Prior,         XK_ANY_MOD,     "\033[5~",       0,    0},
    { XK_Next,          ControlMask,    "\033[6;5~",     0,    0},
    { XK_Next,          ShiftMask,      "\033[6;2~",     0,    0},
    { XK_Next,          XK_ANY_MOD,     "\033[6~",       0,    0},
    { XK_F1,            XK_NO_MOD,      "\033OP" ,       0,    0},
    { XK_F1, /* F13 */  ShiftMask,      "\033[1;2P",     0,    0},
    { XK_F1, /* F25 */  ControlMask,    "\033[1;5P",     0,    0},
    { XK_F1, /* F37 */  Mod4Mask,       "\033[1;6P",     0,    0},
    { XK_F1, /* F49 */  Mod1Mask,       "\033[1;3P",     0,    0},
    { XK_F1, /* F61 */  Mod3Mask,       "\033[1;4P",     0,    0},
    { XK_F2,            XK_NO_MOD,      "\033OQ" ,       0,    0},
    { XK_F2, /* F14 */  ShiftMask,      "\033[1;2Q",     0,    0},
    { XK_F2, /* F26 */  ControlMask,    "\033[1;5Q",     0,    0},
    { XK_F2, /* F38 */  Mod4Mask,       "\033[1;6Q",     0,    0},
    { XK_F2, /* F50 */  Mod1Mask,       "\033[1;3Q",     0,    0},
    { XK_F2, /* F62 */  Mod3Mask,       "\033[1;4Q",     0,    0},
    { XK_F3,            XK_NO_MOD,      "\033OR" ,       0,    0},
    { XK_F3, /* F15 */  ShiftMask,      "\033[1;2R",     0,    0},
    { XK_F3, /* F27 */  ControlMask,    "\033[1;5R",     0,    0},
    { XK_F3, /* F39 */  Mod4Mask,       "\033[1;6R",     0,    0},
    { XK_F3, /* F51 */  Mod1Mask,       "\033[1;3R",     0,    0},
    { XK_F3, /* F63 */  Mod3Mask,       "\033[1;4R",     0,    0},
    { XK_F4,            XK_NO_MOD,      "\033OS" ,       0,    0},
    { XK_F4, /* F16 */  ShiftMask,      "\033[1;2S",     0,    0},
    { XK_F4, /* F28 */  ControlMask,    "\033[1;5S",     0,    0},
    { XK_F4, /* F40 */  Mod4Mask,       "\033[1;6S",     0,    0},
    { XK_F4, /* F52 */  Mod1Mask,       "\033[1;3S",     0,    0},
    { XK_F5,            XK_NO_MOD,      "\033[15~",      0,    0},
    { XK_F5, /* F17 */  ShiftMask,      "\033[15;2~",    0,    0},
    { XK_F5, /* F29 */  ControlMask,    "\033[15;5~",    0,    0},
    { XK_F5, /* F41 */  Mod4Mask,       "\033[15;6~",    0,    0},
    { XK_F5, /* F53 */  Mod1Mask,       "\033[15;3~",    0,    0},
    { XK_F6,            XK_NO_MOD,      "\033[17~",      0,    0},
    { XK_F6, /* F18 */  ShiftMask,      "\033[17;2~",    0,    0},
    { XK_F6, /* F30 */  ControlMask,    "\033[17;5~",    0,    0},
    { XK_F6, /* F42 */  Mod4Mask,       "\033[17;6~",    0,    0},
    { XK_F6, /* F54 */  Mod1Mask,       "\033[17;3~",    0,    0},
    { XK_F7,            XK_NO_MOD,      "\033[18~",      0,    0},
    { XK_F7, /* F19 */  ShiftMask,      "\033[18;2~",    0,    0},
    { XK_F7, /* F31 */  ControlMask,    "\033[18;5~",    0,    0},
    { XK_F7, /* F43 */  Mod4Mask,       "\033[18;6~",    0,    0},
    { XK_F7, /* F55 */  Mod1Mask,       "\033[18;3~",    0,    0},
    { XK_F8,            XK_NO_MOD,      "\033[19~",      0,    0},
    { XK_F8, /* F20 */  ShiftMask,      "\033[19;2~",    0,    0},
    { XK_F8, /* F32 */  ControlMask,    "\033[19;5~",    0,    0},
    { XK_F8, /* F44 */  Mod4Mask,       "\033[19;6~",    0,    0},
    { XK_F8, /* F56 */  Mod1Mask,       "\033[19;3~",    0,    0},
    { XK_F9,            XK_NO_MOD,      "\033[20~",      0,    0},
    { XK_F9, /* F21 */  ShiftMask,      "\033[20;2~",    0,    0},
    { XK_F9, /* F33 */  ControlMask,    "\033[20;5~",    0,    0},
    { XK_F9, /* F45 */  Mod4Mask,       "\033[20;6~",    0,    0},
    { XK_F9, /* F57 */  Mod1Mask,       "\033[20;3~",    0,    0},
    { XK_F10,           XK_NO_MOD,      "\033[21~",      0,    0},
    { XK_F10, /* F22 */ ShiftMask,      "\033[21;2~",    0,    0},
    { XK_F10, /* F34 */ ControlMask,    "\033[21;5~",    0,    0},
    { XK_F10, /* F46 */ Mod4Mask,       "\033[21;6~",    0,    0},
    { XK_F10, /* F58 */ Mod1Mask,       "\033[21;3~",    0,    0},
    { XK_F11,           XK_NO_MOD,      "\033[23~",      0,    0},
    { XK_F11, /* F23 */ ShiftMask,      "\033[23;2~",    0,    0},
    { XK_F11, /* F35 */ ControlMask,    "\033[23;5~",    0,    0},
    { XK_F11, /* F47 */ Mod4Mask,       "\033[23;6~",    0,    0},
    { XK_F11, /* F59 */ Mod1Mask,       "\033[23;3~",    0,    0},
    { XK_F12,           XK_NO_MOD,      "\033[24~",      0,    0},
    { XK_F12, /* F24 */ ShiftMask,      "\033[24;2~",    0,    0},
    { XK_F12, /* F36 */ ControlMask,    "\033[24;5~",    0,    0},
    { XK_F12, /* F48 */ Mod4Mask,       "\033[24;6~",    0,    0},
    { XK_F12, /* F60 */ Mod1Mask,       "\033[24;3~",    0,    0},
    { XK_F13,           XK_NO_MOD,      "\033[1;2P",     0,    0},
    { XK_F14,           XK_NO_MOD,      "\033[1;2Q",     0,    0},
    { XK_F15,           XK_NO_MOD,      "\033[1;2R",     0,    0},
    { XK_F16,           XK_NO_MOD,      "\033[1;2S",     0,    0},
    { XK_F17,           XK_NO_MOD,      "\033[15;2~",    0,    0},
    { XK_F18,           XK_NO_MOD,      "\033[17;2~",    0,    0},
    { XK_F19,           XK_NO_MOD,      "\033[18;2~",    0,    0},
    { XK_F20,           XK_NO_MOD,      "\033[19;2~",    0,    0},
    { XK_F21,           XK_NO_MOD,      "\033[20;2~",    0,    0},
    { XK_F22,           XK_NO_MOD,      "\033[21;2~",    0,    0},
    { XK_F23,           XK_NO_MOD,      "\033[23;2~",    0,    0},
    { XK_F24,           XK_NO_MOD,      "\033[24;2~",    0,    0},
    { XK_F25,           XK_NO_MOD,      "\033[1;5P",     0,    0},
    { XK_F26,           XK_NO_MOD,      "\033[1;5Q",     0,    0},
    { XK_F27,           XK_NO_MOD,      "\033[1;5R",     0,    0},
    { XK_F28,           XK_NO_MOD,      "\033[1;5S",     0,    0},
    { XK_F29,           XK_NO_MOD,      "\033[15;5~",    0,    0},
    { XK_F30,           XK_NO_MOD,      "\033[17;5~",    0,    0},
    { XK_F31,           XK_NO_MOD,      "\033[18;5~",    0,    0},
    { XK_F32,           XK_NO_MOD,      "\033[19;5~",    0,    0},
    { XK_F33,           XK_NO_MOD,      "\033[20;5~",    0,    0},
    { XK_F34,           XK_NO_MOD,      "\033[21;5~",    0,    0},
    { XK_F35,           XK_NO_MOD,      "\033[23;5~",    0,    0},
};

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
    [SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Printable characters in ASCII, used to estimate the advance width
 * of single wide characters.
 */
static char ascii_printable[] =
    " !\"#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~";

