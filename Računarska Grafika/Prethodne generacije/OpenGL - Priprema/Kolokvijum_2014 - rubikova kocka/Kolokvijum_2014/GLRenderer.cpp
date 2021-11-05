#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
    xRotAngle = 0;
    yRotAngle = 0;
    for (int i = 0; i < 3; i++)
        cubeRot[i] = 0;
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

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC* pDC, int w, int h)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (double)w / (double)h, 0.1, 100);
    float a = 10 * sqrt(2);

    gluLookAt(0.00, a, a, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);

    float a = 10 * sqrt(2);

    float position1[] = { 0.0, a, a, 1.0 }; //svetlo GL_LIGHT1 se nalazi na mestu posmatrača, usmereno u pravcu pogleda i stalno prati posmatrača.
    float direction1[] = { 0.0, -1.0, -1.0}; // ne znam bas sta znaci ovo?
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    

    glRotatef(xRotAngle, 1.0, 0.0, 0.0); //postavljamo ovo uvek u DrawScene, da bismo mogli da rotiramo scenu
    glRotatef(yRotAngle, 0.0, 1.0, 0.0);

    glBegin(GL_LINES);
    {
        //glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);

        //glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);

        //glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
    }
    glEnd();

    float position0[] = { 5.0, 20.0, 0.0, 1.0 }; //svetlo GL_LIGHT0 se nalazi fiksno na koordinatama (5.0, 20.0, 0.0)
    glLightfv(GL_LIGHT0, GL_POSITION, position0);

    SetWhiteLight();
    LoadTexture();


    DrawRubikCube(2, 3);

    glFlush();
    SwapBuffers(pDC->m_hDC);
    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(1, &texId);

    wglMakeCurrent(NULL, NULL);
    if (m_hrc)
    {
        wglDeleteContext(m_hrc);
        m_hrc = NULL;
    }
}

void GLRenderer::DrawCube(float a)
{
    float third = 1.0 / 3.0;
    glBegin(GL_QUADS);
    {
        //front
        //glColor3f(1.0, 0.0, 0.0);
        SetMaterial(1.0, 0.0, 0.0);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, a / 2, a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, a / 2, a / 2);

        //right
        //glColor3f(0.0, 0.0, 1.0);
        SetMaterial(0.0, 0.0, 1.0);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, a / 2, a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, a / 2, -a / 2);

        //back
        //glColor3f(1.0, 0.5, 0.0);
        SetMaterial(1.0, 0.5, 0.0);
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(a / 2, a / 2, -a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-a / 2, a / 2, -a / 2);

        //left
        //glColor3f(0.0, 1.0, 0.0);
        SetMaterial(0.0, 1.0, 0.0);
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-a / 2, -a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-a / 2, a / 2, a / 2);

        //top
        //glColor3f(1.0, 1.0, 1.0);
        SetMaterial(1.0, 1.0, 1.0);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, a / 2, -a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, a / 2, a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, a / 2, a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, a / 2, -a / 2);

        //bottom
        //glColor3f(1.0, 1.0, 0.0);
        SetMaterial(1.0, 1.0, 0.0);
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-a / 2, -a / 2, a / 2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(a / 2, -a / 2, -a / 2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(a / 2, -a / 2, a / 2);
    }
    glEnd();
}

void GLRenderer::DrawRubikCube(double a, int count)
{
    float gap = a / 20; //kocke su razmaknute za 5% duzine, zato kroz 20
    float offset = a + gap; // stranica duzine a plus razmak izmedju
    int cntHalf = count / 2;   //celi deo ne razumem????
    int cntMod = count % 2;
    float translation = cntHalf;
    translation -= (cntMod == 0) ? 0.5 : 0;
    translation *= offset;
    float texPart = 1.0 / (float)count; //1 delimo sa ukupnim brojem, isto kao kod nekog kruznog dela, oznaci deo celine za teksturu
    glPushMatrix();

    for (int i = 0; i < count; i++) //jedna kolona u kocki
    {
        for (int j = 0; j < count; j++) //vrsta 
        {
            for (int k = 0; k < count; k++) //kolona 
            {
                glPushMatrix();
                glTranslatef(-translation, -translation, -translation); //ako ne napisemo ovo, koord. poc. ce nam bude u prvoj kockici, dole levo, a ne u centralnoj
                glTranslatef(i * offset, j * offset, k * offset);
                DrawCube(a);
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}

void GLRenderer::SetWhiteLight()
{
    float globalAmbient[] = { 0.5, 0.5, 0.5, 1.0 }; //povećati globalno ambijentalno svetlo na 0.5
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //postaviti lokalnog posmatrača

    float ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); //light0 tackasti izvor
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);//light1 usmereni izvor
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, 2);
    glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 13);
}

void GLRenderer::SetMaterial(float r, float g, float b)
{
    float diffuse[] = { r, g, b, 1.0 }; //difuziona i spekularna boja definisane su (r,g,b) vrednostima
    float specular[] = { r, g, b, 1.0 };
    float ambient[] = { r / 5, g / 5, b / 5, 1.0 }; //ambietalna je 20% difuzione (jedna petina)


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //postavljamo ove tri komponente za materijal za glMaterialfv, a svetlo sa glLightfv
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMateriali(GL_FRONT, GL_SHININESS, 64); //sjajnost je 64
}

void GLRenderer::LoadTexture()
{
    UINT texID;
    DImage img;
    img.Load(CString(".\\Resources\\OpenGL.bmp"));
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());
    texId = texID;
}

void GLRenderer::RotateScene(int xAngle, int yAngle)
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

void GLRenderer::RotateCube(int num, int angle)
{
    cubeRot[num - 1] += angle;
    if (cubeRot[num - 1] > 360)
        cubeRot[num - 1] -= 360;
    else if (cubeRot[num - 1] < 0)
        cubeRot[num - 1] += 360;
}






