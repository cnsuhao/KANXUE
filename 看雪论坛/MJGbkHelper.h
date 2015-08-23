/*****************************************************************************************
码位分配及顺序
　　GBK 亦采用双字节表示，总体编码范围为 8140-FEFE，首字节在 81-FE 之间，尾字节在 40-FE 之间，剔除 xx7F 一条线。
	总计 23940 个码位，共收入 21886 个汉字和图形符号，其中汉字（包括部首和构件）21003 个，图形符号 883 个。
　　全部编码分为三大部分：  

　　1. 汉字区。包括：
　　a. GB 2312 汉字区。即 GBK/2: B0A1-F7FE。收录 GB 2312 汉字 6763 个，按原顺序排列。
　　b. GB 13000.1 扩充汉字区。包括：
　　(1) GBK/3: 8140-A0FE。收录 GB 13000.1 中的 CJK 汉字 6080 个。
　　(2) GBK/4: AA40-FEA0。收录 CJK 汉字和增补的汉字 8160 个。CJK 汉字在前，按 UCS 代码大小排列；增补的汉字（包括部首和构件）在后，
		按《康熙字典》的页码／字位排列。  

　　2. 图形符号区。包括：
　　a. GB 2312 非汉字符号区。即 GBK/1: A1A1-A9FE。其中除 GB 2312 的符号外，还有 10 个小写罗马数字和 GB 12345 增补的符号。
		计符号 717 个。
　　b. GB 13000.1 扩充非汉字区。即 GBK/5: A840-A9A0。BIG-5 非汉字符号、结构符和“○”排列在此区。计符号 166 个。  

　　3. 用户自定义区：分为(1)(2)(3)三个小区。
　　(1) AAA1-AFFE，码位 564 个。
　　(2) F8A1-FEFE，码位 658 个。
　　(3) A140-A7A0，码位 672 个。
　　第(3)区尽管对用户开放，但限制使用，因为不排除未来在此区域增补新字符的可能性。
******************************************************************************************/

#ifndef __MJ_GBKHELPER_H__
#define __MJ_GBKHELPER_H__

namespace MJ_GBK_HELPER
{
	// 简易检测是否gbk
	#define IS_SIMPLE_GBK(x) ((x) & 0x80)

	// 是否gbk字符
	bool IsGBK(unsigned short ushChar);

	// 是否gb2312字符
	bool IsGB2312(unsigned short ushChar);

	// 把UTF-8转换成Unicode
	void UTF_8ToUnicode(wchar_t &wchar, const char szInString[3]);

	// Unicode转换成UTF-8
	void UnicodeToUTF_8(char szOutString[3], wchar_t wchar);
}

#endif
