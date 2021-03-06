#pragma once
#include "afxcmn.h"


// CDiaCpu 对话框

class CDiaCpu : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaCpu)

public:
	CDiaCpu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiaCpu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGCPU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	CListCtrl m_Memory;
	CListCtrl m_Cpu;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
