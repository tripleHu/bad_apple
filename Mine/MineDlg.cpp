
// MineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Mine.h"
#include "MineDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include"string.h"
#include <fstream>
using namespace std;

#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static int map[6601][80][60];
static int time1=1;
char buf[256];
threadInfo Info;
// CMineDlg �Ի���



CMineDlg::CMineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CMineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMineDlg ��Ϣ�������

BOOL CMineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
bitmap2.LoadBitmap(IDB_BITMAP2);

	CRect rc;

  GetWindowRect(&rc);

 SetWindowPos(&wndTop,rc.left,rc.top,1280+20,960+95+10,SWP_NOMOVE);//���ƶ�λ�ã����ı��С
 
 GetClientRect(&m_rect);
 
		MainCDC.DeleteDC();
    MainBmp.DeleteObject();
 CClientDC dc(this);
     MainCDC.CreateCompatibleDC(&dc);
	 MainBmp.CreateCompatibleBitmap(&dc,1280,960+105);
     MainCDC.SelectObject(&MainBmp);

	BackCDC.CreateCompatibleDC(&MainCDC);
	BackBmp.LoadBitmap(IDB_BITMAP1);
	BackCDC.SelectObject(&BackBmp);

	MainCDC.StretchBlt(0,0,1280,960+105,&BackCDC,0,0,1280,960+105,SRCCOPY);
	dc.StretchBlt(0,0,1280,960+105,&MainCDC,0,0,1280,960+105,SRCCOPY);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_HIDE);//ԭ������˽�����������ȡ����������ʾ
	m_Progress.SetRange(0,5450);  //������ȡֵ
	Info.nRange=5450;//������
	Info.pctrlProgress=&m_Progress;//������
	pThread=AfxBeginThread(ThreadFunc,  &Info);//�����߳����ڶ�ȡtxt�ļ�

	PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);//���ű�������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE

}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMineDlg::OnPaint()
{

	 CPaintDC dc(this); 

	 //CClientDC Cdc(this);

	 dc.BitBlt(0,0,1280,65,&MainCDC,0,0,SRCCOPY);
	// dc.BitBlt(0,65,1280,960,&BkDC,0,0 ,SRCCOPY);   //ǰһ��ͼƬ����һ��ͼƬ�ı�����������˸
	 BkDC.DeleteDC();
		BkMap.DeleteObject();
	//mciSendString("play movie",buf,sizeof(buf),NULL);
	//Sleep(1000);
	
	CDC dcMemory2;

  	dcMemory2.CreateCompatibleDC(&dc);
   	dcMemory2.SelectObject(&bitmap2);
	   //CBitmap BkMap;
	   BkMap.CreateCompatibleBitmap(&dc,1280,960);
	   //CDC BkDC;
	   BkDC.CreateCompatibleDC(&dc);
	   BkDC.SelectObject(&BkMap);                //�����Ǻ����������
		for (int j = 0; j < 80; j++) {
                    for (int k = 0; k < 60; k++) {
						
						BkDC.BitBlt(j*16,k*16,
					16,16,&dcMemory2,0,16*(15-map[time1][j][k]) ,SRCCOPY);
					
					}	
		}
		
		dc.BitBlt(0,65,1280,960,&BkDC,0,0 ,SRCCOPY);//��ʾͼ��
		/*BkDC.DeleteDC();
		BkMap.DeleteObject();*/
		Invalidate(FALSE);  //�������浫����������
				Sleep(18);                     //sleepʱ�������ʾ���ٶȣ����ݵ��Ե���
				
		if(time1<6600)      //���Ƴ����˳�ʱ������ʾ��5460��ͼ���˳�
			time1++;
		else
		exit(EXIT_FAILURE);

//��ͼ����������ⲿ�ֹ���
/*BITMAP bmp;
    BkMap.GetBitmap(&bmp);//���λͼ��Ϣ
	        string str;
		    stringstream ss;
		    string txt="E:\\SL\\";
			ss<<time1;
			ss>>str;
			txt=txt+str;
		    txt=txt+".jpg";
		
			char dst[20];
			strcpy_s(dst,txt.c_str());
    errno_t err;
    FILE *fp ;
	err= fopen_s(&fp,dst, "w+b");

    BITMAPINFOHEADER bih = {0};//λͼ��Ϣͷ
    bih.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;//�߶�
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С
    bih.biWidth = bmp.bmWidth;//���
    
    BITMAPFILEHEADER bfh = {0};//λͼ�ļ�ͷ
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//�����ڴ汣��λͼ����

    GetDIBits(BkDC.m_hDC, (HBITMAP) BkMap.m_hObject, 0, 960, p, 
        (LPBITMAPINFO) &bih, DIB_RGB_COLORS);//��ȡλͼ����

    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//д��λͼ����

    delete [] p;

    fclose(fp);*/
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
UINT ThreadFunc(LPVOID lpParam)    //�½��߳���ִ�еĴ���
{
       threadInfo* pInfo=(threadInfo*)lpParam;
	   loadtxt(); 
	   
       return 0;
}
void loadtxt()               // �˴�Ϊ����TXT�ļ����֣�
 {
	 for(int i=1;i<=6543;i++){      //6543�������޸����ֵ�����ƶ�ȡ��txt���ļ���
		 //pInfo->pctrlProgress->SetPos(i);   //���ƽ�����
		    string str;
		    stringstream ss;
		    string txt="D:\\SL\\2\\";
			ss<<i;
			ss>>str;
			txt=txt+str;
		    txt=txt+".txt";
			ifstream inFile;
	        inFile.open(txt);
	if(!inFile.is_open())
	{
		//MessageBox(_T("�Ҳ�����Ҫ��TXT�ļ�"));
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < 80; j++) {
         for (int k = 0; k < 60; k++) {
	inFile>>map[i][j][k];
		 }
	}inFile.close();
	                           }
}

void CMineDlg::OnTimer(UINT_PTR nIDEvent)   //��ʱ����û���õ�
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
   {
       case 1:
      {
		  time1++;
		  Invalidate(FALSE);  //�������浫����������
		  break;
	  }
	}
	CDialogEx::OnTimer(nIDEvent);
}
