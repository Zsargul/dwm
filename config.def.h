/* See LICENSE file for copyright and license details. */

#define TERM "st"
#define BROWSER "qutebrowser"

/* Appearance */
static const char *fonts[]          = { "Terminus:style=Bold:size=16:autohint=true" };
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char dmenufont[]       = "Terminus:style=Bold:size=16:autohint=true";

/* Gaps & Border */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 5;        /* border pixel of windows */

/* Colors */
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

/* Tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask // Mod key | Alt = Mod1 | Win = Mod4
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Helpers for spawning shell commands in the pre dwm-5.0 fashion, as well as terminal commands (used for TUI programs like ranger) */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMCMD(cmd) { .v = (const char*[]){ TERM, "-e", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* Commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { TERM, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument                                                              description */

	/* Spawning applications/shell commands */
	{ MODKEY,                       XK_Return, spawn,          SHCMD(TERM) },                                                        // Terminal
	{ MODKEY,                       XK_d,      spawn,          SHCMD("rofi -show-icons -show drun -drun-display-format {name}") },   // Program launcher
	{ MODKEY,                       XK_m,      spawn,          SHCMD("spotify") },                                                   // Music player	
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },                                                     // Browser
	{ MODKEY,                       XK_p,      spawn,          TERMCMD("pulsemixer") },                                              // Audio mixer
	{ MODKEY,                       XK_f,      spawn,          SHCMD("flameshot gui") },                                             // Screenshot	
	{ MODKEY,                       XK_t,      spawn,          SHCMD("telegram-desktop") },                                          // Telegram

	/* Window manipulation keys */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* Exit DWM */
	{ MODKEY|ShiftMask,             XK_F24,    quit,           {1} }, 																	 
																	 
	/* Tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* Unused commands. Defined with 'NULL' as key and cast to long unsigned int to avoid build warnings. */
	{ MODKEY,                       (long unsigned int)NULL,      togglebar,      {0} },
	{ MODKEY,                       (long unsigned int)NULL,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       (long unsigned int)NULL,      zoom,           {0} },
	
	/* Gap related keybinds */
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              (long unsigned int)NULL,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    (long unsigned int)NULL,      defaultgaps,    {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

