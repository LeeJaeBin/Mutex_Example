
// MutexProjectDlg.h: 헤더 파일
//

#pragma once


// CMutexProjectDlg 대화 상자
class CMutexProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CMutexProjectDlg(CWnd* pParent = nullptr);
	afx_msg void OnTimer(UINT_PTR nIDEvent);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUTEXPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	static UINT ThreadFunction(LPVOID _mothod);
	static UINT SecThreadFunction(LPVOID _mothod);
	static UINT ThirdThreadFunction(LPVOID _mothod);
	static UINT FourthThreadFunction(LPVOID _mothod);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Value;
	afx_msg void OnBnClickedButton1();
	CStatic m_Function;
	CStatic m_Value2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
