
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
	
	YLR::YSQLiteDataBase d1;
	d1.setFilePath("D:/SQLiteDB.db");

	if(d1.connectDataBase())
	{
		AfxMessageBox(_T("OK"));
		const YLR::YDataTable *table = d1.executeSqlReturnDt("SELECT * FROM tb_test");
		if(table != NULL)
		{
			for(int i = 0;i < table->getRowCount();i++)
			{
				CString str = _T("");;
				if(table->getData(i,0)->isNull())
				{
					str += "NULL";
				}
				else
				{
					CString ss;
					ss.Format(_T("%d"),table->getData(i,0)->toInt());
					str += ss;
				}

				if(table->getData(i,1)->isNull())
				{
					str += ",NULL";
				}
				else
				{
					YLR::YData data = YLR::YData(*table->getData(i,1));
					
					str += _T(",") + CString(data.toString()->c_str());
				}

				if(table->getData(i,2)->isNull())
				{
					str += ",NULL";
				}
				else
				{
					YLR::YData data = YLR::YData(*table->getData(i,2));
					
					str += _T(",") + CString(data.toString()->c_str());
				}

				if(table->getData(i,3)->isNull())
				{
					str += ",NULL";
				}
				else
				{
					CString ss;
					ss.Format(_T(",%f"),table->getData(i,3)->toDouble());
					str += ss;
				}

				AfxMessageBox(str);
			}
			
			YLR::YDataInterface::releaseDataTable(table);
		}
		//d1.beginTransaction();
		d1.executeSqlWithOutDt("INSERT INTO tb_test (text1) VALUES ('你好')");
		//d1.rollbackTransaction();
		d1.disconnectDataBase();
	}
}
