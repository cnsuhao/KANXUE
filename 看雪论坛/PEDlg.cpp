
// PEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "看雪论坛.h"
#include "PEDlg.h"
#include "afxdialogex.h"
#include "windows.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <Crypto/md5.h>
#include "MJGbkcode.h"
#include "MJGbkHelper.h"
#include "CommonDef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// PEDlg 对话框


using namespace CryptoPP;

PEDlg::PEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void PEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(PEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGOUT, &PEDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_LOGIN, &PEDlg::OnBnClickedLogin)
	ON_MESSAGE(WM_Login_Finish, OnLoginThreadFinish) 
END_MESSAGE_MAP()

int PEDlg::mMinites=0;

// PEDlg 消息处理程序

BOOL PEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mMinites=0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void PEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR PEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void PEDlg::OnBnClickedLogout()
{
	static bool flag=1;
	if(flag)
	{
		CRect rect;
		GetWindowRect(&rect);
		SetWindowPos(NULL,rect.left,rect.top,200,160,0);
	}
	else
	{
		CRect rect;
		GetWindowRect(&rect);
		SetWindowPos(NULL,rect.left,rect.top,200,400,0);
	}
	flag=!flag;
}



void CalMD5(char*input,char*output)
{
	MD5 vMD5;
	byte digist[16];
	vMD5.CalculateDigest(digist,(byte*)input,strlen(input));
	vMD5.Update((byte*)input,strlen(input));
	vMD5.Final(digist);
	for(int i=0;i<16;i++)
		sprintf(output+i*2,"%.2x",digist[i]);
}
size_t write_data(void * ptr, size_t size, size_t nmemb, void * stream)
{
	ReadBuf * vPReadBuf=(ReadBuf*)stream;
	memcpy(vPReadBuf->mBuf+vPReadBuf->mSizeBuf,ptr,size*nmemb);
	vPReadBuf->mSizeBuf+=size*nmemb;
	return size*nmemb;
}
std::string URL(const char*s)
{
	std::string ret="";
	char buf[10]={0};
	for(int i=0;s[i];i++)
	{
		sprintf(buf,"%.2X",s[i]&0xff);
		ret+="%";
		ret+=buf;
	}
	return ret;
}
std::string   HttpPostAction(const char* host,struct curl_slist* headers,const char* postDada)
{
	CURL* pCURL=curl_easy_init();
	curl_easy_setopt(pCURL,CURLOPT_URL,host);
	curl_easy_setopt(pCURL,CURLOPT_POSTFIELDS,postDada);

	ReadBuf vReadBuf;
	vReadBuf.mBuf=(unsigned char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	vReadBuf.mSizeBuf=0;
	curl_easy_setopt(pCURL, CURLOPT_WRITEDATA, &vReadBuf);
	curl_easy_setopt(pCURL, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(pCURL,CURLOPT_COOKIEFILE,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_COOKIEJAR,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_HTTPHEADER,headers);
	curl_easy_setopt(pCURL,CURLOPT_HEADER,1);
	curl_easy_perform(pCURL);
	curl_easy_cleanup(pCURL);

	//转码
	char* gb2312buf=(char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	MJ_GBK_HELPER::UTF_8ToGB2312(gb2312buf,(char*)vReadBuf.mBuf,vReadBuf.mSizeBuf);

	std::string responce=gb2312buf;
	GlobalFree(gb2312buf);
	GlobalFree(vReadBuf.mBuf);
	return responce;
}
std::string HttpGetAction(const char* host,struct curl_slist* headers)
{
	std::string response="";
	CURL* pCURL=curl_easy_init();
	curl_easy_setopt(pCURL,CURLOPT_URL,host);

	ReadBuf vReadBuf;
	vReadBuf.mBuf=(unsigned char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	vReadBuf.mSizeBuf=0;
	curl_easy_setopt(pCURL, CURLOPT_WRITEDATA, &vReadBuf);
	curl_easy_setopt(pCURL, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(pCURL,CURLOPT_COOKIEFILE,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_COOKIEJAR,"cookie.txt");
	curl_easy_setopt(pCURL,CURLOPT_HTTPHEADER,headers);
	curl_easy_setopt(pCURL,CURLOPT_HEADER,1);
	curl_easy_perform(pCURL);
	curl_easy_cleanup(pCURL);

	char* gb2312buf=(char*)GlobalAlloc(GMEM_ZEROINIT,READBUF_MAXLEN);
	MJ_GBK_HELPER::UTF_8ToGB2312(gb2312buf,(char*)vReadBuf.mBuf,vReadBuf.mSizeBuf);
	
	response=gb2312buf;
	GlobalFree(gb2312buf);
	GlobalFree(vReadBuf.mBuf);
	return response;
}
std::string FindUserID(std::string response)
{
	std::string ret="";
	int place=response.find("bbuserid=");
	if(std::string::npos!=place)
	{
		for(int i=place+9;i<response.length()&&isdigit(response[i]);i++)
		{
			ret+=response[i];
		}
	}
	return ret;
}
UserInfo FindUserInfo(std::string response)
{
	UserInfo vUserInfo;
	std::string ret="";
	int place=response.find("images/onlineranks/level2.gif");
	if(std::string::npos!=place)
	{
		for(int i=place+36;i<response.length()&&response[i]!='\"';i++)
		{
			ret+=response[i];
		}
		if(ret!="")
		{
			vUserInfo.mLevel=ret.substr(5,2);
			vUserInfo.mOnlineHour=ret.substr(19,7);
			vUserInfo.mNextLevelNeed=ret.substr(38,6);
			place=response.find("class=\"time\"");
			vUserInfo.mLastOnline=response.substr(place+13,8);
		}
	}
	return vUserInfo;
}
void PEDlg:: LoginThread(void* arg)
{
	Account* vAccount=(Account*)arg;
	char cryptPass[33];
	CalMD5(vAccount->PasswordBuf,cryptPass);
	char utf8_buf[200]={0};
	MJ_GBK_HELPER::GB2312ToUTF_8(utf8_buf,vAccount->AccountBuf,-1);
	std::string vPostData="vb_login_username=";
	vPostData+=URL(utf8_buf);
	vPostData+="&cookieuser=1&vb_login_password=&s=&securitytoken=1440078975-67fd000ed2d96b93d5a454553d5a801e513db401&do=login&vb_login_md5password=";
	vPostData+=cryptPass;
	vPostData+="&vb_login_md5password_utf=";
	vPostData+=cryptPass;

	
	
	int ret=curl_global_init(CURL_GLOBAL_ALL);

	curl_slist* headerlist=curl_slist_append(NULL,"Accept-Encoding: deflate");
	//std::string response=HttpGetAction("http://bbs.pediy.com",headerlist);
	std::string response=HttpPostAction("http://bbs.pediy.com/login.php?do=login",headerlist,vPostData.c_str());
	std::string userid=FindUserID(response);
	if(userid!="")
	{
		while(1)
		{
			response=HttpGetAction((std::string("http://bbs.pediy.com/member.php?u=")+userid).c_str(),headerlist);
			UserInfo vUserInfo=FindUserInfo(response);
			::SendMessage(vAccount->MainHWND,WM_Login_Finish,(WPARAM )&vUserInfo,NULL);
			Sleep(60000);
			mMinites++;
		}

	}
	curl_slist_free_all(headerlist);

}
void PEDlg::OnBnClickedLogin()
{
	m_Account.MainHWND=GetSafeHwnd();
	GetDlgItemTextA(IDC_EDIT_ACCOUNT,m_Account.AccountBuf,20);
	GetDlgItemTextA(IDC_EDIT_PASSWORD,m_Account.PasswordBuf,20);
	::CreateThread(0,0,(LPTHREAD_START_ROUTINE)LoginThread,&m_Account,0,0);
}
LRESULT PEDlg::OnLoginThreadFinish(WPARAM wParam, LPARAM lParam)
{
	UserInfo *pUser=(UserInfo*)wParam;
	if(wParam)
	{
		CButton* vLoginButton=(CButton*)GetDlgItem(IDC_LOGIN);
		vLoginButton->EnableWindow(0);
		CButton* vLogoutButton=(CButton*)GetDlgItem(IDC_LOGOUT);
		vLogoutButton->EnableWindow(TRUE);

		CEdit* vAccountEdit=(CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT);
		vAccountEdit->EnableWindow(FALSE);
		CEdit* vPass=(CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
		vPass->EnableWindow(FALSE);

		CStatic* vStaticLevel=(CStatic*)GetDlgItem(IDC_STATIC_LEVEL);
		vStaticLevel->SetWindowTextA(pUser->mLevel.c_str());

		CStatic* vStaticOnlineHour=(CStatic*)GetDlgItem(IDC_STATIC_ONLINE_HOUR);
		vStaticOnlineHour->SetWindowTextA(pUser->mOnlineHour.c_str());

		CStatic* vStaticLastOnline=(CStatic*)GetDlgItem(IDC_STATIC_LAST_TIME);
		vStaticLastOnline->SetWindowTextA(pUser->mLastOnline.c_str());

		CStatic* vStaticNextLevelNeed=(CStatic*)GetDlgItem(IDC_STATIC_NEXT_LEVLE);
		vStaticNextLevelNeed->SetWindowTextA(pUser->mNextLevelNeed.c_str());

		CStatic* vStaticLoginTime=(CStatic*)GetDlgItem(IDC_STATIC_LOGIN_TIME);
		char vMinitesBuf[20]={0};
		sprintf(vMinitesBuf,"%d",mMinites);
		vStaticLoginTime->SetWindowTextA(((std::string)""+vMinitesBuf+"分钟").c_str());
	}
	return 0;
}