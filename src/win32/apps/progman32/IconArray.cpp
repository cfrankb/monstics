// IconArray.cpp : implementation file
//

#include "stdafx.h"
#include "progman32.h"
#include "IconArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconArray

CIconArray::CIconArray()
{
    m_nSize=0;
    m_imageList.Create(32,32, ILC_COLOR8|ILC_PALETTE|ILC_MASK, 0, 1);

    ZeroMemory(m_arrIcons, sizeof(m_arrIcons));
}

CIconArray::~CIconArray()
{
}

/////////////////////////////////////////////////////////////////////////////
// CIconArray message handlers

void CIconArray::Serialize(CArchive & ar)
{
    if (ar.IsLoading()) // load
    {
        Forget();

        ar.Read(&m_nSize, 4);
        ar.Read(&m_arrIcons, sizeof(ICON_INFO)*m_nSize);

        int nIcons=0;
        ar.Read(&nIcons, 4);
        if (nIcons)
        {
            m_imageList.Read(&ar);            
        }

        CString str;
        str.Format("ICON COUNT: %d\r\n", m_imageList.GetImageCount());
        OutputDebugString(str);
    }
    else    // save
    {
        ar.Write(&m_nSize,4);
        ar.Write(&m_arrIcons, sizeof(ICON_INFO)*m_nSize);

        int nIcons = m_imageList.GetImageCount();
        if (nIcons)
        {
            ar.Write(&nIcons, 4);
            m_imageList.Write(&ar);    
        }
    }
}

ICON_INFO & CIconArray::operator[] (int i)
{
    return m_arrIcons[i];    
}

int CIconArray::GetSize()
{
    return m_nSize;                            
}

CImageList & CIconArray::GetImageList()
{
    return m_imageList;
}

void CIconArray::RemoveAt(int i)
{

}

int CIconArray::Add(HICON hIcon)
{
    m_imageList.Add(hIcon);
    return m_imageList.GetImageCount() -1;
}

int CIconArray::Add(ICON_INFO & info)
{
    if (m_nSize!=MAX_ICONS)
    {
        memcpy(&m_arrIcons[m_nSize], &info, sizeof(ICON_INFO));
        m_nSize++;
    
        return m_nSize -1;
    }
    else
    {
        return -1;
    }
}

int CIconArray::Add(ICON_INFO & info, HICON hIcon)
{
    info.m_nIconIndex = Add(hIcon);
    return Add(info);
}

void CIconArray::Forget()
{
    while(m_imageList.GetImageCount())
    {
        m_imageList.Remove(0);
    }

    m_nSize=0;
}

HICON CIconArray::GetIcon(int i)
{
    return m_imageList.ExtractIcon(i);
}

BOOL CIconArray::SetIcon(int i, HICON hIcon)
{
    return m_imageList.Replace(i, hIcon);    
}
