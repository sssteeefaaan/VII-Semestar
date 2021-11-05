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
    
    void DrawRoller(float r, float h, int n);
    void PrepareTextures(CString strTex);
    void DrawFigure(float h, float dx, float alpha, float beta, float dt, CString arTex[]);
    void RotateView(int x, int y);


protected:
    HGLRC m_hrc;
    int xRot;
    int yRot;
};

