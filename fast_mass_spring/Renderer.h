/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
#include "Shader.h"
#include "RenderAttach.h"


class Renderer {
protected:
	Shader* program;
	ProgramInput* input;
	unsigned int n_elements;

public:
	Renderer();

	void setShader(Shader* program);
	void setProgramInput(ProgramInput* input);
	void setElementCount(unsigned int n_elements);

	void draw();
};