#pragma once
class GLMaterial
{
public:
	GLMaterial();
	GLMaterial(float* ambient, float* diffuse, float* specular, float* emission, float shininess);
	virtual ~GLMaterial();

	void SelectFront(void);
	void SelectBack(void);

	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetEmission(float r, float g, float b, float a);
	void SetShininess(float s);
	void Select();

protected:
	float* m_vAmbient;
	float* m_vDiffuse;
	float* m_vSpecular;
	float* m_vEmission;
	float m_fShininess;

};

