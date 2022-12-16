// OpenGL.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "OpenGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGL

COpenGL::COpenGL()
{
	//给成员变量赋初值
	step=0.0;
	s=0.1;
}

COpenGL::~COpenGL()
{
	wglMakeCurrent(NULL, NULL) ; 
	wglDeleteContext(hglrc);	//删除渲染描述表
	::ReleaseDC (m_hWnd, hdc) ; //释放设备描述表

}


BEGIN_MESSAGE_MAP(COpenGL, CWnd)
	//{{AFX_MSG_MAP(COpenGL)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
// 设置像素格式函数
int COpenGL::MySetPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 
	
	int  iPixelFormat; 
 
	// 为设备描述表得到最匹配的像素格式 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat Failed", NULL, MB_OK);
		return 0;
	}
	 
	// 设置最匹配的像素格式为当前的像素格式 
	if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat Failed", NULL, MB_OK);
		return 0;
	}

	return 1;
}


/////////////////////////////////////////////////////////////////////////////
// COpenGL message handlers

int COpenGL::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// 设置当前的绘图像素格式
	MySetPixelFormat(::GetDC(m_hWnd));

	// 创建绘图描述表
	hdc = ::GetDC(m_hWnd);
	// 创建渲染描述表
	hglrc = wglCreateContext(hdc);
	// 使绘图描述表为当前调用现程的当前绘图描述表 
	wglMakeCurrent(hdc, hglrc);	
	return 0;
}

void COpenGL::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//调用OpenGL绘图函数进行图形绘制
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除颜色缓存和深度缓存

    s+=0.005;
    if(s>1.0)
		s=0.1;
	step = step + 1.0;
    if (step > 360.0)
		step = step - 360.0;
    glPushMatrix();
	glScalef(s,s,s);
    glRotatef(step,0.0,1.0,0.0);
    glRotatef(step,0.0,0.0,1.0);
  	glRotatef(step,1.0,0.0,0.0);
    DrawColorBox();
    glPopMatrix();
    glFlush();

	SwapBuffers(hdc);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void COpenGL::DrawColorBox(void)
{
	GLfloat  p1[]={0.5,-0.5,-0.5}, p2[]={0.5,0.5,-0.5},
                p3[]={0.5,0.5,0.5},   p4[]={0.5,-0.5,0.5},
                p5[]={-0.5,-0.5,0.5}, p6[]={-0.5,0.5,0.5},
                p7[]={-0.5,0.5,-0.5}, p8[]={-0.5,-0.5,-0.5};

	GLfloat  m1[]={1.0,0.0,0.0},	m2[]={-1.0,0.0,0.0},
				m3[]={0.0,1.0,0.0},	m4[]={0.0,-1.0,0.0},
				m5[]={0.0,0.0,1.0},	m6[]={0.0,0.0,-1.0};

   	
	GLfloat  c1[]={0.0,0.0,1.0},  c2[]={0.0,1.0,1.0},
                c3[]={1.0,1.0,1.0},  c4[]={1.0,0.0,1.0},
                c5[]={1.0,0.0,0.0},  c6[]={1.0,1.0,0.0},
                c7[]={0.0,1.0,0.0},  c8[]={1.0,1.0,1.0};
              
 	
 	  glBegin (GL_QUADS);	//绘制多个四边形
        
		  glColor3fv(c1);
         glNormal3fv(m1);
        glVertex3fv(p1);
		  glColor3fv(c2);
        glVertex3fv(p2);
		  glColor3fv(c3);
        glVertex3fv(p3);
		  glColor3fv(c4);
        glVertex3fv(p4);

		  glColor3fv(c5);
         glNormal3fv(m5);
        glVertex3fv(p5);
		  glColor3fv(c6);
        glVertex3fv(p6);
		  glColor3fv(c7);
        glVertex3fv(p7);
		  glColor3fv(c8);
        glVertex3fv(p8);

		  glColor3fv(c5);
         glNormal3fv(m3);
        glVertex3fv(p5);
		  glColor3fv(c6);
        glVertex3fv(p6);
		  glColor3fv(c3);
        glVertex3fv(p3);
		  glColor3fv(c4);
        glVertex3fv(p4);

		  glColor3fv(c1);
         glNormal3fv(m4);
        glVertex3fv(p1);
		  glColor3fv(c2);
        glVertex3fv(p2);
		  glColor3fv(c7);
        glVertex3fv(p7);
		  glColor3fv(c8);
        glVertex3fv(p8);

		  glColor3fv(c2);
         glNormal3fv(m5);
        glVertex3fv(p2);
		  glColor3fv(c3);
        glVertex3fv(p3);
		  glColor3fv(c6);
        glVertex3fv(p6);
		  glColor3fv(c7);
        glVertex3fv(p7);

		  glColor3fv(c1);
         glNormal3fv(m6);
        glVertex3fv(p1);
		  glColor3fv(c4);
        glVertex3fv(p4);
		  glColor3fv(c5);
        glVertex3fv(p5);
		  glColor3fv(c8);
        glVertex3fv(p8);

	  glEnd();


}
