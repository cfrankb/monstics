// IconArray.h : header file
//

#define MAX_ICONS 64

typedef struct
{
    char m_szTitle[32];
    char m_szPath[_MAX_PATH];
    char m_szDir[_MAX_DIR];
    BOOL m_bMinimize;
    WORD m_nVirtualKeyCode;
    WORD m_nModifiers;
    int m_nIconIndex;
} ICON_INFO;

/////////////////////////////////////////////////////////////////////////////
// CIconArray window

class CIconArray
{
// Construction
public:
	BOOL SetIcon(int i, HICON hIcon);
	HICON GetIcon(int i);
	void Forget();
	int Add(ICON_INFO & info, HICON hIcon);
	int Add(ICON_INFO & info);
	int Add(HICON hIcon);
	void RemoveAt(int i);
	CImageList & GetImageList();
	int GetSize();
	ICON_INFO & operator[] (int i);
	void Serialize(CArchive & ar);
	CIconArray();

// Attributes
public:

// Operations
public:

// Overrides

// Implementation
public:
	~CIconArray();

protected:
    ICON_INFO m_arrIcons[MAX_ICONS];
    CImageList m_imageList; 
    int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////
