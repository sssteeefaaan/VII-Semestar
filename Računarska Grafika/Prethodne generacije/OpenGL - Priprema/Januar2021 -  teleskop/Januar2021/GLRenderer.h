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

    void RotateScene(int x, int y);
    void DrawCylinder(float r, float h, float nr, float nh, bool axes);
    void DrawTelescope(float r, float h, float nr, float nh);


protected:
    HGLRC m_hrc;
    int xRot, yRot;

public:
    int  angleVer, angleHor, alpha;
    float dVizor, dHidden, dHolder;
};

