
// MFCDrawCircle_glimDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCDrawCircle_glim.h"
#include "MFCDrawCircle_glimDlg.h"
#include "afxdialogex.h"
#include "resource.h"

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


// CMFCDrawCircleglimDlg 대화 상자



CMFCDrawCircleglimDlg::CMFCDrawCircleglimDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDRAWCIRCLE_GLIM_DIALOG, pParent)
	, m_circle_1_radius(10)
	, m_circle_2_radius(10)
	, m_circle_3_radius(10)
	, m_circle_thick(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDrawCircleglimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CIRCLE_1_R, m_circle_1_radius);
	DDX_Text(pDX, IDC_CIRCLE_2_R, m_circle_2_radius);
	DDX_Text(pDX, IDC_CIRCLE_3_R, m_circle_3_radius);
	DDX_Text(pDX, IDC_CIRCLE_THICK, m_circle_thick);
}

BEGIN_MESSAGE_MAP(CMFCDrawCircleglimDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_RESET, &CMFCDrawCircleglimDlg::OnBnClickedBtnReset)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCDrawCircleglimDlg 메시지 처리기

BOOL CMFCDrawCircleglimDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCDrawCircleglimDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCDrawCircleglimDlg::OnPaint()
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

		PaintDrawSpace();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCDrawCircleglimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCDrawCircleglimDlg::UpdateDisplay()
{
	CClientDC dc(this);

	CRect rect;
	GetDlgItem(IDC_DRAW_SPACE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_image.Draw(dc, rect.left, rect.top);
}


void CMFCDrawCircleglimDlg::PaintDrawSpace()
{
	CRect rect;
	GetDlgItem(IDC_DRAW_SPACE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nWidth = rect.Width();
	int nHeight = rect.Height();
	int nBpp = 8;

	int bgColor = 0xff;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int y = 0; y < nHeight; y++) {			// 열
		memset(fm + y * nPitch, bgColor, nWidth);	// 행
	}


	UpdateDisplay();
}


BOOL CMFCDrawCircleglimDlg::IsInCircle(int left_x, int top_y, int nCenterX, int nCenterY, int radius)
{
	bool bRect = false;

	double dx = left_x - nCenterX;
	double dy = top_y - nCenterY;
	double dDist = dx * dx + dy * dy;

	if (dDist < radius * radius) {
		bRect = true;
	}

	return bRect;
}


void CMFCDrawCircleglimDlg::DrawCircle(int left_x, int top_y, int radius)
{
	int nCenterX = left_x + radius;
	int nCenterY = top_y + radius;

	//int nPitch = m_image_bg.GetPitch();


}


void CMFCDrawCircleglimDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	
}


void CMFCDrawCircleglimDlg::OnBnClickedBtnReset()
{
	
}



