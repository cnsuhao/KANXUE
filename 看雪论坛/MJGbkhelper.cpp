#include"stdafx.h"
#include "MJGbkhelper.h"

namespace MJ_GBK_HELPER
{
	// 是否gbk字符
	bool IsGBK(unsigned short ushChar)
	{
		unsigned char uc1 = ushChar & 0xff;
		unsigned char uc2 = (ushChar >> 8);
		
		if (IS_SIMPLE_GBK(uc1)) // 先快速判断一下
	    {
	        // GBK编码范围是：首(低)字节从0x81到0xFE，尾(高)字节从0x40到0xFE，同时不包括0x7F
	        if (uc1 >= 0x81 && uc1 <= 0xfe && uc2 >= 0x40 && uc2 <= 0xfe && uc2 != 0x7f)
	        {
	            return true;
	        }
	    }
		else
	    {
	        if (!(uc1>='a' &&  uc1 <='z' ||  uc1>='A' &&  uc1<='Z'))
	        {
	            return false;
	        }
	    }
		
	    return false;
	}

	// 是否gb2312字符
	bool IsGB2312(unsigned short ushChar)
	{
		unsigned char uc1 = ushChar & 0xff;
		unsigned char uc2 = (ushChar >> 8);
		
		if (IS_SIMPLE_GBK(uc1)) // 先快速判断一下
	    {
	        // GBK编码范围是：首(低)字节从0x81到0xFE，尾(高)字节从0x40到0xFE，同时不包括0x7F
	        if (uc1 >= 0xb0 && uc1 <= 0xf7 && uc2 >= 0xa1 && uc2 <= 0xfe && uc2 != 0x7f)
	        {
	            return true;
	        }
	    }
		
	    return false;
	}

	// 把UTF-8转换成Unicode
	void UTF_8ToUnicode(wchar_t &wchar, const char szInString[3])
	{
		if (0 != szInString)
		{
			// 确保大于2字节情况下的wchar高位清0
			wchar = 0;
			
			char *pChars = (char *)&wchar;

			pChars[1] = ((szInString[0] & 0x0F) << 4) + ((szInString[1] >> 2) & 0x0F);
			pChars[0] = ((szInString[1] & 0x03) << 6) + (szInString[2] & 0x3F);
		}
	}

	// Unicode转换成UTF-8
	void UnicodeToUTF_8(char szOutString[3], wchar_t wchar)
	{
		if (0 != szOutString)
		{
			char *pChars = (char *)&wchar;

			szOutString[0] = (0xE0 | ((pChars[1] & 0xF0) >> 4));
			szOutString[1] = (0x80 | ((pChars[1] & 0x0F) << 2)) + ((pChars[0] & 0xC0) >> 6);
			szOutString[2] = (0x80 | (pChars[0] & 0x3F));
		}
	}
}
