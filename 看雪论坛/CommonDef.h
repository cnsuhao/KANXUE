#pragma  once
#include<string>

typedef struct Account
{
	HWND MainHWND;
	char AccountBuf[20];
	char PasswordBuf[20];
}Account;

typedef struct ReadBuf
{
	unsigned char* mBuf;
	int mSizeBuf;
}ReadBuf;

typedef struct UserInfo
{
	std::string mUserName;
	std::string mLevel;
	std::string mOnlineHour;
	std::string mNextLevelNeed;
	std::string mLastOnline;
}UserInfo;

#define READBUF_MAXLEN 0x1000000