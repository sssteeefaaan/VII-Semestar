#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

const double MPI = 3.141592653589793238463;

GLRenderer::GLRenderer(void)
{
    pi = acos(-1);
   
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

    envTex = LoadTexture(".\\Resources\\env.png");
    brickTex = LoadTexture(".\\Resources\\brick.png");

    xRotAngle = 0;
    yRotAngle = 0;
    paddleRotAngle = 0;

    glEnable(GL_TEXTURE_2D);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC* pDC, int w, int h)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (double)w / (double)h, 0.1, 100);
    //gluLookAt(4.00, 5.00, 8.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glDisable(GL_LIGHTING);

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

    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glRotatef(xRotAngle, 1.0, 0.0, 0.0);
    glRotatef(yRotAngle, 0.0, 1.0, 0.0);
    DrawCube(1.0);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glBindTexture(GL_TEXTURE_2D, brickTex); //pogledaj jos malo ovaj deo
    glTranslatef(0, 0, -20);
    glRotatef(xRotAngle, 1.0, 0.0, 0.0);
    glRotatef(yRotAngle, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    DrawTube(2.5, 3.5, 10, 32);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0.0, 5.0, 0.0);
    DrawCone(3.8, 2, 32);
    glTranslatef(0.0, 0.0, 3.8);

    glRotatef(paddleRotAngle, 0.0, 0.0, 1.0);
    DrawPaddle(8, 1.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    DrawPaddle(8, 1.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    DrawPaddle(8, 1.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    DrawPaddle(8, 1.5);
    glEnable(GL_TEXTURE_2D);

    glFlush();
    SwapBuffers(pDC->m_hDC);
    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(1, &envTex);
    glDeleteTextures(1, &brickTex);

    wglMakeCurrent(NULL, NULL);
    if (m_hrc)
    {
        wglDeleteContext(m_hrc);
        m_hrc = NULL;
    }
}

UINT GLRenderer::LoadTexture(char* fileName)
{
    UINT texID;
    DImage img;
    img.Load(CString(fileName));
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());
    return texID;
}

void GLRenderer::DrawCube(double a)
{
    glBindTexture(GL_TEXTURE_2D, envTex);
    glColor3f(1.0, 1.0, 1.0);
    float quarter = 1.0 / 4.0;
    float third = 1.0 / 3.0;

    glBegin(GL_QUAD_STRIP); //10 tacke za 4 dela kocke
    {
        glTexCoord2f(0.0, third);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(0.0, 2 * third);
        glVertex3f(-a / 2, a / 2, a / 2);
        glTexCoord2f(quarter, third);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(quarter, 2 * third);
        glVertex3f(-a / 2, -a / 2, a / 2);

        glTexCoord2f(2 * quarter, third);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(2 * quarter, 2 * third);
        glVertex3f(a / 2, -a / 2, a / 2);
        glTexCoord2f(3 * quarter, third);
        glVertex3f(a / 2, a / 2, -a / 2);
        glTexCoord2f(3 * quarter, 2 * third);
        glVertex3f(a / 2, a / 2, a / 2);

        glTexCoord2f(1.0, third);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(1.0, 2 * third);
        glVertex3f(-a / 2, a / 2, a / 2);
    }
    glEnd();

    glBegin(GL_QUADS); //8 tacke za 2 dela kocke (gore i dole, da je ovde QUAD_STRIP, bile bi 3 strane definisanek
    {
        glTexCoord2f(quarter, 0.0);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(quarter, third);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(2 * quarter, third);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(2 * quarter, 0.0);
        glVertex3f(a / 2, a / 2, -a / 2);

        glTexCoord2f(quarter, 2 * third);
        glVertex3f(-a / 2, -a / 2, a / 2);
        glTexCoord2f(quarter, 1.0);
        glVertex3f(-a / 2, a / 2, a / 2);
        glTexCoord2f(2 * quarter, 1.0);
        glVertex3f(a / 2, a / 2, a / 2);
        glTexCoord2f(2 * quarter, 2 * third);
        glVertex3f(a / 2, -a / 2, a / 2);
    }
    glEnd();
}

void GLRenderer::DrawTube(double r1, double r2, double h, int n)
{
    glBegin(GL_QUAD_STRIP);
    {
        float texPart = 1.0 / (float)n; // kad imamo n segmenata nekog tela
        float angleStep = (2 * pi) / (float)n;  //kad nam treba neki ugao, okrugli objekat 
        float currAngle = 0;
        float y1 = h / 2, y2 = -h / 2;
        for (int i = 0; i <= n; i++)
        {
            float x1 = r1 * cos(currAngle);
            float z1 = r1 * sin(currAngle);
            float x2 = r2 * cos(currAngle);
            float z2 = r2 * sin(currAngle);

            float rDiff = r2 - r1;// ove dve pisem  da bih nasla ny i nr (normale)
            float L = sqrt(h * h + rDiff * rDiff);
            float ny = rDiff / L;
            float nr = h / L;
            float nx = nr * cos(currAngle);
            float nz = nr * sin(currAngle);

            glNormal3f(nx, ny, nz);

            glTexCoord2f(i * texPart, 0.0);
            glVertex3f(x1, y1, z1);

            glTexCoord2f(i * texPart, 1.0);
            glVertex3f(x2, y2, z2);

            currAngle += angleStep;
        }
    }
    glEnd();
}

void GLRenderer::DrawCone2(double r, double h, int n)
{
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, h, 0.0);
    for (int angle = 0; angle <= 360 ; angle += 360 / n) { //zasto ne iscrtava pun krug????
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(angle, 1.0);
        glVertex3f(r * cos(toRad(angle)), 0, r * sin(toRad(angle)));
    }
    glEnd();
}

