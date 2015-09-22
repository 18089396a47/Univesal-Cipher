// Universal Cipher mfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Universal Cipher mfc.h"
#include "Universal Cipher mfcDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUniversalCiphermfcDlg dialog




CUniversalCiphermfcDlg::CUniversalCiphermfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUniversalCiphermfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUniversalCiphermfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, progressVar);
	DDX_Control(pDX, IDC_RADIO1, radioUseFiles);
	DDX_Control(pDX, IDC_RADIO2, radioUseConsol);
	DDX_Control(pDX, IDC_RADIO3, radioNumber);
	DDX_Control(pDX, IDC_RADIO4, radioText);
	DDX_Control(pDX, IDC_RADIO5, radioExpanded);
	DDX_Control(pDX, IDC_EDIT1, editLog);
	DDX_Control(pDX, IDC_CHECK1, checkCheckCipher);
	DDX_Control(pDX, IDC_EDIT2, editConsolInput);
	DDX_Control(pDX, IDC_EDIT3, editConsolOutput);
	DDX_Control(pDX, IDC_EDIT4, editFileInput);
	DDX_Control(pDX, IDC_EDIT5, editFileOutput);
	DDX_Control(pDX, IDC_EDIT6, editKey);
	DDX_Control(pDX, IDC_CHECK3, checkRandKey);
	DDX_Control(pDX, IDC_CHECK4, checkUseKey);
	DDX_Control(pDX, IDC_CHECK2, checkSafeCipher);
}

BEGIN_MESSAGE_MAP(CUniversalCiphermfcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO1, &CUniversalCiphermfcDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CUniversalCiphermfcDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CUniversalCiphermfcDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CUniversalCiphermfcDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CUniversalCiphermfcDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_CHECK1, &CUniversalCiphermfcDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CUniversalCiphermfcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUniversalCiphermfcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUniversalCiphermfcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUniversalCiphermfcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK3, &CUniversalCiphermfcDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CUniversalCiphermfcDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUniversalCiphermfcDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CUniversalCiphermfcDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_CHECK2, &CUniversalCiphermfcDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CUniversalCiphermfcDlg message handlers

BOOL CUniversalCiphermfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	progressVar.SetRange32(0,100);
	radioUseConsol.SetCheck(1);
	radioText.SetCheck(1);
	editLog.ShowWindow(1);
	editConsolInput.ShowWindow(0);
	editConsolOutput.ShowWindow(0);
	checkRandKey.SetCheck(1);
	checkUseKey.SetCheck(1);
	OnBnClickedRadio2();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

struct ThreadParam
{
	LPVOID progressVar;
	LPVOID hThread;
	LPVOID percent;
	ThreadParam(LPVOID _progressVar,LPVOID _hThread,LPVOID _percent):
		progressVar(_progressVar),hThread(_hThread),percent(_percent){}
};

void progress(LPVOID progressVar)
{
	Sleep(1000);
	(*(CProgressCtrl*)progressVar).SetPos(0);
	(*(CProgressCtrl*)progressVar).ShowWindow(0);
}

void endCipher(ThreadParam param)
{
	(*(CProgressCtrl*)param.progressVar).SetPos(*(int*)param.percent);
	(*(HANDLE*)param.hThread)=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)progress,param.progressVar,NULL,NULL);
}

void startCipher(ThreadParam param)
{
	(*(CProgressCtrl*)param.progressVar).ShowWindow(1);
}

void CUniversalCiphermfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUniversalCiphermfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUniversalCiphermfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUniversalCiphermfcDlg::OnBnClickedRadio1()
{
	prop.setInputProp(FILEINPUT);
	CString log="Enter Names Of Files";
	editLog.SetWindowTextA(log);
	editConsolInput.ShowWindow(0);
	editConsolOutput.ShowWindow(0);
	editFileInput.ShowWindow(1);
	editFileOutput.ShowWindow(1);
}

void CUniversalCiphermfcDlg::OnBnClickedRadio2()
{
	prop.setInputProp(CONSOLINPUT);
	CString log="Enter Text";
	editLog.SetWindowTextA(log);
	editConsolInput.ShowWindow(1);
	editConsolOutput.ShowWindow(1);
	editFileInput.ShowWindow(0);
	editFileOutput.ShowWindow(0);
}

void CUniversalCiphermfcDlg::OnBnClickedRadio3()
{
	prop.setCipherProp(NUMBER);
	CString log="Accepted simbols:\r\n0123456789";
	editLog.SetWindowTextA(log);
}

