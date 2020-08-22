#ifndef _PROTOARRAY_H
#define _PROTOARRAY_H

#include "proto.h"
#include "scriptentry.h"

// ProtoArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtoArray 

class CProtoArray 
{
// Construction
public:
	CProto & GetProto(CScriptEntry & entry);
	void Read (CFile & file);
	CProtoArray();

// Attributes
public:
	int GetSize();
	int GetProtoIndex (const CString & str);

// Operations
public:
	void Add (CProto & proto);
	void Forget();
	void RemoveAt (int n);
	CProto & operator [] (int n);

	void KillProto (int nProto);
	void KillFrameSet (int nFrameSet);

// Implementation
public:
	~CProtoArray();
	void Serialize (CArchive & ar);

private:
	CProto * m_arrProto;
	int m_nMax;
	int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////

#endif