// shortestDlg.h : header file
//

#if !defined(AFX_SHORTESTDLG_H__E29F72D9_C6A2_410B_AF11_FC6682DB395E__INCLUDED_)
#define AFX_SHORTESTDLG_H__E29F72D9_C6A2_410B_AF11_FC6682DB395E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShortestDlg dialog
#include<math.h> // hypot()用到
const int r=14; // r是顶点半径
class CShortestDlg : public CDialog
{
// Construction
public:
	CShortestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShortestDlg)
	enum { IDD = IDD_SHORTEST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShortestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawLine(int m, int n, int i); // 以黑色Pen[i]细线型画笔在顶点m和顶点n之间画边(无向细线)
	void DrawLineText(int m, int n); // 在顶点m和顶点n之间的边旁以和边同样的倾角标注边的权值
	void DrawVertexText(int n,int x,int y); // 在距顶点n的中心(x,y)处写顶点名称
	CPen *pOldPen,Pen[2]; // 黑色细实[0]/虚[1]线笔
	void DrawVertexCircle(int n, int i); // 以Pen[i]画笔画序号为n的顶点的圆
 #define MAX_NAME 9 // 顶点字符串的最大长度+1
 POINT Dialog;
 struct VertexType // 顶点信息类型
 {
    char name[MAX_NAME]; // 顶点名称
	POINT pos; // 顶点坐标
 };
 #define INFINITY INT_MAX // 用整型最大值代替∞
 typedef int VRType; // 定义顶点关系类型为整型，与INFINITY的类型一致
 typedef char InfoType; // 弧(边)的相关信息类型
 #define MAX_VERTEX_NUM 26 // 最大顶点个数
 enum GraphKind{DG,DN,UDG,UDN}; // {有向图,有向网,无向图,无向网}
 typedef struct ArcCell // 边(弧)信息结构
 {
   VRType adj; // 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否；对带权图，则为权值
   InfoType *info; // 该弧相关信息的指针(可无)
 }AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 二维数组
 struct MGraph // 图的结构
 {
   VertexType vexs[MAX_VERTEX_NUM]; // 顶点向量
   AdjMatrix arcs; // 邻接矩阵(二维数组)
   int vexnum,arcnum; // 图的当前顶点数和弧数
   GraphKind kind; // 图的种类标志
 };
 typedef char PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 // 3维数组，其值只可能是0或1，故用char类型以减少存储空间的浪费
 typedef VRType DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 2维数组
	double R,X,Y;
	MGraph g;
	PathMatrix p;
	DistancMatrix d;
    int count; // 鼠标左键单击奇数次
	int	number[2]; // 起点城市[0]和终点城市[1]的序号
	int pa[MAX_VERTEX_NUM]; // 最短路径沿途所经过的城市数组
	void path1(MGraph G, PathMatrix P, int i, int j, int pa[]); // 求由序号为i的起点城市到序号为j的终点城市最短路径沿途所经过的城市，存于数组pa[]中
	void ShortestPath_FLOYD(MGraph G,PathMatrix P,DistancMatrix D); // 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w][]及其带权长度D[v][w]。若P[v][w][u]为TRUE，则u是从v到w当前求得最短路径上的顶点
	void InputArcFromFile(FILE *f,InfoType* &arc); // 由文件输入弧(边)的相关信息的函数(空)
    void InputFromFile(FILE *f,VertexType &ver); // 从文件输入顶点信息的函数
	void CreateFromFile(MGraph &G,char* filename,int IncInfo); // 采用数组(邻接矩阵)表示法，由文件构造图或网G。IncInfo=0或1，表示弧(边)无或有相关信息
	int LocateVex(MGraph G,VertexType u); // 初始条件：图G存在，u和G中顶点有相同特征(顶点名称相同)。操作结果：若G中存在顶点u，则返回该顶点在图中位置(序号)；否则返回-1
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTESTDLG_H__E29F72D9_C6A2_410B_AF11_FC6682DB395E__INCLUDED_)
