#include "Code.h"
#include <malloc.h> 
#include <string.h>

Code::Code()
{
	m_MemBase = nullptr;
	initMemory();
}

Code::~Code()
{
	free(m_MemBase);
	m_MemBase = nullptr;
}

void Code::initMemory() {
	m_MemBase = (int*)malloc(pageSize);
}

void Code::AddCode(char* buf)
{
	char buff[] =
	{
		0x55,                       //push        ebp
		0x8B, 0xEC,				 //mov         ebp,esp
		0x8B, 0x45, 0x10,			 //mov         eax,dword ptr[ebp + 10h]
		0x03, 0x45, 0x0C,			 //add         eax,dword ptr[ebp + 0Ch]
		0x03, 0x45, 0x08,			 //add         eax,dword ptr[ebp + 8]
		0x5D,						 //pop         ebp
		0xC3						 //ret
	};
	int size = sizeof(buff);
	memcpy(m_MemBase, buff, size);
}
