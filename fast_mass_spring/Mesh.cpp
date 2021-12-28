/*
 * @Author: ImGili
 * @Description: 
 */
#include"Mesh.h"
// M E S H /////////////////////////////////////////////////////////////////////////////////////
float* Mesh::vbuff() { return VERTEX_DATA(this); }
float* Mesh::nbuff() { return NORMAL_DATA(this); }
float* Mesh::tbuff() { return TEXTURE_DATA(this); }
unsigned int* Mesh::ibuff() { return &_ibuff[0]; }
void Mesh::useIBuff(std::vector<unsigned int>& _ibuff) { this->_ibuff = _ibuff; }

unsigned int Mesh::vbuffLen() { return (unsigned int)n_vertices() * 3; }
unsigned int Mesh::nbuffLen() { return (unsigned int)n_vertices() * 3; }
unsigned int Mesh::tbuffLen() { return (unsigned int)n_vertices() * 2; }
unsigned int Mesh::ibuffLen() { return (unsigned int)_ibuff.size(); }
