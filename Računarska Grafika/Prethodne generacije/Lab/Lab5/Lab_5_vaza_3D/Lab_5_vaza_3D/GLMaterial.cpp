#include "pch.h"
#include "GLMaterial.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLMaterial::GLMaterial()
{
	m_vAmbient = new float[4]{ 0.2, 0.2, 0.2, 1.0 };
	m_vDiffuse = new float[4]{ 0.8, 0.8, 0.8, 1.0 };
	m_vEmission = new float[4]{ 0.0, 0.0, 0.0, 1.0 };
	m_vSpecular = new float[4]{ 0.0, 0.0, 0.0, 1.0 };
	m_vShininess = 0.0;
}

GLMaterial::GLMaterial(float* ambient, float* diffuse, float* specular, float* emission, float shininess)
{
	m_vAmbient = new float[4]{ ambient[0], ambient[1], ambient[2], ambient[3] };
	m_vDiffuse = new float[4]{ diffuse[0], diffuse[1], diffuse[2], diffuse[3] };
	m_vEmission = new float[4]{ emission[0], emission[1], emission[2], emission[3] };
	m_vSpecular = new float[4]{ specular[0], specular[1], specular[2], specular[3] };
	m_vShininess = shininess;
}

void GLMaterial::SetAmbient(float* ambient)
{
	m_vAmbient = new float[4]{ ambient[0], ambient[1], ambient[2], ambient[3] };
}

void GLMaterial::SetDiffuse(float* diffuse)
{
	m_vDiffuse = new float[4]{ diffuse[0], diffuse[1], diffuse[2], diffuse[3] };
}

void GLMaterial::SetSpecular(float* specular)
{
	m_vSpecular = new float[4]{ specular[0], specular[1], specular[2], specular[3] };
}

void GLMaterial::SetEmission(float* emission)
{
	m_vEmission = new float[4]{ emission[0], emission[1], emission[2], emission[3] };
}

void GLMaterial::SetShininess(float shininess)
{
	m_vShininess = shininess;
}

void GLMaterial::Select()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_vAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_vDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_vEmission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_vSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_vShininess);
}

GLMaterial::~GLMaterial()
{
	if (m_vAmbient != nullptr)
		delete[] m_vAmbient;

	if (m_vDiffuse != nullptr)
		delete[] m_vDiffuse;

	if (m_vEmission != nullptr)
		delete[] m_vEmission;

	if (m_vSpecular != nullptr)
		delete[] m_vSpecular;
}
