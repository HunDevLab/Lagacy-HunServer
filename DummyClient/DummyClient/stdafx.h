// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN    // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define NOMINMAX
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <mutex>

#include "protocol.h"

#include "flatbuffers\flatbuffers.h"

#include "CSPacket_generated.h"
#include "SCPacket_generated.h"





// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
