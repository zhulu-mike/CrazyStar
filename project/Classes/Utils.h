#ifndef _UTILS_H_
#define _UTILS_H_

#define RETURN_NONE_IF(cond) if (cond) return
#define RETURN_VALUE_IF(cond, val) if (cond) return val

inline int randLimit(int nMin, int nMax)
{
    assert(nMax != nMin);

    //include max value and min value
    return (rand() % (nMax - nMin + 1) + nMin);
}

/*
 *小字符串格式化
 */
struct StringFormatHelper
{
    StringFormatHelper()
    {
        memset(m_szBuf, 0, sizeof(m_szBuf));
    }

    char* operator ()(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        vsprintf(m_szBuf, format, args);
        va_end(args);

        return m_szBuf;
    }

    char m_szBuf[256];
};

inline std::string transTimeStr(int time)
{
    char buf[64] = {0};
	int m = time / 60;
	int s = time % 60 ;

	sprintf(buf,"%02d:%02d", m, s);
    return std::string(buf);
}


#endif

