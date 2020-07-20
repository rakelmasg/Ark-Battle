/*
 * contorno.cpp
 *
 *  Created on: Nov 7, 2015
 *      Author: francisco
 */

#include "contorno.h"

Contorno::~Contorno() {
	// TODO Auto-generated destructor stub
}

bool Contorno::colision(Plano *pl){
	Vector3D vn(pl->getA(),pl->getB(),pl->getC());
	return fabs(vn*p-pl->getD())<r;
}
bool Contorno::colision(Esfera *e){
	Vector3D pe=e->getP();
	float re=e->getR();
	Vector3D vd=pe-p;
	float l=vd.length();
	return l<r+re;
}
bool Contorno::colision(Cubo *c){
	Vector3D pc=c->getP();
	float rc=c->getS();
	Vector3D vd=pc-p;
	float l=vd.length();
	return l<r+rc;
}

//Comprobamos si hay colision con el contorno, tomamos su profundidad
bool Contorno::colision(Modelo *m) {
	Vector3D pe = m->getP();
	float rm = m->getProfundo()/2.0f;
	Vector3D vd = pe - p;
	float l = vd.length();
	return l<r + rm;
}
