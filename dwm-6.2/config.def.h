/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CodeNewRoman Nerd Font:size=11" };
static const char dmenufont[]       = "CodeNewRoman Mono:size=10";
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
    { "discord",                "discord",          "Discord",  1 << 6,       0,           -1 },
	 */
	/* class                    instance            title       tags mask     isfloating   monitor */
	{ "Gimp",                   NULL,                   NULL,                   0,            0,           -1 },
    { "jetbrains-clion",        "jetbrains-clion",      NULL,                   1 << 0,       0,           -1 },
    { "Eclipse",                "Eclipse",              NULL,                   1 << 0,       0,           -1 },
	{ "Firefox",                NULL,                   NULL,                   1 << 1,       0,           -1 },
	{ "Zenkit",                 "zenkit",               NULL,                   1 << 2,       0,           -1 },
	{ "DBeaver",                "DBeaver",              NULL,                   1 << 3,       0,           -1 },
	{ "Thunderbird",            "Mail",                 NULL,                   1 << 4,       0,           -1 },
	{ "dolphin",                "dolphin",              NULL,                   1 << 5,       0,           -1 },
	{ "Org.gnome.Nautilus",     "org.gnome.Nautilus",   NULL,                   1 << 5,       0,           -1 },
	{ "st-256color",            "st-256color",          "ranger",               1 << 5,       0,           -1 },
    { "discord",                "discord",              NULL,                   1 << 6,       0,           -1 },
	{ "TelegramDesktop",        "telegram-desktop",     NULL,                   1 << 7,       0,           -1 },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,"-b" ,"-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

// Terminal
static const char* cmus[] = {"st","-e","cmus", NULL};
static const char* nvim[] = {"st", "-e", "nvim", NULL};
static const char* ranger[] = {"st", "-e","ranger", NULL};

// Browsers
static const char* qutebrowser[] = {"qutebrowser", NULL};
static const char* chrome[] = {"google-chrome-stable", NULL};
static const char* firefox[] = {"firefox", NULL};

// Editors
static const char* vscode[] = {"code", NULL};
static const char* clion[] = {"clion", NULL};
static const char* pycharm[] = {"pycharm", NULL};

// Misc
static const char* zenkit[] = {"zenkit", NULL};

// Commands
static const char* shutDown[] = {"poweroff", NULL};
static const char* volumeUp[] = {"amixer", "-q", "sset", "Master", "2%+", "unmute", NULL};
static const char* volumeDown[] = {"amixer", "-q", "sset", "Master", "2%-", "unmute", NULL};
static const char* toggleVolume[] = {"amixer","sset", "Master", "toggle", NULL};


/* Media Controls */
static const char* nextSong[] = {"playerctl", "next", NULL};
static const char* previousSong[] = {"playerctl", "previous", NULL};
static const char* playPauseMusic[] = {"playerctl", "play-pause", NULL};

static const char* lowerLight[] = {"xbacklight", "-dec", "2%"};
static const char* higherLight[] = {"xbacklight", "-inc", "2%"};

static Key keys[] = {
    /* ---------------- Personal Commands ---------------- */

    { MODKEY,               		XK_q,    spawn,           {.v = qutebrowser}},
    { MODKEY|ShiftMask,     		XK_c,    spawn,           {.v = chrome}},
    { MODKEY|ControlMask,     		XK_f,    spawn,           {.v = firefox}},

    { MODKEY,               		XK_v,    spawn,           {.v = vscode}},
    { MODKEY|ControlMask,   		XK_c,    spawn,           {.v = clion}},
    { MODKEY|ShiftMask,     		XK_p,    spawn,           {.v = pycharm}},

    { MODKEY,               		XK_w,    spawn,           {.v = zenkit}},

    { MODKEY,               		XK_r,    spawn,           {.v = ranger}},
    { MODKEY|ShiftMask,     		XK_m,    spawn,           {.v = cmus}},
    { MODKEY|ShiftMask,     		XK_n,    spawn,           {.v = nvim}},

    { MODKEY|ShiftMask|ControlMask,	XK_c, 	 spawn,      	  {.v = shutDown}},

    { NULL,    	                    XF86XK_AudioMute,   	    spawn,           {.v = toggleVolume}},
    { NULL,                         XF86XK_AudioLowerVolume,    spawn,           {.v = volumeDown}},
    { NULL,                         XF86XK_AudioRaiseVolume,    spawn,           {.v = volumeUp}},


    { NULL,                         XF86XK_AudioPlay,           spawn,           {.v = playPauseMusic}},
    { NULL,                         XF86XK_AudioPrev,           spawn,           {.v = previousSong}},
    { NULL,                         XF86XK_AudioNext,           spawn,           {.v = nextSong}},


    { NULL,                         XF86XK_MonBrightnessDown,   spawn,           {.v = lowerLight}},
    { NULL,                         XF86XK_MonBrightnessUp,   	spawn,           {.v = higherLight}},
    

    /* ---------------------------------------------------- */
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_a,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

