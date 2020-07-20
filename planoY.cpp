/*
 * planoY.cpp
 *
 *  Created on: Nov 6, 2015
 *      Author: francisco
 */

#include "planoY.h"

PlanoY::~PlanoY() {
	// TODO Auto-generated destructor stub
}
/* ESTA COMENTADO POR QUE NO QUEREMOS QUE SALGAN
void PlanoY::render(){
	Vector3D c=this->getColor();
	glColor3f(c.getX(),c.getY(),c.getZ());
    glBegin(GL_POLYGON);
        glVertex3f(-s, p, -s);
        glVertex3f( s, p, -s);
        glVertex3f( s, p,  s);
        glVertex3f(-s, p,  s);
    glEnd();
}*/
void PlanoY::render() {
}