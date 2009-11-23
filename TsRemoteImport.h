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
#ifndef TEAMSPEAK_REMOTE_H
#define TEAMSPEAK_REMOTE_H

#define cCodecCelp51        0
#define cCodecCelp63        1
#define cCodecGSM148        2
#define cCodecGSM164        3
#define cCodecWindowsCELP52 4

	  //Codec masks
#define cmCelp51        (1 << cCodecCelp51)
#define cmCelp63        (1 << cCodecCelp63)
#define cmGSM148        (1 << cCodecGSM148)
#define cmGSM164        (1 << cCodecGSM164)
#define cmWindowsCELP52 (1 << cCodecWindowsCELP52)

	  //PlayerChannel Privileges
#define pcpAdmin        (1 << 0)
#define pcpOperator     (1 << 1)
#define pcpAutoOperator (1 << 2)
#define pcpVoiced       (1 << 3)
#define pcpAutoVoice    (1 << 4)

	  //PlayerPrivileges
#define ppSuperServerAdmin (1 << 0)
#define ppServerAdmin      (1 << 1)
#define ppCanRegister      (1 << 2)
#define ppRegistered       (1 << 3)
#define ppUnregistered     (1 << 4)

	  //player flags
#define pfChannelCommander (1 << 0)
#define pfWantVoice        (1 << 1)
#define pfNoWhisper        (1 << 2)
#define pfAway             (1 << 3)
#define pfInputMuted       (1 << 4)
#define pfOutputMuted      (1 << 5)
#define pfRecording        (1 << 6)

	  //channel flags
#define cfRegistered   (1 << 0)
#define cfUnregistered (1 << 1)
#define cfModerated    (1 << 2)
#define cfPassword     (1 << 3)
#define cfHierarchical (1 << 4)
#define cfDefault      (1 << 5)

	  //ServerType Flags
#define stClan       (1 << 0)
#define stPublic     (1 << 1)
#define stFreeware   (1 << 2)
#define stCommercial (1 << 3)

#define grRevoke 0
#define grGrant  1

#pragma pack(push,1) //Byte alignment
struct TtsrVersion
{
	int Major;
	int Minor;
	int Release;
	int Build;
};
struct TtsrPlayerInfo
{
	int PlayerID;
	int ChannelID;
	char NickName[30];
	int PlayerChannelPrivileges;
	int PlayerPrivileges;
	int PlayerFlags;
};
struct TtsrServerInfo
{
	char ServerName[30];
	char WelcomeMessage[256];
	int ServerVMajor;
	int ServerVMinor;
	int ServerVRelease;
	int ServerVBuild;
	char ServerPlatform[30];
	char ServerIp[30];
	char ServerHost[100];
	int ServerType;
	int ServerMaxUsers;
	int SupportedCodecs;
	int ChannelCount;
	int PlayerCount;
};

struct TtsrChannelInfo
{
	int ChannelID;
	int ChannelParentID;
	int PlayerCountInChannel;
	int ChannelFlags;
	int Codec;
	char Name[30];
};
struct TtsrUserInfo
{
	struct TtsrPlayerInfo Player;
	struct TtsrChannelInfo Channel;
	struct TtsrChannelInfo ParentChannel;
};
#pragma pack(pop)

void *tsrDLL;

//##############################################################################
//#
//#  Function int InitTsRemoteLibrary(BOOL TryLocal);
//#
//#  Description:
//#    Loads and binds the TSRemote library
//#
//#  Input:
//#    TryLocal: if true, it will try to load the library from the same dir
//#              as the program location. If that fails it will fall back to
//#              the default locations.
//#
//#  Output:
//#    Result: (0=ok, -1= library already initialized,
//#             -2=error loading library
//#             -3=error during binding functions
//#
//##############################################################################
int InitTsRemoteLibrary(char TryLocal);

