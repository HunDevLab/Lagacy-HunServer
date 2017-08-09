#pragma once
class cLog
{
public:
	cLog();
	~cLog();
public:
	static void ErrorDisplay(char* msg);
	static void ErrorDisplay(char* msg, int error_no);

	static void LogMessage(char* msg);
};

