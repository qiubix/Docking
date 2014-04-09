//Materials.h
//...

#ifndef MATERIALS_H
#define MATERIALS_H

//#include <GL/GLUT.H>
#include "GLUT.H"
#include <iostream>

/* Materials:
 * Am = Ambient
 * Di = Diffuse
 * Sp = Specular
 * Sh = Shininess
 */


const GLfloat metalAm[4] = { 0.31, 0.31, 0.31, 1.00 };
const GLfloat metalDi[4] = { 0.57, 0.57, 0.57, 1.00 };
const GLfloat metalSp[4] = { 0.90, 0.90, 0.90, 1.00 };
const GLfloat metalSh = 27.8;

const GLfloat fireAm[4] = { 0.00, 0.65, 0.94, 0.00 };
const GLfloat fireDi[4] = { 1.00, 1.00, 1.00, 0.50 };
const GLfloat fireSp[4] = { 0.00, 0.00, 0.00, 0.00 };
const GLfloat fireSh = 0;

const GLfloat plasmaAm[4] = { 0.00, 0.65, 0.94, 0.00 };
const GLfloat plasmaDi[4] = { 1.00, 1.00, 1.00, 0.50 };
const GLfloat plasmaSp[4] = { 0.00, 0.00, 0.00, 0.00 };
const GLfloat plasmaSh = 30;

void metalMaterial();
void fireMaterial();
void plasmaMaterial(int);
float changeDiffuse(int);

#endif//MATERIALS_H