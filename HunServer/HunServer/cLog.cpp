#include "stdafx.h"
#include "cLog.h"


cLog::cLog()
{
}


cLog::~cLog()
{
}

void cLog::ErrorDisplay(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
void cLog::ErrorDisplay(char* msg, int error_no)
{
	WCHAR *lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("%s", msg);
	wprintf(L"Error : %s\n", lpMsgBuf);
	LocalFree(lpMsgBuf);
}
void cLog::LogMessage(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
}