
// MineDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMineDlg �Ի���
class CMineDlg : public CDialogEx
{
// ����
public:

	CMineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	  CDC BackCDC;
	CBitmap  BackBmp;
CDC     MainCDC;
CBitmap	 MainBmp;

	CBitmap           bitmap1; 
	CBitmap           bitmap2; 
	CRect              m_rect;
    
	CDC BkDC;
	CBitmap BkMap;
	CWinThread *pThread;//�̺߳���������
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��

	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_Progress;
};
struct threadInfo

{

    unsigned int nRange;//��Χ

    CProgressCtrl* pctrlProgress;

};
UINT ThreadFunc(LPVOID pParm);//�̺߳����Ķ���
void loadtxt();