void CUniversalCiphermfcDlg::OnBnClickedRadio4()
{
	prop.setCipherProp(SYMBOL);
	CString log="Accepted simbols:\r\n!\"#%&'()*+,-./0123456789:;<=>?@";
	log+="ABCDEFGHIJKLMNOPQRSTUVWXYZ[]\\^_abcdefghijklmnopqrstuvwxyz";
	editLog.SetWindowTextA(log);
}

void CUniversalCiphermfcDlg::OnBnClickedRadio5()
{
	prop.setCipherProp(EXPANDED);
	CString log="All simbols accepted";
	editLog.SetWindowTextA(log);
}

void CUniversalCiphermfcDlg::OnBnClickedCheck1()
{
	prop.setUseCheck(!prop.getUseCheck());
	if (checkCheckCipher.GetCheck())
		editLog.SetWindowTextA(_T("Check Enabled"));
	else
		editLog.SetWindowTextA(_T("Check Disabled"));
}

void CUniversalCiphermfcDlg::OnBnClickedButton1()
{
	ThreadParam param(&progressVar,&hThread,&percent);
	startCipher(param);
	CString input,output,keyStr;
	string initialStr,finalStr,key;
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileInput.GetWindowTextA(input);
		ifstream in(input);
		if (in.bad() || in.fail())
		{
			editLog.SetWindowTextA(_T("File Error"));
			percent=5;
			endCipher(param);
			return;
		}
		string buff;
		while (getline(in,buff))
			initialStr+=buff+'\n';
		initialStr.erase(initialStr.end()-1);
		int len=initialStr.length();
		for (int i=0;i<len;i++)
			output+=initialStr[i];
	}
	else
	{
		editConsolInput.GetWindowTextA(input);
		initialStr=input;
		int pos=initialStr.find('\r');
		while (pos!=-1)
		{
			initialStr.erase(pos,1);
			pos=initialStr.find('\r');
		}
	}
	editKey.GetWindowTextA(keyStr);
	key=keyStr;
	Cipher c;
	int result;
	if (prop.getSafeCipher())
		result=c.safeCipher(initialStr,finalStr,prop.getCipherProp());
	else
		result=c.cipher(initialStr,finalStr,key,prop.getCipherProp(),prop.getRandKey(),prop.getUseKey());
	switch (result)
	{
	case OK:
		editLog.SetWindowTextA(_T("All's OK"));
		percent=100;
		break;
	case ERRORKEY:
		editLog.SetWindowTextA(_T("Bad Key"));
		percent=10;
		endCipher(param);
		return;
	case ERRORSHUFFLE:
		editLog.SetWindowTextA(_T("Shuffle Error"));
		percent=15;
		endCipher(param);
		return;
	case ERRORTYPE:
		editLog.SetWindowTextA(_T("Type Error"));
		percent=20;
		endCipher(param);
		return;
	}
	keyStr.SetString(_T(""));
	int len=key.length();
	for (int i=0;i<len;i++)
		keyStr+=key[i];
	if (prop.getUseKey())
		editKey.SetWindowTextA(keyStr);
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileOutput.GetWindowTextA(output);
		ofstream out(output);
		if (out.bad() || out.fail())
		{
			editLog.SetWindowTextA(_T("File Error"));
			percent=95;
			endCipher(param);
			return;
		}
		out<<finalStr;
	}
	else
	{
		int pos=finalStr.find('\n');
		while (pos!=-1)
		{
			finalStr.insert(pos,"\r");
			pos=finalStr.find('\n',pos+2);
		}
		len=finalStr.length();
		for (int i=0;i<len;i++)
			output+=finalStr[i];
		editConsolOutput.SetWindowTextA(output);
	}
	endCipher(param);
}

