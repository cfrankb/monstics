// DotArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDotArray 
#ifndef _DOTARRAY_H
#define _DOTARRAY_H

#include "dot.h"

class CDotArray 
{
// Construction
public:
	CDotArray();

// Attributes
public:
	int GetSize() { return m_nSize;}

// Operations
public:
	CDot & operator[](int n) {return m_arrDots[n];}
	int Add (CDot & pDot);
	void Forget();

// Implementation
public:
	~CDotArray();

protected:
	CDot * m_arrDots;
	int m_nMax;
	int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////

#endif