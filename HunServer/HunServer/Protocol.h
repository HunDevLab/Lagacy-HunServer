#include <Windows.h>
#include <iostream>

#define MAX_BUFF_SIZE   4000
#define MAX_PACKET_SIZE  255

#define BOARD_WIDTH   300
#define BOARD_HEIGHT  300

#define VIEW_RADIUS   10

#define MAX_USER 100

#define NPC_START  500
#define NUM_OF_NPC  2000

#define MY_SERVER_PORT  4000

#define MAX_STR_SIZE  100

#define CS_UP    1
#define CS_DOWN  2
#define CS_LEFT  3
#define CS_RIGHT    4
#define CS_CHAT		5
#define CS_LOGIN	6
#define CS_ATTACK	7
#define CS_HEAL		8


#define SC_POS           1
#define SC_PUT_PLAYER    2
#define SC_REMOVE_PLAYER 3
#define SC_CHAT		4
#define SC_LOGIN_OK	5
#define SC_LOGIN_FAIL	6
#define SC_LEVELUP	7
#define SC_MONTERDAMAGE		8
#define SC_HEAL				9
#define SC_DEAD				10

#pragma pack (push, 1)

struct cs_packet_up {
	BYTE size;
	BYTE type;
};

struct cs_packet_down {
	BYTE size;
	BYTE type;
};

struct cs_packet_left {
	BYTE size;
	BYTE type;
};

struct cs_packet_right {
	BYTE size;
	BYTE type;
};

struct cs_packet_chat {
	BYTE size;
	BYTE type;
	WCHAR message[MAX_STR_SIZE];
};

struct cs_packet_login {
	BYTE	size;
	BYTE	type;
	char	id[10];
};
struct cs_packet_attack {
	BYTE	size;
	BYTE	type;
};

struct cs_packet_heal {
	BYTE	size;
	BYTE	type;
};


///////////// server - Client packet
struct sc_packet_pos {
	BYTE size;
	BYTE type;
	WORD id;
	UINT x;
	UINT y;
};


struct sc_packet_put_player {
	BYTE size;
	BYTE type;
	WORD id;
	UINT x;
	UINT y;
	int Exp;
	int LevelupExp;
	int hp;
	int mp;
	int att_power;
	int level;
};
struct sc_packet_remove_player {
	BYTE size;
	BYTE type;
	WORD id;
};

struct sc_packet_chat {
	BYTE size;
	BYTE type;
	WORD id;
	WCHAR message[MAX_STR_SIZE];
};

struct sc_packet_login {
	BYTE	size;
	BYTE	type;
	int		id;
	int		x;
	int		y;
	int		hp;
	int		exp;
	int		mp;
	int		level;
};

struct sc_packet_attack {
	BYTE size;
	BYTE type;
	UINT Exp;
	UINT LevelupExp;
	UINT hp;
	UINT mp;
	UINT level;
	UINT monsternum;
	UINT playerHP;
};

struct sc_packet_heal {
	BYTE	size;
	BYTE	type;
	int		hp;
	int		mp;
};
struct sc_packet_dead {
	BYTE	size;
	BYTE	type;
	int		x;
	int		y;
	int		hp;
};
#pragma pack (pop)
#pragma once
