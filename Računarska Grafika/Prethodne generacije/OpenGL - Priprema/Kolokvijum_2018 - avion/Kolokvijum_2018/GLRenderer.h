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

    UINT LoadTexture(char* fileName);
    void DrawTriangle(float d1, float d2, float rep);
    void DrawShip();
    void RotateView(int xAngle, int yAngle);
    void DrawSpaceCube(double a);
    void ToggleLight();


protected:
    HGLRC m_hrc;
    UINT shipTex;
    UINT spaceTex[6];
    float pi;
    int xRotAngle;
    int yRotAngle;
    bool lightOn;
};

