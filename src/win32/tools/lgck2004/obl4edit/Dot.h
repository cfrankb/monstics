#ifndef _DOT_H
#define _DOT_H

// Dot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDot 

class CDot 
{
// Construction
public:
	CDot (CDot &dot);
	CDot (int x, int y);
	CDot ();

// Attributes
public:
	CPoint & Point ();

// Operations
public:
	CDot & operator = (CDot & dot);
	BOOL operator == (CDot & dot);

// Implementation
public:
	~CDot();
	int m_nColor;
	int m_nX;
	int m_nY;

protected:
	void Init();
};

/////////////////////////////////////////////////////////////////////////////

#endif