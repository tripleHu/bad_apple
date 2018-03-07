
// MineDlg.cpp : 实现文件
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
// CMineDlg 对话框



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


// CMineDlg 消息处理程序

BOOL CMineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
bitmap2.LoadBitmap(IDB_BITMAP2);

	CRect rc;

  GetWindowRect(&rc);

 SetWindowPos(&wndTop,rc.left,rc.top,1280+20,960+95+10,SWP_NOMOVE);//不移动位置，但改变大小
 
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
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_HIDE);//原来设计了进度条，现在取消掉，不显示
	m_Progress.SetRange(0,5450);  //进度条取值
	Info.nRange=5450;//进度条
	Info.pctrlProgress=&m_Progress;//进度条
	pThread=AfxBeginThread(ThreadFunc,  &Info);//开启线程用于读取txt文件

	PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);//播放背景音乐

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE

}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMineDlg::OnPaint()
{

	 CPaintDC dc(this); 

	 //CClientDC Cdc(this);

	 dc.BitBlt(0,0,1280,65,&MainCDC,0,0,SRCCOPY);
	// dc.BitBlt(0,65,1280,960,&BkDC,0,0 ,SRCCOPY);   //前一张图片做后一张图片的背景，避免闪烁
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
	   BkDC.SelectObject(&BkMap);                //这里是核心输出部分
		for (int j = 0; j < 80; j++) {
                    for (int k = 0; k < 60; k++) {
						
						BkDC.BitBlt(j*16,k*16,
					16,16,&dcMemory2,0,16*(15-map[time1][j][k]) ,SRCCOPY);
					
					}	
		}
		
		dc.BitBlt(0,65,1280,960,&BkDC,0,0 ,SRCCOPY);//显示图像
		/*BkDC.DeleteDC();
		BkMap.DeleteObject();*/
		Invalidate(FALSE);  //擦除画面但不擦除背景
				Sleep(18);                     //sleep时间控制显示的速度，根据电脑调整
				
		if(time1<6600)      //控制程序退出时间在显示了5460张图后退出
			time1++;
		else
		exit(EXIT_FAILURE);

//截图输出，不用这部分功能
/*BITMAP bmp;
    BkMap.GetBitmap(&bmp);//获得位图信息
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

    BITMAPINFOHEADER bih = {0};//位图信息头
    bih.biBitCount = bmp.bmBitsPixel;//每个像素字节大小
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;//高度
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//图像数据大小
    bih.biWidth = bmp.bmWidth;//宽度
    
    BITMAPFILEHEADER bfh = {0};//位图文件头
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//文件总的大小
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//写入位图文件头
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//写入位图信息头
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//申请内存保存位图数据

    GetDIBits(BkDC.m_hDC, (HBITMAP) BkMap.m_hObject, 0, 960, p, 
        (LPBITMAPINFO) &bih, DIB_RGB_COLORS);//获取位图数据

    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//写入位图数据

    delete [] p;

    fclose(fp);*/
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMineDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
UINT ThreadFunc(LPVOID lpParam)    //新建线程所执行的代码
{
       threadInfo* pInfo=(threadInfo*)lpParam;
	   loadtxt(); 
	   
       return 0;
}
void loadtxt()               // 此处为调用TXT文件部分，
 {
	 for(int i=1;i<=6543;i++){      //6543，可以修改这个值来控制读取的txt的文件数
		 //pInfo->pctrlProgress->SetPos(i);   //控制进度条
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
		//MessageBox(_T("找不到必要的TXT文件"));
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < 80; j++) {
         for (int k = 0; k < 60; k++) {
	inFile>>map[i][j][k];
		 }
	}inFile.close();
	                           }
}

void CMineDlg::OnTimer(UINT_PTR nIDEvent)   //定时器，没有用到
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
   {
       case 1:
      {
		  time1++;
		  Invalidate(FALSE);  //擦除画面但不擦除背景
		  break;
	  }
	}
	CDialogEx::OnTimer(nIDEvent);
}
