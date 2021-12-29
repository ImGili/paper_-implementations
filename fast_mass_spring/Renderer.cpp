/*
 * @Author: ImGili
 * @Description: 
 */
#include "Renderer.h"

Renderer::Renderer() {}

void Renderer::setShader(Shader* program) {
	this->program = program;
}

void Renderer::setProgramInput(ProgramInput* input) {
	this->input = input;
}

void Renderer::setElementCount(unsigned int n_elements) { this->n_elements = n_elements; }

void Renderer::draw() {
	glBindVertexArray(*input);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, n_elements, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
	glUseProgram(0);
}

