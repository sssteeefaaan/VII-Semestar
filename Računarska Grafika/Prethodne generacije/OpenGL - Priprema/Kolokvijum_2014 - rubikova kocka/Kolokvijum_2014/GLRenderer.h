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
    
    void DrawCube(float a);
    void DrawRubikCube(double a, int count);
    void SetWhiteLight();
    void SetMaterial(float r, float g, float b);
    void LoadTexture();
    void RotateScene(int xAngle, int yAngle);
    void RotateCube(int num, int angle);


protected:
    HGLRC m_hrc;
    int xRotAngle;
    int yRotAngle;
    UINT texId;
    int cubeRot[3];
};

