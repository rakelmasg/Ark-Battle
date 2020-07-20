/*
 * planoZ.cpp
 *
 *  Created on: Nov 7, 2015
 *      Author: francisco
 */

#include "planoZ.h"

PlanoZ::~PlanoZ() {
	// TODO Auto-generated destructor stub
}
/* ESTA COMENTADO POR QUE NO QUEREMOS QUE SALGAN LOS PLANOS
void PlanoZ::render() {
	Vector3D c = this->getColor();
	glColor3f(c.getX(), c.getY(), c.getZ());
	glBegin(GL_POLYGON);
	glVertex3f(-s, -s, p);
	glVertex3f(s, -s, p);
	glVertex3f(s, s, p);
	glVertex3f(-s, s, p);
	glEnd();
}
*/
void PlanoZ::render() {
}
