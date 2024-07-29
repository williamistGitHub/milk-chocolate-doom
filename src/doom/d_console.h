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

#ifndef __D_CONSOLE__
#define __D_CONSOLE__

typedef void (*concmdcallback_t)(int argc, char** argv, void *callbackvar);

void D_RegisterConsoleCmd(const char *name, concmdcallback_t callback, void *callbackvar);
void D_ExecuteCmd(char *cmd);

#endif