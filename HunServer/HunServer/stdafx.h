// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"
#pragma comment(lib, "ws2_32.lib")
#define NOMINMAX
#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <process.h>
#include <mutex>
#include <chrono>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include "Protocol.h"
#include "cSingleton.h"
#include "CommonDef.h"
#include "cIocpManager.h"
#include "cLog.h"
#include "cClientInfo.h"
#include "cPlayer.h"
#include "cClientManager.h"
#include "cPacketController.h"
#include "cNetworkSession.h"

static std::mutex gLock;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