//##############################################################################
//#
//#  Function int CloseTsRemoteLibrary();
//#
//#  Description:
//#    Frees the hawkvoice library loaded by InitTsRemoteLibrary
//#
//#  Input:
//#    None
//#
//#  Output:
//#    Result: (0=ok, -1= library not initialized, -2=error during FreeLibrary
//#
//##############################################################################
int CloseTsRemoteLibrary();

//##############################################################################
//#
//#  Procedure int tsrGetLastError(char *pchBuffer, int BufferLength);
//#
//#  Description:
//#    Get the full error message that was send with the last error
//#
//#  Input:
//#    pchBuffer: A pointer to a nulterminated string where the error message
//#               will be copied to.
//#    BufferLength: The size of pchBuffer
//#
//#  Output:
//#    None
//#
//##############################################################################
void (*tsrGetLastError)(char *pchBuffer, int BufferLength);

//##############################################################################
//#
//#  Function int tsrConnect(char* URL);
//#
//#  Description:
//#    Connect the ts to a new server as described in the URL. Will disconnect
//#    if the client is currently connected. The Url is the same format as the
//#    normal starup link ("teamspeak://voice.teamspeak.org:9500" etc)
//#
//#  Input:
//#    URL: A pointer to a null terminated string containing the url for the
//#         server.
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrConnect)(char* URL);

//##############################################################################
//#
//#  Function int tsrDisconnect();
//#
//#  Description:
//#    Disconnects the client from the current server.
//#
//#  Input:
//#    None
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrDisconnect)(void);

//##############################################################################
//#
//#  Function int tsrQuit();
//#
//#  Description:
//#    Disconnect, Close and terminate the client.
//#
//#  Input:
//#    None
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrQuit)(void);

//##############################################################################
//#
//#  Function int tsrSwitchChannelName(char *ChannelName, char *ChannelPassword);
//#
//#  Description:
//#    Switch to the channel with the name "Channelname"
//#    Not that tsrSwitchChannelID is preferred.
//#
//#  Input:
//#    ChannelName: Name of the channel to switch to
//#    ChannelPassword: Password for the channel. May be nil
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSwitchChannelName)(char *ChannelName, char *ChannelPassword);

//##############################################################################
//#
//#  Function int tsrSwitchChannelID(int ChannelID, char *ChannelPassword);
//#
//#  Description:
//#    Switch to the channel with the id "channelID"
//#
//#  Input:
//#    ChannelID : ID of the channel to switch to
//#    ChannelPassword: Password for the channel. May be nil
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSwitchChannelID)(int ChannelID, char *ChannelPassword);

//##############################################################################
//#
//#  Function int tsrGetVersion(TtsrVersion *tsrVersion);
//#
//#  Description:
//#    Get the version of the ts client
//#
//#  Input:
//#    Pointer to a TtsrVersion record
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrVersion is filled with the client version
//#
//##############################################################################
int (*tsrGetVersion)(struct TtsrVersion *tsrVersion);

//##############################################################################
//#
//#  Function int TtsrGetServerInfo(TtsrServerInfo *tsrServerInfo);
//#
//#  Description:
//#    Get the Info on the server (name, channelcount, playercount etc etc)
//#
//#  Input:
//#    Pointer to a TtsrServerInfo record
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrServerInfo is filled with the server info
//#
//##############################################################################
int (*tsrGetServerInfo)(struct TtsrServerInfo *tsrServerInfo);

//##############################################################################
//#
//#  Function int tsrGetUserInfo(TtsrUserInfo *tsrUserInfo);
//#
//#  Description:
//#    Get the Info on the user (name, channel, flags etc etc)
//#
//#  Input:
//#    Pointer to a TtsrUserInfo record
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrUserInfo is filled with the user info
//#
//##############################################################################
int (*tsrGetUserInfo)(struct TtsrUserInfo *tsrUserInfo);

