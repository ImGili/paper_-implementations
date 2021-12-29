#pragma once
#include<glad/glad.h>
class ProgramInput
{
private:
	GLuint vbo[4]; // vertex buffer object handles | position, normal, texture, index
	void bufferData(unsigned int index, void* buff, size_t size);
	GLuint handle; // vertex array object handle

public:
	ProgramInput();

	void setPositionData(float* buff, unsigned int len);
	void setNormalData(float* buff, unsigned int len);
	void setTextureData(float* buff, unsigned int len);
	void setIndexData(unsigned int* buff, unsigned int len);

	operator GLuint() const; // cast to GLuint
	~ProgramInput();
};