// Stack.h : header file
//

#ifndef _STACK_H
#define _STACK_H

#define MAXSTACK 400

/////////////////////////////////////////////////////////////////////////////
// CStack window

class CStack 
{
// Construction
public:
	void push(int n);
	int pop();
	void Forget();
	void Init();
	int GetSize();
	CStack();

// Attributes
public:

// Operations
public:

// Implementation
public:
	~CStack();

protected:
	int m_arrData[MAXSTACK];
	int m_nSize;
};

#endif 

/////////////////////////////////////////////////////////////////////////////
