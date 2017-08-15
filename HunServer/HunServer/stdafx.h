// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#pragma comment(lib, "ws2_32.lib")
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
#include "cIocpServer.h"
#include "cLog.h"
#include "cClientInfo.h"
#include "cPlayer.h"
#include "cClientManager.h"
#include "cPacketController.h"



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
