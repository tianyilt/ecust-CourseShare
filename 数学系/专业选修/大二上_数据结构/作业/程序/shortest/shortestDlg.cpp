// shortestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shortest.h"
#include "shortestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortestDlg dialog

CShortestDlg::CShortestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShortestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShortestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShortestDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShortestDlg, CDialog)
	//{{AFX_MSG_MAP(CShortestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortestDlg message handlers

BOOL CShortestDlg::OnInitDialog()
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
	CRect rect;
	ShowWindow(SW_SHOWMAXIMIZED); // 最大化对话框窗口
    GetClientRect(rect); // 得到对话框的窗口尺寸并赋给rect(左上角为0,0)
	Dialog.x=rect.right; // 将对话框的窗口尺寸赋给全局坐标量Dialog
    Dialog.y=rect.bottom;
	CWnd *pWnd=GetDlgItem(IDOK); // pWnd指向“退出”按钮
	pWnd->GetClientRect(rect); // 得到“退出”按钮的尺寸并赋给rect(左上角为0,0)
	pWnd->SetWindowPos(NULL,Dialog.x-rect.right-10,Dialog.y-rect.bottom-10,0,0,SWP_NOSIZE); // 设置“退出”按钮在右下角
	pWnd=GetDlgItem(IDC_STATIC1); // pWnd指向固定文本框("全国铁路交通示意图")
	pWnd->GetClientRect(rect); // 得到固定文本框的尺寸并赋给rect(左上角为0,0)
	pWnd->SetWindowPos(NULL,(Dialog.x-rect.right)/2,0,0,0,SWP_NOSIZE); // 设置固定文本框在上边居中
    CreateFromFile(g,"mapvc.txt",0); // 通过当前目录下的文件mapvc.txt构造没有相关信息的无向网g
	int i;
	int Xmin=g.vexs[0].pos.x,Xmax=g.vexs[0].pos.x,Ymin=g.vexs[0].pos.y,Ymax=g.vexs[0].pos.y;
	for(i=1;i<g.vexnum;i++) // 求得顶点坐标的最小值、最大值，分别存入Xmin、Xmax、Ymin和Ymax
	{
		if(g.vexs[i].pos.x<Xmin)
			Xmin=g.vexs[i].pos.x;
		else if(g.vexs[i].pos.x>Xmax)
			Xmax=g.vexs[i].pos.x;
		if(g.vexs[i].pos.y<Ymin)
			Ymin=g.vexs[i].pos.y;
		else if(g.vexs[i].pos.y>Ymax)
			Ymax=g.vexs[i].pos.y;
	}
	for(i=0;i<g.vexnum;i++) // 对所有顶点
	{
		g.vexs[i].pos.x=(Dialog.x-4*r)*(g.vexs[i].pos.x-Xmin)/(Xmax-Xmin)+2*r; // 修改顶点坐标，使得适应屏幕尺寸(最大、最小坐标都距边界2r)
		g.vexs[i].pos.y=(Dialog.y-4*r)*(g.vexs[i].pos.y-Ymin)/(Ymax-Ymin)+2*r;
		g.arcs[i][i].adj=0; // ShortestPath_FLOYD()要求对角元素值为0,因为两点相同,其距离为0
	}
	ShortestPath_FLOYD(g,p,d); // 求图g中每对顶点间的最短路径。存于二维数组d中，三维数组p中存放的是每对顶点间的最短路径所经过的顶点
	count=0; // 鼠标左键单击次数，初值为0
	Pen[0].CreatePen(PS_SOLID,1,RGB(0,0,0)); // 黑色细实线笔
	Pen[1].CreatePen(PS_DOT,1,RGB(0,0,0)); // 黑色细点(虚)线笔
	pOldPen=NULL;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShortestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShortestDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		//CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		int i,j;
		for(i=0;i<g.vexnum;i++) // 对所有顶点
			DrawVertexCircle(i,0); // 以黑色细实线画序号为i的顶点的圆
		DrawVertexText(0,3*r,-r/2); // 写顶点乌鲁木齐的名称
		DrawVertexText(1,0,-r*2); // 写顶点呼和浩特的名称
		DrawVertexText(2,-3*r,-r/2); // 写顶点哈尔滨的名称
		for(i=3;i<g.vexnum;i++) // 顶点
			DrawVertexText(i,0,0); // 写顶点名称，顶点[0]～[2]的名称大于2个汉字，在上面另行处理
		for(i=0;i<g.vexnum;i++) // 边(无向)
			for(j=0;j<i;j++)
				if(g.arcs[i][j].adj!=INFINITY) // 有边
				{
					DrawLine(i,j,0); // 以黑色实细线型画笔在顶点i和顶点j之间画边(无向细线)
					DrawLineText(i,j); // 在顶点i和顶点j之间的边旁以和边同样的倾角标注边的权值
				}
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShortestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShortestDlg::CreateFromFile(MGraph &G, char *filename, int IncInfo)
 { // 采用数组(邻接矩阵)表示法，由文件构造图或网G。IncInfo=0或1，表示弧(边)无或有相关信息
   int i,j,k;
   VRType w=0; // 顶点关系类型，图
   VertexType v1,v2; // 顶点类型
   FILE *f; // 文件指针类型
   f=fopen(filename,"r"); // 打开数据文件，并以f表示
   fscanf(f,"%d",&G.kind); // 由文件输入G的类型
   if(G.kind%2) // 网
     w=INFINITY;
   fscanf(f,"%d",&G.vexnum); // 由文件输入G的顶点数
   for(i=0;i<G.vexnum;++i)
     InputFromFile(f,G.vexs[i]); // 由文件输入顶点信息
   fscanf(f,"%d",&G.arcnum); // 由文件输入G的弧(边)数
   for(i=0;i<G.vexnum;++i) // 初始化二维邻接矩阵
     for(j=0;j<G.vexnum;++j)
     {
       G.arcs[i][j].adj=w; // 不相邻
       G.arcs[i][j].info=NULL; // 没有相关信息
     }
   if(!(G.kind%2)) // 图
     w=1;
   for(k=0;k<G.arcnum;++k) // 对于所有弧
   {
     fscanf(f,"%s%s",v1.name,v2.name); // 输入弧尾、弧头的名称
     if(G.kind%2) // 网
       fscanf(f,"%d",&w); // 再输入权值
     i=LocateVex(G,v1); // 弧尾的序号
     j=LocateVex(G,v2); // 弧头的序号
     G.arcs[i][j].adj=w; // 权值
     if(IncInfo) // 有相关信息
       InputArcFromFile(f,G.arcs[i][j].info);
       // 由文件动态生成存储空间，输入弧的相关信息
     if(G.kind>1) // 无向
       G.arcs[j][i]=G.arcs[i][j]; // 无向，两个单元的信息相同
   }
   fclose(f); // 关闭数据文件
 }

