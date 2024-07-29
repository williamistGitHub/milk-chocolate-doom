//
// Copyright(C) 2024 williamist
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	All console code lives here (hud/input in hu_stuff.c)
//

#include "d_console.h"

#include <stdlib.h>
#include "i_system.h"
#include "m_misc.h"
#include "doomstat.h"

#define MAX_CONCMDS 64
#define MAX_CONARGS 8

typedef struct
{
    const char *name;
    concmdcallback_t callback;
    void *callbackvar;
} concmd_t;

static concmd_t concmds[MAX_CONCMDS];
static int concmds_length = 0;

void D_RegisterConsoleCmd(const char *name, concmdcallback_t callback,
                          void *callbackvar)
{
    if (concmds_length == MAX_CONCMDS)
    {
        I_Error("Error: attempted to register console command '%s' when max commands have been reached.", name);
        return;
    }
    
    concmd_t cmd = {name, callback, callbackvar};
    concmds[concmds_length++] = cmd;
}

void D_ExecuteCmd(char *cmd)
{
    char *tempcmd = M_StringDuplicate(cmd);
    M_ForceLowercase(tempcmd);
    static char *argv[MAX_CONARGS];

    // build argv list
    int argc = 1;
    argv[0] = tempcmd;
    char *argvcmd = tempcmd;
    while (*argvcmd)
    {
        if (*argvcmd == ' ')
        {
            argv[argc++] = argvcmd + 1;
            *argvcmd = '\0';

            // we hit max args, break
            if (argc == MAX_CONARGS)
                break;
        }

        argvcmd++;
    }

    // search for command
    for (int i = 0; i < concmds_length; i++)
    {
        if (!strcmp(argv[0], concmds[i].name))
        {
            concmds[i].callback(argc, argv, concmds[i].callbackvar);
            goto end;
        }
    }

    players[consoleplayer].message = "Unknown command";

    end:
    free(tempcmd);
}