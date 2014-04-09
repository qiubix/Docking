//Materials.cpp
//...

#include "Materials.h"

void metalMaterial()
{
  glDisable(GL_BLEND);
  /* Material */
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  metalAm);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  metalDi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, metalSp);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, metalSh);
}

void fireMaterial()
{
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  fireAm);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  fireDi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fireSp);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fireSh);
}

void plasmaMaterial(int frame_no)
{
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  plasmaAm);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  plasmaDi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, plasmaSp);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, plasmaSh);
  glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, changeDiffuse(frame_no));
}

float changeDiffuse(int frame_no){
	float min = 0.7;
	float zakres = (1 - min)/2;


	float dif = min+zakres + sin((float) frame_no)*zakres;

	return dif;

}