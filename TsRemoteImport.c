/****************************************************************************

    X-IvAp  -  Martin Domig <martin@domig.net>
    Copyright (C) 2006 by Martin Domig
    Linux port (C) 2009 by Denis Misiurca

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

****************************************************************************/

/*
This is ported version of TsRemoteImport.pas (for Delphi)
creating a C "SDK" for TeamSpeak. Currently it only supports
windows, but this could easy be changed. It has not been
FULLY tested, but it should all work, if you have a bug report
please email me.  Do not email me if you are not 100% of what
you are doing, in other words I do not want to deal with someone
who simply cannot code, only genuine bug reports please.

Ported by:
Neil Popplewell
aka -TAT-Neo & Neo4E656F
email: neo@clantat.com
msn: x4e656f@hotmail.com
*/

#include <stdio.h>
#include <dlfcn.h>
#include "TsRemoteImport.h"

int InitTsRemoteLibrary(char TryLocal)
{
	tsrDLL = dlopen("/opt/teamspeak2-client/client_sdk/libTSRemote.so.0.4", RTLD_LAZY|RTLD_LOCAL);
	if (!tsrDLL)
		return -2;

	tsrQuit = dlsym(tsrDLL, "tsrQuit");
	tsrConnect = dlsym(tsrDLL, "tsrConnect");
	tsrDisconnect = dlsym(tsrDLL, "tsrDisconnect");
	tsrSendTextMessage = dlsym(tsrDLL, "tsrSendTextMessage");
	tsrSendTextMessageToChannel = dlsym(tsrDLL, "tsrSendTextMessageToChannel");
	tsrSwitchChannelID = dlsym(tsrDLL,"tsrSwitchChannelID");
	tsrSwitchChannelName = dlsym(tsrDLL,"tsrSwitchChannelName");
	tsrGetLastError = dlsym(tsrDLL,"tsrGetLastError");
	tsrSetWantVoiceReason = dlsym(tsrDLL,"tsrSetWantVoiceReason");
	tsrSetVoice = dlsym(tsrDLL,"tsrSetVoice");
	tsrSetOperator = dlsym(tsrDLL,"tsrSetOperator");
	tsrSetPlayerFlags = dlsym(tsrDLL,"tsrSetPlayerFlags");
	tsrKickPlayerFromServer = dlsym(tsrDLL,"tsrKickPlayerFromServer");
	tsrKickPlayerFromChannel = dlsym(tsrDLL,"tsrKickPlayerFromChannel");
	tsrGetVersion = dlsym(tsrDLL,"tsrGetVersion");
	tsrGetUserInfo = dlsym(tsrDLL,"tsrGetUserInfo");
	tsrGetChannelInfoByID = dlsym(tsrDLL,"tsrGetChannelInfoByID");
	tsrGetChannelInfoByName = dlsym(tsrDLL,"tsrGetChannelInfoByName");
	tsrGetPlayerInfoByID = dlsym(tsrDLL,"tsrGetPlayerInfoByID");
	tsrGetPlayerInfoByName = dlsym(tsrDLL,"tsrGetPlayerInfoByName");
	tsrGetServerInfo = dlsym(tsrDLL,"tsrGetServerInfo");
	tsrGetPlayers = dlsym(tsrDLL,"tsrGetPlayers");
	tsrGetChannels = dlsym(tsrDLL,"tsrGetChannels");
	if (!tsrQuit || !tsrDisconnect || !tsrConnect || !tsrSendTextMessage || !tsrSendTextMessageToChannel
		|| !tsrSwitchChannelID || !tsrSwitchChannelID || !tsrGetLastError || !tsrSetWantVoiceReason
		|| !tsrSetVoice || !tsrSetOperator || !tsrSetPlayerFlags || !tsrKickPlayerFromServer
		|| !tsrKickPlayerFromChannel || !tsrGetVersion || !tsrGetUserInfo || !tsrGetChannelInfoByID
		|| !tsrGetChannelInfoByName || !tsrGetPlayerInfoByID|| !tsrGetPlayerInfoByName
		|| !tsrGetServerInfo || !tsrGetChannels) return -3;
	else return 0;
}
int CloseTsRemoteLibrary()
{
	if (!tsrDLL) return -1;
	return dlclose(tsrDLL)?0:-2;
}
