// ProtoPage4.h : header file
//

#include "scr4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CProtoPage4 dialog

class CProtoPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProtoPage4)

// Construction
public:
	CProtoPage4();
	~CProtoPage4();

// Dialog Data
	//{{AFX_DATA(CProtoPage4)
	enum { IDD = IDD_PROTOPAGE4 };
	int		m_nAutoBullet;
	int		m_nAutoProto;
	int		m_nAutoProtoTime;
	int		m_nAutoBulletTime;
	int		m_nAutoSound;
	int		m_nAutoSoundTime;
	int		m_nAutoTriggerTime;
	BOOL	m_bAutoTrigger;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProtoPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CScr4editDoc *m_pDoc;
	
protected:
	// Generated message map functions
	//{{AFX_MSG(CProtoPage4)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
