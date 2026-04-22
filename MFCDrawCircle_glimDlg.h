
// MFCDrawCircle_glimDlg.h: 헤더 파일
//

#pragma once


// CMFCDrawCircleglimDlg 대화 상자
class CMFCDrawCircleglimDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCDrawCircleglimDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDRAWCIRCLE_GLIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CImage m_image;

	int m_circle_1_radius;
	int m_circle_2_radius;
	int m_circle_3_radius;
	int m_circle_thick;

	CString m_circle_1_xy;
	CString m_circle_2_xy;
	CString m_circle_3_xy;

	int m_circle_count = 0;
	CPoint m_circle_pos[3];

	void PaintDrawSpace();
	void UpdateDisplay();

	BOOL ValidImgPos(int x, int y, int w, int h);
	BOOL ValidImgPos(int x, int y);

	BOOL IsInCircle(int left_x, int top_y, int nCenterX, int nCenterY, int radius);
	void DrawCircle(int left_x, int top_y, int radius);


	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
};