float GLRenderer::toRad(float angle)
{
    return (angle * MPI) / 180;
}
void GLRenderer::DrawCone(double r, double h, int n)
{
    glBegin(GL_TRIANGLES);
    {
        float currAngle = 0;
        float angleStep = (2 * pi) / n;
        float L = sqrt(h * h + r * r);
        float ny = r / L;
        float nr = h / L;

        for (int i = 0; i < n; i++)
        {
            float nx = nr * cos(currAngle + angleStep / 2); // zasto + angleStep / 2??
            float nz = nr * sin(currAngle + angleStep / 2); // zato sto se vrh trougla nalazi na sredini stranie, tj. izmedju tacaka koje su definisane dole
            glNormal3f(nx, ny, nz);
            glVertex3f(0, h, 0);

            nx = nr * cos(currAngle); // normale racunamo sa nr; prva tacka bez rastojanja
            nz = nr * sin(currAngle);
            glNormal3f(nx, ny, nz);
            float x = r * cos(currAngle); //a koordinate sa obicno r 
            float z = r * sin(currAngle);
            glVertex3f(x, 0, z);

            nx = nr * cos(currAngle + angleStep); //druga tacka sa plus rastojanje, tj. ugao
            nz = nr * sin(currAngle + angleStep);
            glNormal3f(nx, ny, nz);
            x = r * cos(currAngle + angleStep);
            z = r * sin(currAngle + angleStep);
            glVertex3f(x, 0, z);

            currAngle += angleStep;
        }
    }
    glEnd();
}

void GLRenderer::DrawPaddle(double length, double width)
{
    glNormal3f(0.0, 0.0, 1.0);
    float xMove = width / 16;
    glBegin(GL_QUADS);
    {
        glVertex3f(0.0 - xMove, 0.0, 0.0);
        glVertex3f(width / 8 - xMove, 0.0, 0.0);
        glVertex3f(width / 8 - xMove, length / 8, 0.0);
        glVertex3f(0.0 - xMove, length / 8, 0.0);

        glVertex3f(0.0 - xMove, length / 8, 0.0);
        glVertex3f(width / 8 - xMove, length / 8, 0.0);
        glVertex3f(width - xMove, 2 * (length / 8), 0.0);
        glVertex3f(0.0 - xMove, 2 * (length / 8), 0.0);

        glVertex3f(0.0 - xMove, 2 * (length / 8), 0.0);
        glVertex3f(width - xMove, 2 * (length / 8), 0.0);
        glVertex3f(width - xMove, length, 0.0);
        glVertex3f(0.0 - xMove, length, 0.0);
    }
    glEnd();
}

void GLRenderer::RotateView(int xAngle, int yAngle)
{
    xRotAngle += xAngle;
    if (xRotAngle > 360)
        xRotAngle -= 360;
    else if (xRotAngle < 0)
        xRotAngle -= 360;

    yRotAngle += yAngle;
    if (yRotAngle > 360)
        yRotAngle -= 360;
    else if (yRotAngle < 0)
        yRotAngle -= 360;
}

void GLRenderer::RotatePaddles(int angle)
{
    paddleRotAngle += angle;
    if (paddleRotAngle > 360)
        paddleRotAngle -= 360;
    else if (paddleRotAngle < 0)
        paddleRotAngle += 360;
}






