/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Aleo:size=13" };
static const char dmenufont[]       = "Aleo:size=13";

static const char normbordercolor[] = "#f6f6f6";
static const char normbgcolor[]     = "#f6f6f6";
static const char normfgcolor[]     = "#1d1f21";
static const char selbordercolor[]  = "#e5ae38";
static const char selbgcolor[]      = "#1177aa";
static const char selfgcolor[]      = "#ffffff";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel] =  { selfgcolor, selbgcolor,  selbordercolor },
};

/* tagging */
static const char *tags[] = {
  "base", "web", "dev", "doc", "img",
  "vid", "mus", "eml", "foo",
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
  { "Firefox",       NULL,        NULL,          1 << 1,  False,       -1 },
  { "Chromium",      NULL,        NULL,          1 << 1,  False,       -1 },
  { "chromium",      NULL,        NULL,          1 << 1,  False,       -1 },
  { "qutebrowser",   NULL,        NULL,          1 << 1,  False,       -1 },
  { "Vimb",          NULL,        NULL,          1 << 1,  False,       -1 },
  { "tabbed",        NULL,        NULL,          1 << 1,  False,       -1 },
  {  NULL,           NULL,        "evim",        1 << 2,  False,       -1 },
  { "Zathura",       NULL,        NULL,          1 << 3,  False,       -1 },
  { "Sxiv",          NULL,        NULL,          1 << 4,  False,       -1 },
  { "Inkscape",      NULL,        NULL,          1 << 4,  False,       -1 },
  { "mpv",           NULL,        NULL,          1 << 5,  False,       -1 },
  { "VidyoDesktop",  NULL,        NULL,          1 << 5,  False,       -1 },
  { "vncviewer",     "Vncviewer", NULL,          1 << 5,  False,       -1 },
  {  NULL,           NULL,        "cmus",        1 << 6,  False,       -1 },
  {  NULL,           NULL,        "mutt",        1 << 7,  False,       -1 },
  {  NULL,           NULL,        "scratchpad",  0,       True,        -1 },
  {  NULL,           NULL,        "todo",        0,       True,        -1 },
  {  NULL,           NULL,        "esp",        0,       True,         -1 },
  { "Gcolor2",       NULL,        NULL,          0,       True,        -1 },
  { "Lxappearance",  NULL,        NULL,          0,       True,        -1 },
  { "XFontSel",      NULL,        NULL,          0,       True,        -1 },
  { "Wine",          NULL,        NULL,          0,       True,        -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]       = { "kitty", NULL };
static const char *irssicmd[]      = { "kitty", "-t", "irssi", "-e", "irssi", NULL };
static const char *lockcmd[]       = { "slock", NULL };
static const char *mailcmd[]       = { "kitty", "-t", "mutt", "-e", "mutt", NULL };
static const char *muscmd[]        = { "st", "-t", "cmus", "-e", "cmus", NULL };
static const char *musnext[]       = { "st", "-e", "cmus-remote", "--next", NULL };
static const char *muspause[]      = { "st", "-e", "cmus-remote", "--pause", NULL };
static const char *musprev[]       = { "st", "-e", "cmus-remote", "--prev", NULL };
static const char *padcmd[]        = { "st", "-t", "scratchpad", "-g", "56x10-30+40", NULL };
static const char *rangercmd[]     = { "st", "-t", "ranger", "-e", "ranger", NULL };
static const char *tmuxcmd[]       = { "st", "-t", "tmux", "-e", "tmux", "-f", "/home/moritz/.tmux.conf", NULL };
static const char *todocmd[]       = { "st", "-t", "todo", "-e", "vim", "/home/moritz/TODO", NULL };
static const char *espcmd[]        = { "st", "-t", "esp", "-e", "vim", "/home/moritz/ESP", NULL };
static const char *voldowncmd[]    = { "pactl", "set-sink-volume", "0", "-2%", NULL };
static const char *volupcmd[]      = { "pactl", "set-sink-volume", "0", "+2%", NULL };
static const char *lightdowncmd[]    = { "xbacklight", "-10", NULL };
static const char *lightupcmd[]      = { "xbacklight", "+10", NULL };
static const char *voloffcmd[]     = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *brightupcmd[]   = { "xbacklight", "-inc", "10", NULL };
static const char *brightdowncmd[] = { "xbacklight", "-doc", "10", NULL };
static const char *printcmd[]      = { "scrot", NULL };
static const char *printfocuscmd[] = { "scrot", "--focused", NULL };
static const char *webcmd[]        = { "/home/moritz/bin/run_browser", NULL };
static const char *chromecmd[]     = { "chromium", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_v,      spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_Return, zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { 0,                 0x1008ff12,  spawn,           {.v = voloffcmd } },
  { 0,                 0x1008ff11,  spawn,           {.v = voldowncmd } },
  { 0,                 0x1008ff13,  spawn,           {.v = volupcmd } },
  { 0,                 0x1008ff03,  spawn,           {.v = lightdowncmd } },
  { 0,                 0x1008ff02,  spawn,           {.v = lightupcmd } },
  { 0,                 0x1008ff14,  spawn,           {.v = muspause } },
  { 0,                 0x1008ff16,  spawn,           {.v = musprev } },
  { 0,                 0x1008ff17,  spawn,           {.v = musnext } },
  { MODKEY|ShiftMask,  XK_v,        spawn,           {.v = webcmd} },
  { MODKEY|ShiftMask,  XK_w,        spawn,           {.v = chromecmd} },
  { MODKEY|ShiftMask,  XK_i,        spawn,           {.v = irssicmd} },
  { MODKEY|ShiftMask,  XK_l,        spawn,           {.v = lockcmd} },
  { MODKEY|ShiftMask,  XK_m,        spawn,           {.v = mailcmd} },
  { MODKEY|ShiftMask,  XK_s,        spawn,           {.v = padcmd} },
  { MODKEY|ShiftMask,  XK_o,        spawn,           {.v = muscmd} },
  { MODKEY,            XK_p,        spawn,           {.v = printcmd} },
  { MODKEY|ShiftMask,  XK_p,        spawn,           {.v = printfocuscmd} },
  { MODKEY|ShiftMask,  XK_r,        spawn,           {.v = rangercmd} },
  { MODKEY|ShiftMask,  XK_t,        spawn,           {.v = tmuxcmd} },
  { MODKEY|ShiftMask,  XK_y,        spawn,           {.v = todocmd} },
  { MODKEY|ShiftMask,  XK_e,        spawn,           {.v = espcmd} },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        toggleview,     {0} },
  { ClkTagBar,            0,              Button3,        view,           {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
