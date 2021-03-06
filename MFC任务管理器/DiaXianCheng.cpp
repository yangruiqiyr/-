// DiaXianCheng.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC任务管理器.h"
#include "DiaXianCheng.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CDiaXianCheng 对话框

IMPLEMENT_DYNAMIC(CDiaXianCheng, CDialogEx)

CDiaXianCheng::CDiaXianCheng(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGXianCheng, pParent)
{

}

CDiaXianCheng::~CDiaXianCheng()
{
}

void CDiaXianCheng::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BOOL CDiaXianCheng::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD dwOldStyle = m_ListCtrl.GetExtendedStyle();
	m_ListCtrl.SetExtendedStyle(
		dwOldStyle | LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES |
		LVS_EX_CHECKBOXES
	);
	CRect rc;
	m_ListCtrl.GetClientRect(rc);
	int nWidth = rc.Width();
	m_ListCtrl.InsertColumn(0, L"线程ID", 0, nWidth / 3);
	m_ListCtrl.InsertColumn(1, L"所属进程", 0, nWidth / 3);
	m_ListCtrl.InsertColumn(2, L"线程在内核中分配的优先级", 0, nWidth / 3);
	BianLi();

	return TRUE;
}

BOOL CDiaXianCheng::BianLi()
{
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		printf("快照error!\n");
		return false;
	}
	// 2. 开始遍历进程
	THREADENTRY32 ti = { sizeof(THREADENTRY32) };
	BOOL bRet = Thread32First(hTool32, &ti);
	if (!bRet)
	{
		printf("Thread32First error!\n");
		return false;
	}
	int i = 0;
	do
	{
		//if (ti.th32OwnerProcessID == dwPID)
		{
			m_ListCtrl.UpdateWindow();
			CString str;
			str.Format(_T("%ld"), ti.th32ThreadID);
			m_ListCtrl.InsertItem(i, str);
			str.Format(_T("%ld"), ti.th32OwnerProcessID);
			m_ListCtrl.SetItemText(i, 1, str);
			str.Format(_T("%ld"), ti.tpBasePri);
			m_ListCtrl.SetItemText(i, 2, str);
			i++;
		}
	} while (Thread32Next(hTool32, &ti));
	return true;
}


BEGIN_MESSAGE_MAP(CDiaXianCheng, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaXianCheng::OnBnClickedkill)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDiaXianCheng::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDiaXianCheng::OnBnClickedGuaqi)
	ON_BN_CLICKED(IDC_BUTTON2, &CDiaXianCheng::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDiaXianCheng 消息处理程序


void CDiaXianCheng::OnBnClickedkill()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD n;
	n = _wtoi(temp2);
	HANDLE hwnd = OpenThread(PROCESS_TERMINATE, FALSE, n);
	TerminateProcess(hwnd, 0);
}


void CDiaXianCheng::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int temp = pNMItemActivate->iItem;
	temp2 = m_ListCtrl.GetItemText(temp, 1);
}


void CDiaXianCheng::OnBnClickedGuaqi()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD n;
	n = _wtoi(temp2);
	HANDLE hwnd = OpenThread(PROCESS_TERMINATE, FALSE, n);
	SuspendThread(hwnd);
}


void CDiaXianCheng::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD n;
	n = _wtoi(temp2);
	HANDLE hwnd = OpenThread(PROCESS_TERMINATE, FALSE, n);
	ResumeThread(hwnd);
}
