/////////////////////////////////////////////////////////////////////////////
// CSS3Frame 

#ifndef _SS3FRAME_H
#define _SS3FRAME_H

#define IMG2MAP_RATIO (64)
#define SS3FRAME_VERSION 0x400
#define MODE_ZLIB_ALPHA -1
#define MAX_UNDO 10

// IMPORTANT: This class must be inherited from CObject so
// we can use CObArray.

// SS3Frame.h : header file
//

class CSS3Frame : public CObject
{

// Construction
public:
	void Set (int nLen, int nHei);
	void CopyImage (CSS3Frame * src);
	void Shrink();
	CSS3Frame(CSS3Frame* src, BOOL bClear=FALSE);
	CSS3Frame(int p_nLen, int p_nHei, char *pBitmap=NULL);
    CSS3Frame();

// Attributes
public:
	BOOL CanRedo ();
	BOOL CanUndo ();
	BOOL IsValid ();
	BOOL IsPacked ();
	void SetPacked ();

// Operations
public:
	CSS3Frame & operator = (CSS3Frame &src);
	void RainbowEffect ();
	void RainbowEffectExclude (UCHAR nColor);
	void InverseColor ();
	void Enlarge2x();
	void Resize (int nLen, int nHei);
	void Rotate90();
	void FloodFill (int x, int y, UCHAR oldColor, UCHAR newColor);
	void Erase();
	void ShiftRight();
	void ShiftLeft();
	void ShiftDown();
	void ShiftUP();
	void FlipVert();
	void FlipHorz();
	void NewImage(char *pImage);
	void Forget();
	void Replace (CSS3Frame *src);
	BOOL Redo();
	BOOL Undo();
	BOOL Dirty();
	UCHAR * Point (int x, int y);
	void SpreadVert ();
	void SpreadHorz ();

// Implementation
public:
	~CSS3Frame(); 
	void Serialize(CArchive& ar, int nMode);
	void Read (CFile & file, int nMode);
	void Write (CFile & file);

	int m_nLen;
	int m_nHei;
    char *m_pBitmap;

    int m_bMapped;
    char *m_pMap;

private:
	void Init();

	BOOL m_bPacked;

	CObArray m_arrUndo;
	CObArray m_arrRedo;
};

/////////////////////////////////////////////////////////////////////////////

#endif