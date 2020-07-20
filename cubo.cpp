/*
 * cubo.cpp
 *
 *  Created on: Nov 6, 2015
 *      Author: francisco
 */

#include "cubo.h"
#include "contorno.h"

Cubo::Cubo() {
	// TODO Auto-generated constructor stub

}

Cubo::~Cubo() {
	// TODO Auto-generated destructor stub
}
void Cubo::render(){
	Vector3D c=this->getColor();
	Vector3D p=this->getP();
	glPushMatrix();
	 glColor3f(c.getX(),c.getY(),c.getZ());
     glTranslatef(p.getX(),p.getY(),p.getZ());
     glutSolidCube(getS());
	glPopMatrix();
}
inline Contorno *Cubo::getContorno(){
	return new Contorno(this->getP(),this->getS());
}
inline bool Cubo::colision(Solido *s){
	Contorno *c=s->getContorno();
	return c->colision(this);
}
