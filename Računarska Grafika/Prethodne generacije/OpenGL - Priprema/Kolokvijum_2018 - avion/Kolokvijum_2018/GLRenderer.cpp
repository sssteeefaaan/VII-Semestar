#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
    pi = acos(-1);
    xRotAngle = 0;
    yRotAngle = 0;
    lightOn = false;
}

GLRenderer::~GLRenderer(void)
{
}

bool GLRenderer::CreateGLContext(CDC* pDC)
{
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

    if (nPixelFormat == 0) return false;

    BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

    if (!bResult) return false;

    m_hrc = wglCreateContext(pDC->m_hDC);

    if (!m_hrc) return false;

    return true;
}

void GLRenderer::PrepareScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); 
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    shipTex = LoadTexture(".\\Resources\\ShipT1.png");
    spaceTex[0] = LoadTexture(".\\Resources\\front.jpg");
    spaceTex[1] = LoadTexture(".\\Resources\\left.jpg");
    spaceTex[2] = LoadTexture(".\\Resources\\right.jpg");
    spaceTex[3] = LoadTexture(".\\Resources\\back.jpg");
    spaceTex[4] = LoadTexture(".\\Resources\\top.jpg");
    spaceTex[5] = LoadTexture(".\\Resources\\bot.jpg");

    glEnable(GL_TEXTURE_2D);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC* pDC, int w, int h)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (double)w / (double)h, 0.1, 100);
    //gluLookAt(5.00, 5.00, 12.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    //glEnable(GL_TEXTURE_2D);

    glRotatef(xRotAngle, 1.0, 0.0, 0.0);
    glRotatef(yRotAngle, 0.0, 1.0, 0.0);

    glBindTexture(GL_TEXTURE_2D, spaceTex[1]);
    DrawSpaceCube(1.0);
    glPopMatrix();


    glEnable(GL_DEPTH_TEST);


    glTranslatef(0, 0, -10.0);
    glRotatef(xRotAngle, 1.0, 0.0, 0.0);
    glRotatef(yRotAngle, 0.0, 1.0, 0.0);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
    }
    glEnd();
    glEnable(GL_TEXTURE_2D);

    float light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightPosition[] = { -1.0, 0.0, 1.0, 0.0 };

    if (lightOn)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    float d3 = sqrt(5.8 * 5.8 + 2.15 * 2.15);
    glTranslatef(-d3 / 2, 0.0, 0.0);

    DrawShip();

    glFlush();
    SwapBuffers(pDC->m_hDC);
    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(1, &shipTex);
    glDeleteTextures(6, spaceTex);

    wglMakeCurrent(NULL, NULL);
    if (m_hrc)
    {
        wglDeleteContext(m_hrc);
        m_hrc = NULL;
    }
}

UINT GLRenderer::LoadTexture(char* fileName)
{
    UINT texId;
    DImage img;

    img.Load(CString(fileName));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &texId);

    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
    return texId;
}

void GLRenderer::DrawTriangle(float d1, float d2, float rep)
{

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0, 1.0, 1.0);

        float d3 = sqrt(d2 * d2 + d1 * d1);
        float sine = d2 / d3;
        float cosine = d1 / d3;
        float x = d1 * sine;
        float y = d1 * cosine;
        float normX = x / d3;
        float normY = y / d3;


        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.5 * rep, rep);
        glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f((0.5 + normX) * rep, rep - (normY * rep));
        glVertex3f(d1, 0.0, 0.0);
        glTexCoord2f(0.5 * rep, 0.0);
        glVertex3f(d1, d2, 0.0);
    }
    glEnd();
}

void GLRenderer::DrawShip()
{
    float d1 = 5.8, d2 = 2.15, rep = 3;
    float angle = atan(d2 / d1);
    glBindTexture(GL_TEXTURE_2D, shipTex);

    glPushMatrix();
    glRotatef(-4.75, 0.0, 1.0, 0.0);
    glRotatef(13, 1.0, 0.0, 0.0);
    glRotatef(-angle * (180 / pi), 0.0, 0.0, 1.0);
    DrawTriangle(d1, d2, rep);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    glRotatef(-4.75, 0.0, 1.0, 0.0);
    glRotatef(13, 1.0, 0.0, 0.0);
    glRotatef(-angle * (180 / pi), 0.0, 0.0, 1.0);
    DrawTriangle(d1, d2, rep);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, -1.0, 1.0);
    glRotatef(-4.75, 0.0, 1.0, 0.0);
    glRotatef(13, 1.0, 0.0, 0.0);
    glRotatef(-angle * (180 / pi), 0.0, 0.0, 1.0);
    DrawTriangle(d1, d2, rep);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, -1.0, -1.0);
    glRotatef(-4.75, 0.0, 1.0, 0.0);
    glRotatef(13, 1.0, 0.0, 0.0);
    glRotatef(-angle * (180 / pi), 0.0, 0.0, 1.0);
    DrawTriangle(d1, d2, rep);
    glPopMatrix();


}

void GLRenderer::RotateView(int xAngle, int yAngle)
{
    xRotAngle += xAngle;
    if (xRotAngle > 360)
        xRotAngle -= 360;
    else if (xRotAngle < 0)
        xRotAngle += 360;

    yRotAngle += yAngle;
    if (yRotAngle > 360)
        yRotAngle -= 360;
    else if (yRotAngle < 0)
        yRotAngle += 360;
}

void GLRenderer::DrawSpaceCube(double a)
{
    glBindTexture(GL_TEXTURE_2D, spaceTex[4]);
    glBegin(GL_QUADS);
    {
        //top
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, a / 2, a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, a / 2, -a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, a / 2, a / 2);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, spaceTex[5]);
    glBegin(GL_QUADS);
    {
        //bottom
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, -a / 2, a / 2);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, spaceTex[0]);
    glBegin(GL_QUADS);
    {
        //front
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, a / 2, -a / 2);
    }
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, spaceTex[3]);
    glBegin(GL_QUADS);
    {
        //back
        glTexCoord2f(0.0, 0.0);
        glVertex3f(a / 2, a / 2, a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-a / 2, a / 2, a / 2);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, spaceTex[1]);
    glBegin(GL_QUADS);
    {
        //left
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, a / 2, a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-a / 2, a / 2, -a / 2);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, spaceTex[2]);
    glBegin(GL_QUADS);
    {
        //right
        glTexCoord2f(0.0, 0.0);
        glVertex3f(a / 2, a / 2, -a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, a / 2, a / 2);
    }
    glEnd();
}

void GLRenderer::ToggleLight()
{
    lightOn = !lightOn;
}






