#pragma once
#define piconst acos(-1)

class GLRenderer
{
public:
    GLRenderer(void);
    virtual ~GLRenderer(void);

    bool CreateGLContext(CDC* pDC);
    void PrepareScene(CDC* pDC);
    void Reshape(CDC* pDC, int w, int h);
    void DrawScene(CDC* pDC);
    void DestroyScene(CDC* pDC);

    void DrawThorus(double R, double r);
    void RotateView(int x, int y);
    UINT LoadTexture(char* fileName);
    void SetThorusMat();
    void RotateThorus(double L);


protected:
    HGLRC m_hrc;
    int rotX;
    int rotY;
};

