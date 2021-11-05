#pragma once
class GLMaterial
{
private:
    float* m_vAmbient;
    float* m_vDiffuse;
    float* m_vSpecular;
    float* m_vEmission;
    float m_vShininess;

public:
    GLMaterial();
    GLMaterial(float* ambient, float* diffuse, float* specular, float* emission, float shininess);
    void SetAmbient(float* ambient);
    void SetDiffuse(float* diffuse);
    void SetSpecular(float* specular);
    void SetEmission(float* emission);
    void SetShininess(float shininess);
    void Select();
    ~GLMaterial();
};

