// lgckcmd.h : header file
//

#ifndef _LGCKCMD_H
#define _LGCKCMD_H

/////////////////////////////////////////////////////////////////////////////
// CLGCKCmd window

class CLgckCmd 
{
// Construction
public:
	void Read(CFile &file);
	CLgckCmd();

// Attributes
public:

// Operations
public:
	void Init();
	void Write (CFile & file);
	void operator =(CLgckCmd & cmd);

// Implementation
public:
	~CLgckCmd();

	int m_nArgs;
	int m_nLevel;
	int m_arrArgs[4];

	int m_nOffset;
};

#endif

/////////////////////////////////////////////////////////////////////////////