//##############################################################################
//#
//#  Function int tsrGetChannelInfoByID(int ChannelID,
//#					TtsrChannelInfo *tsrChannelInfo,
//#					TtsrPlayerInfo *tsrPlayerInfo,
//#					int *PlayerRecords);
//#
//#  Description:
//#    Get the Info on the channel specified by ChannelID and optionally also
//#    get the users from that channel
//#
//#  Input:
//#    ChannelID: The ID of the channel you want the info from
//#    tsrChannelInfo: pointer to a TtsrChannelInfo record;
//#    tsrPlayerInfo: This is the pointer to an array of TtsrPlayerInfo records
//#                   If it is NIL, no player records will be retrieved
//#    PlayerRecords: Pointer to an integer. It must contain how many records
//#                   tsrPlayerInfo has room for. (records, not bytes)
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrChannelInfo is filled with the channel info.
//#                If tsrPlayerInfo was not NIL then the player records are
//#                filled. PlayerRecords indicates how many records were filled
//#
//##############################################################################
int (*tsrGetChannelInfoByID)(int ChannelID,
				struct TtsrChannelInfo *tsrChannelInfo,
				struct TtsrPlayerInfo *tsrPlayerInfo,
				int *PlayerRecords);

//##############################################################################
//#
//#  Function int tsrGetChannelInfoByName(char *ChannelName,
//#					  TtsrChannelInfo *tsrChannelInfo,
//#					  TtsrPlayerInfo *tsrPlayerInfo,
//#					  int *PlayerRecords);
//#
//#  Description:
//#    Get the Info on the channel specified by ChannelName and optionally also
//#    get the users from that channel
//#
//#  Input:
//#    ChannelName: The Name of the channel you want the info from
//#    tsrChannelInfo: pointer to a TtsrChannelInfo record;
//#    tsrPlayerInfo: This is the pointer to an array of TtsrPlayerInfo records
//#                   If it is NIL, no player records will be retrieved
//#    PlayerRecords: Pointer to an integer. It must contain how many records
//#                   tsrPlayerInfo has room for. (records, not bytes)
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrChannelInfo is filled with the channel info.
//#                If tsrPlayerInfo was not NIL then the player records are
//#                filled. PlayerRecords indicates how many records were filled
//#
//##############################################################################
int (*tsrGetChannelInfoByName)(char *ChannelName,
				struct TtsrChannelInfo *tsrChannelInfo,
				struct TtsrPlayerInfo *tsrPlayerInfo,
				int *PlayerRecords);

//##############################################################################
//#
//#  Function int tsrGetPlayerInfoByID(int PlayerID,
//#					   TtsrPlayerInfo *tsrServerInfo);
//#
//#  Description:
//#    Get the Info on the player specified by PlayerID.
//#
//#  Input:
//#    PlayerID: The ID of the player you want the info from
//#    tsrPlayerInfo: This is the pointer to a TtsrPlayerInfo record
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrPlayerInfo is filled with the player info.
//#
//##############################################################################
int (*tsrGetPlayerInfoByID)(int PlayerID,
			    struct TtsrPlayerInfo *tsrServerInfo);
//##############################################################################
//#
//#  Function int tsrGetPlayerInfoByName(char *PlayerName,
//#					   TtsrPlayerInfo *tsrServerInfo);
//#
//#  Description:
//#    Get the Info on the player specified by PlayerName.
//#
//#  Input:
//#    PlayerName: The Name of the player you want the info from
//#    tsrPlayerInfo: This is the pointer to a TtsrPlayerInfo record
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrPlayerInfo is filled with the player info.
//#
//##############################################################################
int (*tsrGetPlayerInfoByName)(char *PlayerName,
			      struct TtsrPlayerInfo *tsrServerInfo);

//##############################################################################
//#
//#  Function int tsrGetChannels(TtsrChannelInfo *tsrChannels,
//#				 int *ChannelRecords);
//#
//#  Description:
//#    Get a list of the channels on the server.
//#
//#  Input:
//#    tsrChannels: A pointer to an array of TtsrChannelInfo records
//#    ChannelRecords: pointer to a integer which specifies how many
//#                    TtsrChannelInfo records tsrChannels can hold.
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrChannels is filled with the channel info.
//#              ChannelRecords will have the number or records that were filled
//#
//##############################################################################
int (*tsrGetChannels)(struct TtsrChannelInfo *tsrChannels,
			int *ChannelRecords);

