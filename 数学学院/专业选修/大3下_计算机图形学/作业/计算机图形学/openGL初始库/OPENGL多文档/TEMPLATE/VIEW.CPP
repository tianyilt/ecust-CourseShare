// $$root$$View.cpp : implementation of the C$$Safe_root$$View class
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$root$$Doc.h"
#include "$$root$$View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View

IMPLEMENT_DYNCREATE(C$$Safe_root$$View, CGLEnabledView)

BEGIN_MESSAGE_MAP(C$$Safe_root$$View, CGLEnabledView)
	//{{AFX_MSG_MAP(C$$Safe_root$$View)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View construction/destruction

C$$Safe_root$$View::C$$Safe_root$$View()
{
	// TODO: add construction code here
/////////////////////////////////////////////////////////////////////////////
//初始化成员变量
	X_Angle=0.0;
	Y_Angle=0.0;
//////////////////////////////////////////////////////////////////////////////
}

C$$Safe_root$$View::~C$$Safe_root$$View()
{
}


/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View printing

BOOL C$$Safe_root$$View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void C$$Safe_root$$View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void C$$Safe_root$$View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View diagnostics

#ifdef _DEBUG
void C$$Safe_root$$View::AssertValid() const
{
	CView::AssertValid();
}

void C$$Safe_root$$View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C$$Safe_root$$Doc* C$$Safe_root$$View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C$$Safe_root$$Doc)));
	return (C$$Safe_root$$Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$View message handlers
void C$$Safe_root$$View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 记录鼠标的位置
	MouseDownPoint=point;
	// 捕捉鼠标的运动
	SetCapture();
	
//	CGLEnabledView::OnLButtonDown(nFlags, point);
}

void C$$Safe_root$$View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 鼠标按下位置置于原点
	MouseDownPoint=CPoint(0,0);
	// 解除捕捉鼠标
	ReleaseCapture();	
//	CGLEnabledView::OnLButtonUp(nFlags, point);
}

void C$$Safe_root$$View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 检测是否捕捉鼠标
	if (GetCapture()==this)
	{
	// 旋转对象一个步长
		X_Angle+=double(point.y-MouseDownPoint.y)/3.6;
		Y_Angle+=double(point.x-MouseDownPoint.x)/3.6;
	// 更新场景
		Invalidate(TRUE);
	// 记下鼠标位置
		MouseDownPoint=point;
	};	
//	CGLEnabledView::OnMouseMove(nFlags, point);
}


void C$$Safe_root$$View::OnDrawGL()
{
	glPushMatrix();
	// 旋转对象一个给定的角度
	glRotated(X_Angle,1.0,0.0,0.0);
	glRotated(Y_Angle,0.0,1.0,0.0);
	glBegin(GL_LINES);
		// yellow x axis arrow
		glColor3f(1.f,1.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.1f,0.0f);
		// cyan y axis arrow
		glColor3f(0.f,1.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.1f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.1f,0.9f,0.0f);
		// magenta z axis arrow
		glColor3f(1.f,0.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.1f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.1f,0.9f);
	glEnd();

	glPopMatrix();
}


