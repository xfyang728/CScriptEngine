#pragma once
class Code {
	enum CpuType { X86, X64 };
	int pageSize = 0x10000;
public:
	int* m_MemBase;

public:
	Code();
	~Code();
	void initMemory();
	void AddCode(char buff[]);
	//virtual void formatCode();
};