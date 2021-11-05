#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
    xRotationAngle = 0;
    yRotationAngle = 0;
    zoom = -10;
    moonYRotationAngle = 0;
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
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    T[0] = LoadTexture(".\\Resources\\TSC0.jpg");
    T[1] = LoadTexture(".\\Resources\\TSC1.jpg");
    T[2] = LoadTexture(".\\Resources\\TSC2.jpg");
    T[3] = LoadTexture(".\\Resources\\TSC3.jpg");
    T[4] = LoadTexture(".\\Resources\\TSC4.jpg");
    T[5] = LoadTexture(".\\Resources\\TSC5.jpg");

    S[0] = LoadTexture(".\\Resources\\S0.jpg");
    S[1] = LoadTexture(".\\Resources\\S1.jpg");
    S[2] = LoadTexture(".\\Resources\\S2.jpg");
    S[3] = LoadTexture(".\\Resources\\S3.jpg");
    S[4] = LoadTexture(".\\Resources\\S4.jpg");
    S[5] = LoadTexture(".\\Resources\\S5.jpg");

    M[0] = LoadTexture(".\\Resources\\M0.jpg");
    M[1] = LoadTexture(".\\Resources\\M1.jpg");
    M[2] = LoadTexture(".\\Resources\\M2.jpg");
    M[3] = LoadTexture(".\\Resources\\M3.jpg");
    M[4] = LoadTexture(".\\Resources\\M4.jpg");
    M[5] = LoadTexture(".\\Resources\\M5.jpg");

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
    //gluLookAt(0.00, 0.00, 8.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glRotatef(xRotationAngle, 1.0, 0.0, 0.0);
    glRotatef(yRotationAngle, 0.0, 1.0, 0.0);
    DrawSpace(1.0, 20);
    glPopMatrix();

    if (lightOn)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

    float light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

    glEnable(GL_DEPTH_TEST);
    glTranslatef(0, 0, zoom);
    glRotatef(xRotationAngle, 1.0, 0.0, 0.0);
    glRotatef(yRotationAngle, 0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    DrawEarth(3, 20);
    glTranslatef(-50, 0, 0);
    glRotatef(moonYRotationAngle, 0.0, 1.0, 0.0);
    DrawMoon(1.0, 20);

    glFlush();
    SwapBuffers(pDC->m_hDC);
    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(6, T);
    glDeleteTextures(6, S);
    glDeleteTextures(6, M);

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
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());

    return texId;
}

void GLRenderer::DrawPatch(double R, int n)
{
    double step = (double)2 / (double)n;
    double paramY = 1.0;
    for (int i = 0; i < n; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        {
            double paramX = -1.0;
            double paramYlower = paramY - step;
            for (int j = 0; j <= n; j++)
            {
                //paramX += j * step;
                double phi = atan(paramX);
                double theta1 = atan(paramY * cos(phi));

                double x1 = R * cos(theta1) * sin(phi);
                double z1 = R * cos(theta1) * cos(phi);
                double y1 = R * sin(theta1);

                glNormal3f(x1 / R, y1 / R, z1 / R);
                float yTex = (paramY + 1.0) / 2.0;
                glTexCoord2f((paramX + 1.0) / 2.0, 1.0 - yTex);
                glVertex3f(x1, y1, z1);


                phi = atan(paramX);
                double theta2 = atan(paramYlower * cos(phi));

                double x2 = R * cos(theta2) * sin(phi);
                double z2 = R * cos(theta2) * cos(phi);
                double y2 = R * sin(theta2);

                glNormal3f(x2 / R, y2 / R, z2 / R);
                yTex = (paramYlower + 1.0) / 2.0;
                glTexCoord2f((paramX + 1.0) / 2.0, 1.0 - yTex);
                glVertex3f(x2, y2, z2);

                paramX += step;
            }
        }
        glEnd();
        paramY -= step;
    }
}


void GLRenderer::DrawPatch2(double R, int n)
{
    double TexRazmak = (double)2 / double(n);
   
    double y = 1.0;

    
    for (int i = 0; i < n; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        {
            double x = -1.0;
            for (int j = 0; j <= n; j++)
            {

                double phi = atan(x);
                double theta = atan(y * cos(phi));

                double xd = R * cos(theta) * sin(phi);
                double yd = R * cos(theta) * cos(phi);
                double zd = R * sin(theta);

                glNormal3f(xd / R, yd / R, zd / R);
                glTexCoord2f((x + 1.0) / 2.0, 1.0-((y + 1.0) / 2.0));
                glVertex3f(xd, yd, yd);

                phi = atan(x);
                double theta2 = atan((y - TexRazmak) * cos(phi));

                double x2 = R * cos(theta2) * sin(phi);
                double z2 = R * cos(theta2) * cos(phi);
                double y2 = R * sin(theta2);

                y= (y-TexRazmak + 1.0) / 2.0;
                glNormal3f(x2 / R, y2 / R, z2 / R);
                glTexCoord2f((x + 1.0) / 2.0, 1.0-y);
                glVertex3f(x2, y2, y2);

                x += TexRazmak;

            }
        }
         glEnd();
        y -= TexRazmak;
    }


}

void GLRenderer::DrawEarth(double R, int tes)
{
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotatef(i * 90, 0.0, 1.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, T[i]);
        DrawPatch(R, tes);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glRotatef((1 + i * 2) * 90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, T[5 - i]);
        DrawPatch(R, tes);
        glPopMatrix();
    }
}

void GLRenderer::DrawMoon(double R, int tes)
{
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotatef(i * 90, 0.0, 1.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, M[i]);
        DrawPatch(R, tes);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glRotatef((1 + i * 2) * 90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, M[5 - i]);
        DrawPatch(R, tes);
        glPopMatrix();
    }
}

void GLRenderer::DrawSpace(double R, int tes)
{
    glDisable(GL_CULL_FACE);
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotatef(i * 90, 0.0, 1.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, S[i]);
        DrawPatch(R, tes);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glRotatef((1 + i * 2) * 90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, S[5 - i]);
        DrawPatch(R, tes);
        glPopMatrix();
    }
    glEnable(GL_CULL_FACE);
}

void GLRenderer::RotateView(int xAngle, int yAngle)
{
    xRotationAngle += xAngle;
    if (xRotationAngle < 0)
        xRotationAngle += 360;
    else if (xRotationAngle > 360)
        xRotationAngle -= 360;

    yRotationAngle += yAngle;
    if (yRotationAngle < 0)
        yRotationAngle += 360;
    else if (yRotationAngle > 360)
        yRotationAngle -= 360;
}

void GLRenderer::Zoom(float zoomAmount)
{
    zoom += zoomAmount;
    if (zoom > -7.0)
        zoom = -7.0;
}

void GLRenderer::RotateMoon(int yAngle)
{
    moonYRotationAngle += yAngle;
    if (moonYRotationAngle < 0)
        moonYRotationAngle += 360;
    else if (moonYRotationAngle > 360)
        moonYRotationAngle -= 360;
}