void CUniversalCiphermfcDlg::OnBnClickedButton2()
{
	ThreadParam param(&progressVar,&hThread,&percent);
	startCipher(param);
	CString input,output,keyStr;
	string initialStr,finalStr,key;
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileInput.GetWindowTextA(input);
		ifstream in(input);
		if (in.bad() || in.fail())
		{
			editLog.SetWindowTextA(_T("File Error"));
			percent=5;
			endCipher(param);
			return;
		}
		string buff;
		while (getline(in,buff))
			initialStr+=buff+'\n';
		initialStr.erase(initialStr.end()-1);
		int len=initialStr.length();
		for (int i=0;i<len;i++)
			output+=initialStr[i];
	}
	else
	{
		editConsolInput.GetWindowTextA(input);
		initialStr=input;
		int pos=initialStr.find('\r');
		while (pos!=-1)
		{
			initialStr.erase(pos,1);
			pos=initialStr.find('\r');
		}
	}
	editKey.GetWindowTextA(keyStr);
	key=keyStr;
	Cipher c;
	int result;
	if (prop.getSafeCipher())
		result=c.safeDecipher(initialStr,finalStr,prop.getCipherProp());
	else
		result=c.decipher(initialStr,finalStr,key,prop.getCipherProp(),prop.getUseKey());
	switch (result)
	{
	case OK:
		editLog.SetWindowTextA(_T("All's OK"));
		percent=100;
		break;
	case ERRORKEY:
		editLog.SetWindowTextA(_T("Bad Key"));
		percent=10;
		endCipher(param);
		return;
	case ERRORSHUFFLE:
		editLog.SetWindowTextA(_T("Shuffle Error"));
		percent=15;
		endCipher(param);
		return;
	case ERRORTYPE:
		editLog.SetWindowTextA(_T("Type Error"));
		percent=20;
		endCipher(param);
		return;
	}
	keyStr.SetString(_T(""));
	int len=key.length();
	for (int i=0;i<len;i++)
		keyStr+=key[i];
	if (prop.getUseKey())
		editKey.SetWindowTextA(keyStr);
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileOutput.GetWindowTextA(output);
		ofstream out(output);
		if (out.bad() || out.fail())
		{
			editLog.SetWindowTextA(_T("File Error"));
			percent=95;
			endCipher(param);
			return;
		}
		out<<finalStr;
	}
	else
	{
		int pos=finalStr.find('\n');
		while (pos!=-1)
		{
			finalStr.insert(pos,"\r");
			pos=finalStr.find('\n',pos+2);
		}
		len=finalStr.length();
		for (int i=0;i<len;i++)
			output+=finalStr[i];
		editConsolOutput.SetWindowTextA(output);
	}
	endCipher(param);
}

void CUniversalCiphermfcDlg::OnBnClickedButton3()
{
	CString strTmp1,strTmp2;
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileInput.GetWindowTextA(strTmp1);
		editFileOutput.GetWindowTextA(strTmp2);
		editFileInput.SetWindowTextA(strTmp2);
		editFileOutput.SetWindowTextA(strTmp1);
	}
	else
	{
		editConsolInput.GetWindowTextA(strTmp1);
		editConsolOutput.GetWindowTextA(strTmp2);
		editConsolInput.SetWindowTextA(strTmp2);
		editConsolOutput.SetWindowTextA(strTmp1);
	}
	editLog.SetWindowTextA(_T("Swap"));
}

void CUniversalCiphermfcDlg::OnBnClickedButton4()
{
	ThreadParam param(&progressVar,&hThread,&percent);
	startCipher(param);
	CString input,output,keyStr;
	string initialStr,finalStr,key;
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileInput.GetWindowTextA(input);
		ifstream in(input);
		if (in.bad() || in.fail())
		{
			editLog.SetWindowTextA(_T("File Error"));
			percent=5;
			endCipher(param);
			return;
		}
		string buff;
		while (getline(in,buff))
			initialStr+=buff+'\n';
		initialStr.erase(initialStr.end()-1);
		int len=initialStr.length();
		for (int i=0;i<len;i++)
			output+=initialStr[i];
	}
	else
	{
		editConsolInput.GetWindowTextA(input);
		initialStr=input;
		int pos=initialStr.find('\r');
		while (pos!=-1)
		{
			initialStr.erase(pos,1);
			pos=initialStr.find('\r');
		}
	}
	editKey.GetWindowTextA(keyStr);
	key=keyStr;
	Cipher c;
	switch (c.check(initialStr,key,prop.getCipherProp(),CIPHER,prop.getRandKey(),
		prop.getUseKey(),prop.getSafeCipher()))
	{
	case OK:
		output=_T("Cipher: All's OK");
		percent=100;
		break;
	case ERRORKEY:
		output=_T("Cipher: Bad Key");
		percent=10;
		endCipher(param);
		break;;
	case ERRORSHUFFLE:
		output=_T("Cipher: Shuffle Error");
		percent=15;
		endCipher(param);
		break;
	case ERRORTYPE:
		output=_T("Cipher: Type Error");
		percent=20;
		endCipher(param);
		break;
	}
	switch (c.check(initialStr,key,prop.getCipherProp(),DECIPHER,prop.getRandKey(),
		prop.getUseKey(),prop.getSafeCipher()))
	{
	case OK:
		editLog.SetWindowTextA(output+_T("\r\nDecipher: All's OK"));
		percent=100;
		break;
	case ERRORKEY:
		editLog.SetWindowTextA(output+_T("\r\nDecipher: Bad Key"));
		percent=10;
		endCipher(param);
		break;;
	case ERRORSHUFFLE:
		editLog.SetWindowTextA(output+_T("\r\nDecipher: Shuffle Error"));
		percent=15;
		endCipher(param);
		break;
	case ERRORTYPE:
		editLog.SetWindowTextA(output+_T("\r\nDecipher: Type Error"));
		percent=20;
		endCipher(param);
		break;
	}
	endCipher(param);
}

