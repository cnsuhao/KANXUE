#include "stdafx.h"
#include "MJGbkcode.h"

namespace MJ_GBK_HELPER
{
	// 把Unicode转换成GB2312
	unsigned int UnicodeToGB2312(char *pszOutString, const wchar_t *pwszInString, unsigned int unInSize)
	{
		if (NULL == pwszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = wcslen(pwszInString);
		}

		unsigned int unOutSize = 0;

		unsigned int i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pszOutString)
		{
			for (i=0; i < unInSize; ++i)
			{
				unsigned short ushCode = (unsigned short)pwszInString[i];
				
				if (IS_SIMPLE_GBK(ushCode))
				{
					*(unsigned short *)(pszOutString+unOutSize) = g_ushGBKUcs[ushCode][1];

					unOutSize += 2;
				}
				else
				{
					pszOutString[unOutSize] = *(char *)&g_ushGBKUcs[ushCode][1];

					unOutSize += 1;
				}
			}
		}
		else
		{
			for (i=0; i < unInSize; ++i)
			{
				if (IS_SIMPLE_GBK(pwszInString[i]))
				{
					unOutSize += 2;
				}
				else
				{
					unOutSize += 1;
				}
			}
		}

		return unOutSize;
	}

	// 把Unicode转换成GB2312
	std::string UnicodeToGB2312(const wchar_t *pwszInString, unsigned int unInSize)
	{
		std::string strOut;
		
		if (NULL == pwszInString || 0 == unInSize)
		{
			return strOut;
		}

		if (-1 == unInSize)
		{
			unInSize = wcslen(pwszInString);
		}

		unsigned int i = 0;

		for (i=0; i < unInSize; ++i)
		{
			unsigned short ushCode = (unsigned short)pwszInString[i];
			
			if (IS_SIMPLE_GBK(ushCode))
			{
				unsigned short ushChar = g_ushGBKUcs[ushCode][1];

				strOut += (ushChar & 0xff);
				strOut += (ushChar >> 8);
			}
			else
			{
				strOut += *(char *)&g_ushGBKUcs[ushCode][1];
			}
		}

		strOut += '\0';
	
		return strOut;
	}

	// 把Unicode转换成GB2312
	unsigned int UnicodeToGB2312_Ex(std::string &strOut, const wchar_t *pwszInString, unsigned int unInSize)
	{
		if (NULL == pwszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = wcslen(pwszInString);
		}

		unsigned int i = 0;

		strOut = "";

		for (i=0; i < unInSize; ++i)
		{
			unsigned short ushCode = (unsigned short)pwszInString[i];
			
			if (IS_SIMPLE_GBK(ushCode))
			{
				unsigned short ushChar = g_ushGBKUcs[ushCode][1];

				strOut += (ushChar & 0xff);
				strOut += (ushChar >> 8);
			}
			else
			{
				strOut += *(char *)&g_ushGBKUcs[ushCode][1];
			}
		}

		strOut += '\0';
	
		return strOut.size();
	}

	// UTF-8转为GB2312
	unsigned int UTF_8ToGB2312(char *pszOutString, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int unOutSize = 0;

		unsigned int i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pszOutString)
		{
			while (i < unInSize)
			{
				if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
				{
					wchar_t wchar;
					UTF_8ToUnicode(wchar, pszInString+i);

					unsigned short ushCode = (unsigned short)wchar;
					
					*(unsigned short *)(pszOutString+unOutSize) = g_ushGBKUcs[ushCode][1];

					unOutSize += 2;

					i += 3;
				}
				else
				{
					pszOutString[unOutSize] = pszInString[i];

					unOutSize++;
					i++;
				}
			}
		}
		else
		{
			while (i < unInSize)
			{
				if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
				{
					unOutSize += 2;

					i += 3;
				}
				else
				{
					unOutSize++;
					i++;
				}
			}
		}

		return unOutSize;
	}

	// UTF-8转为GB2312
	std::string UTF_8ToGB2312(const char *pszInString, unsigned int unInSize)
	{
		std::string strOut;
		
		if (NULL == pszInString || 0 == unInSize)
		{
			return strOut;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		while (i < unInSize)
		{
			if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
			{
				wchar_t wchar;
				UTF_8ToUnicode(wchar, pszInString+i);

				unsigned short ushCode = (unsigned short)wchar;
				
				unsigned short ushChar = g_ushGBKUcs[ushCode][1];

				strOut += (ushChar & 0xff);
				strOut += (ushChar >> 8);

				i += 3;
			}
			else
			{
				strOut += pszInString[i];

				i++;
			}
		}

		strOut += '\0';
	
		return strOut;
	}

	// UTF-8转为GB2312
	unsigned int UTF_8ToGB2312_Ex(std::string &strOut, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		strOut = "";

		while (i < unInSize)
		{
			if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
			{
				wchar_t wchar;
				UTF_8ToUnicode(wchar, pszInString+i);

				unsigned short ushCode = (unsigned short)wchar;
				
				unsigned short ushChar = g_ushGBKUcs[ushCode][1];

				strOut += (ushChar & 0xff);
				strOut += (ushChar >> 8);

				i += 3;
			}
			else
			{
				strOut += pszInString[i];

				i++;
			}
		}

		strOut += '\0';
	
		return strOut.size();
	}


	unsigned int UTF_8ToUnicode_Ex(std::wstring &strOut, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		strOut = L"";

		while (i < unInSize)
		{
			wchar_t outChar = 0;
			if ( (pszInString[i] & 0xE0) == 0xE0)
			{
				UTF_8ToUnicode(outChar, pszInString+i);

				i += 3;
			}
			else if ( (pszInString[i] & 0xC0) == 0xC0)
			{
				outChar = (pszInString[i] & 0x1f) << 6;
				outChar |= (pszInString[i+1] & 0x3f);

				i += 2;
			}
			else
			{
				outChar = (wchar_t)pszInString[i]; 
				i += 1;
			}
			strOut += outChar;
		}

		return strOut.size();
	}

	// GB2312转换成Unicode
	unsigned int Gb2312ToUnicode(wchar_t *pwszOutString, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int unOutSize = 0;

		unsigned int i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pwszOutString)
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
				{
					unsigned short ushCode = *(unsigned short *)(pszInString+i);
					
					pwszOutString[unOutSize++] = g_ushGBKUcs[ushCode][0];

					i += 2;
				}
				else
				{
					pwszOutString[unOutSize++] = pszInString[i];

					i++;
				}
			}
		}
		else
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
				{					
					unOutSize++;

					i += 2;
				}
				else
				{
					unOutSize++;

					i++;
				}
			}
		}

		return unOutSize;
	}

	// GB2312转换成Unicode
	std::wstring Gb2312ToUnicode(const char *pszInString, unsigned int unInSize)
	{
		std::wstring wstrOut;
		
		if (NULL == pszInString || 0 == unInSize)
		{
			return wstrOut;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		while (i < unInSize)
		{
			if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
			{
				unsigned short ushCode = *(unsigned short *)(pszInString+i);
				
				wstrOut += g_ushGBKUcs[ushCode][0];

				i += 2;
			}
			else
			{
				wstrOut += pszInString[i];

				i++;
			}
		}

		wstrOut += L'\0';
	
		return wstrOut;
	}

	// GB2312转换成Unicode
	unsigned int Gb2312ToUnicode_Ex(std::wstring &wstrOut, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		wstrOut = L"";

		while (i < unInSize)
		{
			if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
			{
				unsigned short ushCode = *(unsigned short *)(pszInString+i);
				
				wstrOut += g_ushGBKUcs[ushCode][0];

				i += 2;
			}
			else
			{
				wstrOut += pszInString[i];

				i++;
			}
		}

		//wstrOut += L'\0';
	
		return wstrOut.size();
	}

	// GB2312转为UTF-8
	unsigned int GB2312ToUTF_8(char *pszOutString, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int unOutSize = 0;

		unsigned int i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pszOutString)
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
				{
					unsigned short ushCode = *(unsigned short *)(pszInString+i);
					
					wchar_t wchar = g_ushGBKUcs[ushCode][0];

					UnicodeToUTF_8(pszOutString+unOutSize, wchar);

					unOutSize += 3;
					i += 2;
				}
				else
				{
					pszOutString[unOutSize++] = pszInString[i];

					i++;
				}
			}
		}
		else
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
				{
					unOutSize += 3;
					i += 2;
				}
				else
				{
					unOutSize++;
					i++;
				}
			}
		}

		return unOutSize;
	}


	// GB2312转为UTF-8
	std::string GB2312ToUTF_8(const char *pszInString, unsigned int unInSize)
	{
		std::string strOut;
		
		if (NULL == pszInString || 0 == unInSize)
		{
			return strOut;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		while (i < unInSize)
		{
			if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
			{
				unsigned short ushCode = *(unsigned short *)(pszInString+i);
				
				wchar_t wchar = g_ushGBKUcs[ushCode][0];

				char str[3];

				UnicodeToUTF_8(str, wchar);

				strOut += str[0];
				strOut += str[1];
				strOut += str[2];

				i += 2;
			}
			else
			{
				strOut += pszInString[i];

				i++;
			}
		}

		return strOut;
	}

	// GB2312转为UTF-8
	unsigned int GB2312ToUTF_8_Ex(std::string &strOut, const char *pszInString, unsigned int unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		unsigned int i = 0;

		strOut = "";

		while (i < unInSize)
		{
			if (i < unInSize-1 && IsGBK(*(unsigned short *)&pszInString[i]))
			{
				unsigned short ushCode = *(unsigned short *)(pszInString+i);
				
				wchar_t wchar = g_ushGBKUcs[ushCode][0];

				char str[3];

				UnicodeToUTF_8(str, wchar);

				strOut += str[0];
				strOut += str[1];
				strOut += str[2];

				i += 2;
			}
			else
			{
				strOut += pszInString[i];

				i++;
			}
		}

		strOut += '\0';

		return strOut.size();
	}
    
    int DecodeUtfCodeTwoChar(unsigned char a, unsigned char b)
    {
        int ret = 0;
        int bb = (b&0x3f);
        int aa = (a&0x1f)<<6;
        ret = bb|aa;
        return ret;
    }
    
    int DecodeUtfCodeThreeChar(unsigned char a, unsigned char b, unsigned char c)
    {
        int ret = 0;
        int cc = (c&0x3f);
        int bb = (b&0x3f)<<6;
        int aa = (a&0xf)<<12;
        ret = cc|bb|aa;
        return ret;
    }
    
    int DecodeUtfCodeFourChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d)
    {
        int ret = 0;
        int dd = (d&0x3f);
        int cc = (c&0x3f)<<6;
        int bb = (b&0x3f)<<12;
        int aa = (a&0x7)<<18;
        ret = dd|cc|bb|aa;
        return ret;
    }
    
    int DecodeUtfCodeFiveChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d, unsigned char e)
    {
        int ret = 0;
        int ee = (e&0x3f);
        int dd = (d&0x3f)<<6;
        int cc = (c&0x3f)<<12;
        int bb = (b&0x3f)<<18;
        int aa = (a&0x3)<<24;
        ret = ee|dd|cc|bb|aa;
        return ret;
    }
    
    int DecodeUtfCodeSixChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d, unsigned char e, unsigned char f)
    {
        int ret = 0;
        int ff = (f&0x3f);
        int ee = (e&0x3f)<<6;
        int dd = (d&0x3f)<<12;
        int cc = (c&0x3f)<<18;
        int bb = (b&0x3f)<<24;
        int aa = (a&0x1)<<30;
        ret = ff|ee|dd|cc|bb|aa;
        return ret;
    }
    
    bool IsEmoji(int codePoint)
    {
        return
        ((codePoint >= 0x1f000) && (codePoint <= 0x1f6f0))
        ||
        ((codePoint >= 0x2000) && (codePoint <= 0x2940))
        ||
        ((codePoint >= 0xE000) && (codePoint <= 0xE4FF));
    }
    
    
    std::string FilterEmoji(std::string str)
    {
        //test
        //char test[] = {'t','1'};
        //char test[] = {'t','2',0xc1,0x81};
        //char test[] = {'t','3',0xe1,0x81,0x81};
        //char test[] = {'t','4',0xf1,0x81,0x81,0x81};
        //char test[] = {'t','5',0xf9,0x81,0x81,0x81,0x81};
        //char test[] = {'t','6',0xfd,0x81,0x81,0x81,0x81,0x81};
        //string testStr(test,0,8);
        //str = testStr;
        //test end
        int length = str.length();
        char target[128] = {0};//jonas add  YunYingBranch
        
        //memset(target, 0, length);//jonas del  YunYingBranch
        int targetId=0;
        const char * source = str.c_str();
        
        for(int i = 0; i < length; i++)
        {
        	if(targetId >= 128)
        	{
        		break;//jonas add  YunYingBranch
        	}
            unsigned char tempChar = source[i]&0xff;
            
            if(tempChar >= 0 && tempChar < 0xc0)
            {
                target[targetId++] = source[i];
            }else if(tempChar >= 0xc0 && tempChar < 0xe0)
            {
                int unicode = DecodeUtfCodeTwoChar(source[i],source[i+1]);
                if(IsEmoji(unicode))
                {
                    i += 1;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xe0 && tempChar < 0xf0)
            {
                int unicode = (i+2 <= length) ? DecodeUtfCodeThreeChar(source[i],source[i+1],source[i+2]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 2;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xf0 && tempChar < 0xf8)
            {
                int unicode = (i+3 <= length) ? DecodeUtfCodeFourChar(source[i],source[i+1],source[i+2],source[i+3]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 3;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xf8 && tempChar < 0xfc)
            {
                int unicode = (i+4 <= length) ? DecodeUtfCodeFiveChar(source[i],source[i+1],source[i+2],source[i+3],source[i+4]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 4;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xfc && tempChar <= 0xff)
            {
                int unicode = (i+5 <= length) ? DecodeUtfCodeSixChar(source[i],source[i+1],source[i+2],source[i+3],source[i+4],source[i+5]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 5;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }
        }
        std::string ret(target,0,targetId);
        return ret;
        
    }
}