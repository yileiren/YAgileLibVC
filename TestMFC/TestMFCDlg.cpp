
// TestMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMFC.h"
#include "TestMFCDlg.h"
#include "afxdialogex.h"

#include "../include/JsonCpp/json.h"
#include "../include/YDataType/YData.h"
#include "../include/YDataBase/YColumn.h"

#include "../include/YSerialPort/YSerialPort.h"

#include "../include/YDataBase/YSqlServerDataBase.h"
#include "../include/YDataBase/YSQLiteDataBase.h"
#include "../include/YDataBase/YAccessDataBase.h"

#include "../include/YCrypto/YMD5Encrypt.h"

#include "../include/YSystem/YMachineInfo.h"

#include "../include/YNetwork/YConnection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMFCDlg 对话框




CTestMFCDlg::CTestMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestMFCDlg 消息处理程序

BOOL CTestMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	if(!AfxOleInit())//这就是初始化COM库
	{
		AfxMessageBox(_T("OLE初始化出错!"));
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestMFCDlg::OnBnClickedOk()
{
	//WORD wVersionRequested = MAKEWORD(1,1);
	//WSADATA wsaData;
	//int err = WSAStartup(wVersionRequested,&wsaData);

	//SOCKET s = socket(AF_INET,SOCK_STREAM,0);
	//if(YLR::YNetWork::YConnection::setRcvTimeOut(s,300))
	//{
	//	int t = YLR::YNetWork::YConnection::getRcvTimeOut(s);

	//	CString str;
	//	str.Format(_T("%d"),t);
	//	AfxMessageBox(str);
	//}
	//else
	//	AfxMessageBox(_T("error"));

	YLR::YDataType::YByteType * f = new YLR::YDataType::YByteType();
	f->setSize(50);
	f->setSize(100);
	delete f;
}