void CUniversalCiphermfcDlg::OnBnClickedCheck3()
{
	prop.setRandKey(!prop.getRandKey());
	if (prop.getRandKey())
		editLog.SetWindowTextA(_T("Key Autorandom Is On"));
	else
		editLog.SetWindowTextA(_T("Key Autorandom Is Off"));
}

void CUniversalCiphermfcDlg::OnBnClickedCheck4()
{
	prop.setUseKey(!prop.getUseKey());
	if (prop.getUseKey())
	{
		editLog.SetWindowTextA(_T("Use Key"));
		editKey.EnableWindow();
		checkRandKey.EnableWindow();
	}
	else
	{
		editLog.SetWindowTextA(_T("Don't Use Key"));
		editKey.EnableWindow(0);
		checkRandKey.EnableWindow(0);
	}
}

void CUniversalCiphermfcDlg::OnBnClickedButton5()
{
	if (!checkSafeCipher.GetCheck())
	{
		editLog.SetWindowTextA(_T("Error\r\nSelect Safe Cipher"));
		return;
	}
	ThreadParam param(&progressVar,&hThread,&percent);
	startCipher(param);
	CString input,output,keyStr;
	string initialStr,finalStr,key;
	if (prop.getInputProp()==FILEINPUT)
	{
		editFileInput.GetWindowTextA(input);
		ifstream in(input);
		if (in.bad() || in.fail())
		{
			editLog.SetWindowTextA(_T("File Error"));
			percent=5;
			endCipher(param);
			return;
		}
		string buff;
		while (getline(in,buff))
			initialStr+=buff+'\n';
		initialStr.erase(initialStr.end()-1);
		int len=initialStr.length();
		for (int i=0;i<len;i++)
			output+=initialStr[i];
	}
	else
	{
		editConsolInput.GetWindowTextA(input);
		initialStr=input;
		int pos=initialStr.find('\r');
		while (pos!=-1)
		{
			initialStr.erase(pos,1);
			pos=initialStr.find('\r');
		}
	}
	editKey.GetWindowTextA(keyStr);
	key=keyStr;
	Cipher c;
	c.restoreInitialStr(initialStr,prop.getCipherProp());
	endCipher(param);
}

void CUniversalCiphermfcDlg::OnBnClickedButton6()
{
	ThreadParam param(&progressVar,&hThread,&percent);
	startCipher(param);
	CString keyStr;
	string key;
	editKey.GetWindowTextA(keyStr);
	key=keyStr;
	Cipher c;
	if (c.restoreKey(key))
	{
		percent=100;
		editLog.SetWindowTextA(_T("Key Restoration Succesful"));
		keyStr.SetString(_T(""));
		for (unsigned int i=0;i<key.length();i++)
			keyStr+=key[i];
		editKey.SetWindowTextA(keyStr);
	}
	else
	{
		percent=10;
		keyStr.SetString(_T(""));
		for (unsigned int i=0;i<key.length();i++)
			keyStr+=key[i];
		editLog.SetWindowTextA(_T("KeyRestoration Unsuccesful\r\nPossible Key:\r\n")+keyStr);
	}
	endCipher(param);
}

void CUniversalCiphermfcDlg::OnBnClickedCheck2()
{
	prop.setSafeCipher(!prop.getSafeCipher());
	if (checkSafeCipher.GetCheck())
	{
		editLog.SetWindowTextA(_T("Use Safe Cipher Algorithm"));
		editKey.EnableWindow(0);
		checkRandKey.EnableWindow(0);
		checkUseKey.EnableWindow(0);
	}
	else
	{
		editLog.SetWindowTextA(_T("Use Usual Cipher Algorithm"));
		if (checkUseKey.GetCheck())
		{
			editKey.EnableWindow();
			checkRandKey.EnableWindow();
		}
		checkUseKey.EnableWindow();
	}
}
