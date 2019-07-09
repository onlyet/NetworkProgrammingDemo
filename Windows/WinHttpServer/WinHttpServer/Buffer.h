#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <string>

class Buffer
{
public:
    Buffer();
    virtual ~Buffer();

    void clear();
    UINT remove(UINT nSize);
    UINT read(PBYTE pData, UINT nSize);
    BOOL write(PBYTE pData, UINT nSize);
    BOOL write(const std::string& s);
    int scan(PBYTE pScan, UINT nPos);
    BOOL insert(PBYTE pData, UINT nSize);
    BOOL insert(const std::string& s);
    void copy(Buffer& buf);
    PBYTE getBuffer(UINT nPos = 0);
    void writeFile(const std::string& fileName);

    //数据大小
    UINT getBufferLen();

protected:
    UINT reallocateBuffer(UINT nSize);
    UINT deallocateBuffer(UINT nSize);
    //占用内存大小
    UINT getMemSize();

protected:
    PBYTE       m_pBegin;   //缓冲区头部位置
    PBYTE       m_pEnd;     //缓冲区尾部位置
    UINT        m_nSize;    //Buffer占用内存大小
};

#endif // !__BUFFER_H__


