#include "stdafx.h"

#define MAX_BUFF_SIZE   4000
#define MAX_PACKET_SIZE  255
#define MAX_USER 100
#define MY_SERVER_PORT  4000

// ---------------------------------------------------
//				Client -> Server Type
// ---------------------------------------------------
#define CS_LOGIN_REQ	1


// ---------------------------------------------------
//				Server -> Client Type
// ---------------------------------------------------
#define SC_LOGIN_RES		101
#define SC_PUT_PLAYER		102
#define SC_REMOVE_PLAYER	103

#pragma pack (push, 1)

// ---------------------------------------------------
//				Client -> Server Packet
// ---------------------------------------------------
struct cs_login_req_packet {
	int size;
	int type;
	char idString[10];
	char pwString[30];
};




// ---------------------------------------------------
//				Server -> Client Packet
// ---------------------------------------------------
enum FAIL_REASON {
	ID = 0,
	PW,
};
struct sc_login_res_packet {
	int size;
	int type;
	bool isSuccess;
	bool failReason;
};

struct sc_put_player_packet {
	int size;
	int type;
	int id;
	int hp;
	int mp;
	int atk;
	int level;
	float xpos;
	float ypos;
	float zpos;
};
#pragma pack (pop)
#pragma once
