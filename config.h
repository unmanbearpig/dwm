#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
/* border pixel of windows */
static const unsigned int borderpx  = 0;

/* border pixel of windows only for floating windows */
static const unsigned int borderpx_floating  = 1;

static const unsigned int snap      = 8;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:pixelsize=20:autohint=false:antialias=false:minspace=true" };
static const char dmenufont[]       =   "xos4 Terminus:pixelsize=20:antialias=false:autohint=false:minspace=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
  { "|||",      columns_layout },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *dmenu_xty_cmd[] = { "xty", NULL };
static const char *termcmd_main[]  = { "xterm", NULL };
static const char *termcmd_alt[]   = { "st", "bash", "--login", NULL };
static const char *browsercmd[]    = { "firefox-trunk", NULL };
static const char *mpvpastecmd[]   = { "mpvpaste", NULL };
static const char *mutecmd[]       = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *micmutecmd[]    = { "amixer", "-q", "set", "Capture", "toggle", NULL };
static const char *volupcmd[]      = { "amixer", "set", "Master", "1dB+", NULL };
static const char *voldowncmd[]    = { "amixer", "set", "Master", "1dB-", NULL };

// #define RightAltMask Mod3Mask

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,                    spawn,               {.v = dmenucmd } },
	{ MODKEY,                       XK_t,                    spawn,               {.v = dmenu_xty_cmd } },
	{ MODKEY,                       XK_Return,               spawn,               {.v = termcmd_main } },
	{ MODKEY|ShiftMask,             XK_Return,               spawn,               {.v = termcmd_alt } },
	{ MODKEY|ShiftMask,             XK_Return,               spawn,               {.v = browsercmd } },
	{ MODKEY|ControlMask,           XK_Return,               spawn,               {.v = mpvpastecmd } },
	{ 0,                            XF86XK_AudioMute,        spawn,               {.v = mutecmd } },
	{ 0,                            XF86XK_AudioMicMute,     spawn,               {.v = micmutecmd } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,               {.v = volupcmd } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,               {.v = voldowncmd } },
	{ MODKEY|ControlMask,           XK_m,                    spawn,               {.v = mutecmd } },
	{ MODKEY,                       XK_f,                    togglefullscr,       {0} },
	{ MODKEY,                       XK_m,                    zoom,                {0} },
	{ MODKEY|ShiftMask,             XK_f,                    togglefloating,      {0} },
	{ MODKEY,                       XK_b,                    togglebar,           {0} },
	{ MODKEY,                       XK_n,                    rotate,              {.i = -1 } },
	{ MODKEY,                       XK_p,                    rotate,              {.i = +1 } },
	{ MODKEY,                       XK_o,                    focusstack,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,                    focusstack,          {.i = -1 } },
	{ MODKEY,                       XK_i,                    incnmaster,          {.i = +1 } },
	{ MODKEY,                       XK_d,                    incnmaster,          {.i = -1 } },
	{ MODKEY,                       XK_h,                    setmfact,            {.f = -0.05} },
	{ MODKEY,                       XK_s,                    setmfact,            {.f = +0.05} },
	{ MODKEY,                       XK_Tab,                  view,                {0} },
	{ MODKEY,                       XK_q,                    killclient,          {0} },
	{ MODKEY,                       XK_comma,                setlayout,           {.v = &layouts[0]} },
	{ MODKEY,                       XK_period,               setlayout,           {.v = &layouts[2]} },
	{ MODKEY,                       XK_l,                    setlayout,           {.v = &layouts[3]} },
	{ MODKEY,                       XK_0,                    view,                {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,                 {.ui = ~0 } },
	{ MODKEY,                       XK_apostrophe,           focusmon,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                tagmon,              {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               tagmon,              {.i = +1 } },
	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,                    quit,                {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd_main } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