//##############################################################################
//#
//#  Function int tsrGetPlayers(TtsrPlayerInfo *tsrPlayers,
//#					  int *PlayerRecords);
//#
//#  Description:
//#    Get a list of the Players on the server.
//#
//#  Input:
//#    tsrPlayers: A pointer to an array of TtsrPlayerInfo records
//#    PlayerRecords: pointer to a integer which specifies how many
//#                    TtsrPlayerInfo records tsrPlayers can hold.
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#    if result = 0 then tsrPlayers is filled with the Player info.
//#              PlayerRecords will have the number or records that were filled
//#
//##############################################################################
int (*tsrGetPlayers)(struct TtsrPlayerInfo *tsrPlayers,
			int *PlayerRecords);

//##############################################################################
//#
//#  Function int tsrSetPlayerFlags(int tsrPlayerFlags );
//#
//#  Description:
//#    Set player flags of the user
//#
//#  Input:
//#    tsrPlayerFlags: An integer wich has the bitmask for all the flags
//#                    All flags are set to this bitmask.
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSetPlayerFlags)(int tsrPlayerFlags );

//##############################################################################
//#
//#  Function int tsrSetWantVoiceReason(char *tsrReason);
//#
//#  Description:
//#    set the reason you want voice on a channel
//#
//#  Input:
//#    tsrReason: The reseason for voice
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSetWantVoiceReason)(char *tsrReason);

//##############################################################################
//#
//#  Function int tsrSetOperator(int PlayerID,int GrantRevoke);
//#
//#  Description:
//#    Grant or revoke Operator status
//#
//#  Input:
//#    PlayerID: ID of the player to set the operator status for
//#    GrantRevoke: Set to grGrant to grant or grRevoke to revoke the privilege
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSetOperator)(int PlayerID,int GrantRevoke);

//##############################################################################
//#
//#  Function int tsrSetVoice(int PlayerID,int GrantRevoke);
//#
//#  Description:
//#    Grant or revoke Voice status
//#
//#  Input:
//#    PlayerID: ID of the player to set the Voice status for
//#    GrantRevoke: Set to grGrant to grant or grRevoke to revoke the privilege
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSetVoice)(int PlayerID,int GrantRevoke);

//##############################################################################
//#
//#  Function int tsrKickPlayerFromServer(int PlayerID, char *Reason);
//#
//#  Description:
//#    Kick a player from the server;
//#
//#  Input:
//#    PlayerID: ID of the player to set the Voice status for
//#    Reason: The reason why he was kicked
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrKickPlayerFromServer)(int PlayerID, char *Reason);

//##############################################################################
//#
//#  Function int tsrKickPlayerFromChannel(int PlayerID, char *Reason);
//#
//#  Description:
//#    Kick a player from the Channel;
//#
//#  Input:
//#    PlayerID: ID of the player to set the Voice status for
//#    Reason: The reason why he was kicked
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrKickPlayerFromChannel)(int PlayerID, char *Reason);

//##############################################################################
//#
//#  Function int tsrSendTextMessageToChannel(int ChannelID,char *Message);
//#
//#  Description:
//#    Send a text message to a channel
//#
//#  Input:
//#    ChannelID: The ID of the channel you want to send the txt message to
//#    Message : The message you want to send.
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSendTextMessageToChannel)(int ChannelID, char *Message);

//##############################################################################
//#
//#  Function int tsrSendTextMessage(char *Message);
//#
//#  Description:
//#    Send a text message to everyone
//#
//#  Input:
//#    Message : The message you want to send.
//#
//#  Output:
//#    Result: 0 = OK, else the error number
//#
//##############################################################################
int (*tsrSendTextMessage)(char *Message);

#endif
