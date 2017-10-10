// HunServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	cIocpManager* server = new cIocpManager;
	server->Begin();

	while (true)
	{

	}
}

