/*
 * Esfera.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: francisco
 */

#include "esfera.h"
#include "contorno.h"

Esfera::Esfera() {
	// TODO Auto-generated constructor stub

}

Esfera::~Esfera() {
	// TODO Auto-generated destructor stub
}

void Esfera::render(){
	Vector3D c=this->getColor();
	Vector3D p=this->getP();
	glPushMatrix();
	 glColor3f(c.getX(),c.getY(),c.getZ());
     glTranslatef(p.getX(),p.getY(),p.getZ());
     glutSolidSphere(getR(),10,10);
	glPopMatrix();
}
inline Contorno *Esfera::getContorno(){
	return new Contorno(getP(),getR());
}
inline bool Esfera::colision(Solido *s){
	Contorno *c=s->getContorno();
	return c->colision(this);
}