void CShortestDlg::InputFromFile(FILE *f, VertexType &ver) // 与之配套的从文件输入顶点信息的函数
{
   fscanf(f,"%s%d%d",ver.name,&ver.pos.x,&ver.pos.y);
}

int CShortestDlg::LocateVex(MGraph G, VertexType u)
 { // 初始条件：图G存在，u和G中顶点有相同特征(顶点名称相同)
   // 操作结果：若G中存在顶点u，则返回该顶点在图中位置(序号)；否则返回-1
   int i;
   for(i=0;i<G.vexnum;++i) // 对于所有顶点依次查找
     if(strcmp(u.name,G.vexs[i].name)==0) // 顶点与给定的u的顶点名称相同
       return i; // 返回顶点序号
   return -1; // 图G中不存在与顶点u有相同名称的顶点
 }

void CShortestDlg::InputArcFromFile(FILE *f, InfoType *&arc) // 由文件输入弧(边)的相关信息的函数(空)
{
}

void CShortestDlg::ShortestPath_FLOYD(MGraph G, PathMatrix P, DistancMatrix D)
 { // 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w][]及其带权长度D[v][w]。
   // 若P[v][w][u]为TRUE，则u是从v到w当前求得最短路径上的顶点。算法7.16
   int u,v,w,i;
   for(v=0;v<G.vexnum;v++) // 各对结点之间初始已知路径及距离
     for(w=0;w<G.vexnum;w++)
     {
       D[v][w]=G.arcs[v][w].adj; // 顶点v到顶点w的直接距离
       for(u=0;u<G.vexnum;u++)
         P[v][w][u]=FALSE; // 路径矩阵初值
       if(D[v][w]<INFINITY) // 从v到w有直接路径
         P[v][w][v]=P[v][w][w]=TRUE; // 由v到w的路径经过v和w两点
     }
   for(u=0;u<G.vexnum;u++)
     for(v=0;v<G.vexnum;v++)
       for(w=0;w<G.vexnum;w++)
         if(D[v][u]<INFINITY&&D[u][w]<INFINITY&&D[v][u]+D[u][w]<D[v][w])
         { // 从v经u到w的一条路径更短
           D[v][w]=D[v][u]+D[u][w]; // 更新最短距离
           for(i=0;i<G.vexnum;i++)
             P[v][w][i]=P[v][u][i]||P[u][w][i];
             // 从v到w的路径经过从v到u和从u到w的所有路径
         }
 }

void CShortestDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString strMessage,ss;
	int i,k;
	for(i=0;i<g.vexnum;i++) // 求得鼠标点击顶点的序号i
	{
		X=double(point.x-g.vexs[i].pos.x);
		Y=double(point.y-g.vexs[i].pos.y);
		if(int(hypot(X,Y))<=r) // hypot()：斜边
		{
			count++;
			break;
		}
	}
	if(i<g.vexnum) // 鼠标点击了序号为i的顶点
	{
		if(count%2) // 鼠标左键单击奇数次(点击起点)
		{
			if(count>1) // 不是第一次求最短距离，要用黑笔重画
			{
				DrawVertexCircle(number[0],0); // 用黑笔重画起点
				DrawVertexCircle(number[1],0); // 用黑笔重画终点
				k=1;
				while(pa[k]!=-1) // pa[k]是依次经过的顶点序号
				{
					DrawLine(pa[k-1],pa[k],0); // 以黑色实细线型画笔在顶点pa[k-1]和顶点pa[k]之间画边(无向细线)
					DrawVertexCircle(pa[k],0); // 用黑笔重画依次经过的顶点
					k++;
				};
			}
			DrawVertexCircle(i,1); // 用虚线笔重画鼠标所点之顶点(起点)
			number[0]=i; // 该顶点为起点
			SetWindowLong(GetSafeHwnd(),GWL_STYLE,GetWindowLong(GetSafeHwnd(),GWL_STYLE)& (~WS_MINIMIZEBOX)); // 使对话框最小化按钮不可用
		}
		else // 鼠标左键单击偶数次（点击终点）
		{
			number[1]=i; // 该顶点为终点
			if(d[number[0]][number[1]]<INFINITY) // 有通路
			{
				path1(g,p,number[0],number[1],pa); // 求最短路径上由起点城市到终点城市沿途所经过的城市，其顶点序号存于数组pa
				strMessage.Format("%s到%s的最短距离为%d\n途经: %s ",g.vexs[number[0]].name,g.vexs[number[1]].name,d[number[0]][number[1]],g.vexs[pa[0]].name);
				int k=1;
				while(pa[k]!=-1)
				{
					DrawLine(pa[k-1],pa[k],1); // 以黑色虚线画笔在顶点pa[k-1]和顶点pa[k]之间画边(无向细线)
					DrawVertexCircle(pa[k],1); // 用虚线笔重画沿线之顶点
					ss.Format("%s ",g.vexs[pa[k++]].name);
					strMessage+=ss;
				}
			}
			else
			{
				DrawVertexCircle(i,1); // 用虚线笔重画鼠标所点之顶点(终点)
				strMessage.Format("%s到%s没有路径可通\n",g.vexs[number[0]].name,g.vexs[number[1]].name);
				pa[1]=-1; // 没有路径可通的情况下，不再用黑笔重画直线的标志
			}
			MessageBox(strMessage,"最短路径");
			SetWindowLong(GetSafeHwnd(),GWL_STYLE,GetWindowLong(GetSafeHwnd(),GWL_STYLE)^ (WS_MINIMIZEBOX)); // 使对话框最小化按钮重新可用
		}
	}	
	CDialog::OnLButtonDown(nFlags, point);
}

void CShortestDlg::path1(MGraph G, PathMatrix P, int i, int j, int pa[])
{ // 求由序号为i的起点城市到序号为j的终点城市最短路径沿途所经过的城市，存于数组pa[]中
	int k,n=0,m=i; // 起点城市序号赋给m
	for(k=0;k<G.vexnum;k++)
		pa[k]=-1; // pa的初值
	while(m!=j) // 没到终点城市
	{
		G.arcs[m][m].adj=INFINITY; // 对角元素赋值无穷大
		for(k=0;k<G.vexnum;k++)
			if(G.arcs[m][k].adj<INFINITY&&P[m][j][k]) // m到k有直接通路，且k在m到j的最短路径上
			{
				pa[n++]=m;
				G.arcs[m][k].adj=G.arcs[k][m].adj=INFINITY; // 将直接通路设为不通
				m=k; // 经过的城市序号赋给m，继续查找
				break;
			}
	}
	pa[n]=j; // 终点城市
}

