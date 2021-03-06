
// MutexProjectDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MutexProject.h"
#include "MutexProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMutexProjectDlg 대화 상자



CMutexProjectDlg::CMutexProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUTEXPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMutexProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_VALUE2, m_Value2);
}

BEGIN_MESSAGE_MAP(CMutexProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMutexProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMutexProjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMutexProjectDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMutexProjectDlg 메시지 처리기

BOOL CMutexProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CButton *button1 = (CButton*)GetDlgItem(IDOK);
	CButton *button2 = (CButton*)GetDlgItem(IDCANCEL);
	button1->DestroyWindow();
	button2->DestroyWindow();

	SetTimer(1, 100, NULL);
	SetTimer(2, 100, NULL);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMutexProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMutexProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMutexProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CWinThread *m_pThread = new CWinThread();
CWinThread *m_pThread2 = new CWinThread();
CWinThread *m_pThread3 = new CWinThread();
CWinThread *m_pThread4 = new CWinThread();

BOOL SharingValue = TRUE;
BOOL SharingValue2 = TRUE;
int FunctionNum = 0;

int count = 0;
int count2 = 0;

HANDLE g_hMutex;

void CMutexProjectDlg::OnTimer(UINT_PTR nIDEvent) {
	if (nIDEvent == 1) {
		CString string;
		string.Format(L"%d", count);

		m_Value.SetWindowText(string);
	}
	else if (nIDEvent == 2) {
		CString string;
		string.Format(L"%d", count2);

		m_Value2.SetWindowText(string);
	}
}

UINT CMutexProjectDlg::ThreadFunction(LPVOID _mothod) {
	while(1){
		//SharingValue = TRUE;
		count += 1;
		Sleep(100);
	}
	return 0;
}

UINT CMutexProjectDlg::SecThreadFunction(LPVOID _mothod) {
	while (1) {
		//SharingValue = FALSE;
		count += 1;
		Sleep(100);
	}
	return 0;
}

void CMutexProjectDlg::OnBnClickedButton1()
{
	m_pThread = AfxBeginThread(ThreadFunction, this);
	m_pThread2 = AfxBeginThread(SecThreadFunction, this);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

UINT CMutexProjectDlg::ThirdThreadFunction(LPVOID _mothod) {
	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);
		//SharingValue2 = TRUE;
		count2 += 1;
		Sleep(100);
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

UINT CMutexProjectDlg::FourthThreadFunction(LPVOID _mothod) {
	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);
		//SharingValue2 = FALSE;
		count2 += 1;
		Sleep(100);
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

void CMutexProjectDlg::OnBnClickedButton2()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	m_pThread3 = AfxBeginThread(ThirdThreadFunction, this);
	m_pThread4 = AfxBeginThread(FourthThreadFunction, this);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMutexProjectDlg::OnBnClickedButton3()
{
	m_pThread = AfxBeginThread(ThreadFunction, this);
	m_pThread2 = AfxBeginThread(SecThreadFunction, this);

	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	m_pThread3 = AfxBeginThread(ThirdThreadFunction, this);
	m_pThread4 = AfxBeginThread(FourthThreadFunction, this);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
