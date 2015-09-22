// Universal Cipher mfcDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Cipher.h"

#define FILEINPUT 1
#define CONSOLINPUT 2

// CUniversalCiphermfcDlg dialog
class CUniversalCiphermfcDlg : public CDialog
{
// Construction
public:
	CUniversalCiphermfcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UNIVERSALCIPHERMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl progressVar;
	CButton radioUseFiles;
	CButton radioUseConsol;
	CButton radioNumber;
	CButton radioText;
	CButton radioExpanded;
	CEdit editLog;
	afx_msg void OnBnClickedRadio1();
private:
	class Properties
	{
		int inputProp;
		int cipherProp;
		bool randKey;
		bool useKey;
		bool useCheck;
		bool safeCipher;
	public:
		Properties():
		  inputProp(CONSOLINPUT),cipherProp(SYMBOL),randKey(true),
			  useKey(true),useCheck(false),safeCipher(false){}
		Properties(int _inputProp,int _cipherProp,bool _randKey,
			bool _useCheck=false,bool _useKey=true,bool _safeCipher=false):
		  inputProp(_inputProp),cipherProp(_cipherProp),randKey(_randKey),
			  useCheck(_useCheck),useKey(_useKey),safeCipher(_safeCipher){}
		int getInputProp()
		{
			return inputProp;
		}
		int getCipherProp()
		{
			return cipherProp;
		}
		bool getRandKey()
		{
			return randKey;
		}
		bool getUseKey()
		{
			return useKey;
		}
		bool getUseCheck()
		{
			return useCheck;
		}
		bool getSafeCipher()
		{
			return safeCipher;
		}
		void setInputProp(int _inputProp)
		{
			inputProp=_inputProp;
		}
		void setCipherProp(int _cipherProp)
		{
			cipherProp=_cipherProp;
		}
		void setRandKey(bool _randKey)
		{
			randKey=_randKey;
		}
		void setUseKey(bool _useKey)
		{
			useKey=_useKey;
		}
		void setUseCheck(bool _useCheck)
		{
			useCheck=_useCheck;
		}
		void setSafeCipher(bool _safeCipher)
		{
			safeCipher=_safeCipher;
		}
	} prop;
	HANDLE hThread;
	int percent;
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	CButton checkCheckCipher;
	afx_msg void OnBnClickedCheck1();
	CEdit editConsolInput;
	CEdit editConsolOutput;
	CEdit editFileInput;
	CEdit editFileOutput;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CEdit editKey;
	afx_msg void OnBnClickedButton4();
	CButton checkRandKey;
	afx_msg void OnBnClickedCheck3();
	CButton checkUseKey;
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CButton checkSafeCipher;
	afx_msg void OnBnClickedCheck2();
};