void CShortestDlg::DrawVertexCircle(int n, int i)
{ // 以黑色Pen[i]细线型画序号为n的顶点的圆
	CDC* pDC=GetDC(); // 得到设备环境(以便画图)
	pDC->SelectStockObject(NULL_BRUSH); // 图形透明(不填充)
	pOldPen=pDC->SelectObject(&Pen[i]); // 选择黑色Pen[i]型的细线画笔
	pDC->Ellipse(g.vexs[n].pos.x-r,g.vexs[n].pos.y-r,g.vexs[n].pos.x+r,g.vexs[n].pos.y+r); // 用当前色的画笔画序号为n的圆
	pDC->SelectObject(pOldPen); // 恢复原有的画笔
	ReleaseDC(pDC); //  与pDC=GetDC()对应
}

void CShortestDlg::DrawVertexText(int n,int x,int y)
{ // 在距顶点n的中心(x,y)处写顶点名称
	CDC* pDC=GetDC(); // 得到设备环境(以便写文本)
	pDC->SetBkMode(TRANSPARENT); // 设置文本背景为透明的
	pDC->SetTextAlign(TA_CENTER); // 设置文本对齐方式，指定点在中间
	CFont *pOldFont=NULL,fnBig;
	fnBig.CreatePointFont(90,"宋体",NULL); // 设置文本的字号和字体
	pOldFont=pDC->SelectObject(&fnBig);
	pDC->TextOut(g.vexs[n].pos.x+x,g.vexs[n].pos.y-r/2+y,g.vexs[n].name);
	pDC->SelectObject(pOldFont); // 恢复原有的字体风格，非常重要
	ReleaseDC(pDC); //  与pDC=GetDC()对应
}

void CShortestDlg::DrawLineText(int m, int n)
{ // 在顶点m和顶点n之间的边旁以和边同样的倾角标注边的权值
	int q;
	CDC* pDC=GetDC(); // 得到设备环境(以便写文本)
	pDC->SetBkMode(TRANSPARENT); // 设置文本背景为透明的
	pDC->SetTextAlign(TA_CENTER); // 设置文本对齐方式，指定点在中间
	X=g.vexs[n].pos.x-g.vexs[m].pos.x;
	Y=g.vexs[n].pos.y-g.vexs[m].pos.y;
	R=hypot(X,Y); // 边的长度，由顶点中心算起
	q=int(atan2(-Y,X)*1800/3.14159216); // 边的倾角，单位是0.1度
	if(q>1350) // 使边的倾角在-45°～135°之间
		q-=1800;
	else if(q<-450)
		q+=1800;
	CFont fnBig;
	fnBig.CreateFont(r,0,q,0,0,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS, // 设置倾斜的字体风格
	CLIP_DEFAULT_PRECIS,PROOF_QUALITY,DEFAULT_PITCH+FF_DONTCARE,"Times New Roman");  
	CFont *pOldFont=pDC->SelectObject(&fnBig); // 选择倾斜的字体，并将原有的字体风格存于pOldFont，非常重要
	CString str;
	str.Format("%d",g.arcs[m][n].adj); // 边的权值赋给串str
	pDC->TextOut(g.vexs[n].pos.x-int(X/2),g.vexs[n].pos.y-int(Y/2)+2,str); // 用倾斜的字体在边的附近写权值
	pDC->SelectObject(pOldFont); // 恢复原有的字体风格，非常重要
	ReleaseDC(pDC); //  与pDC=GetDC()对应
}

void CShortestDlg::DrawLine(int m, int n, int i)
{ // 以黑色Pen[i]细线型画笔在顶点m和顶点n之间画边(无向细线)
	int x,y;
	CDC* pDC=GetDC(); // 得到设备环境(以便画图)
	pDC->SelectStockObject(NULL_BRUSH); // 图形透明(不填充)
	pOldPen=pDC->SelectObject(&Pen[i]); // 选择黑色Pen[i]型的细线画笔
	X=g.vexs[n].pos.x-g.vexs[m].pos.x;
	Y=g.vexs[n].pos.y-g.vexs[m].pos.y;
	R=hypot(X,Y); // 边的长度，由顶点中心算起
	x=int(r*X/R); // 按以上倾角，圆心到圆周水平、垂直的距离
	y=int(r*Y/R);
	pDC->MoveTo(g.vexs[m].pos.x+x,g.vexs[m].pos.y+y); // 由两顶点的圆周起画边
	pDC->LineTo(g.vexs[n].pos.x-x,g.vexs[n].pos.y-y);
	pDC->SelectObject(pOldPen); // 恢复原有的画笔
	ReleaseDC(pDC); //  与pDC=GetDC()对应
}
