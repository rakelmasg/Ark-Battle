/*
 * Juego.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: raquel
 */

#include "juego.h"

Juego::Juego() {
	// TODO Auto-generated constructor stub
}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
}

void Juego::moverNave(char dir) {   //Recibe un char (u=arriba,d=abajo,r=derecha,l=izquierda)
	Vector3D vel = this->getVelNave();    //Obtenemos el vector de velocidad de la nave
	float velY = vel.getY(), velX = vel.getX(), velZ = vel.getZ();  //Tomamos sus componentes
	float angle = 0.4f*PI / 180.0f;  //Angulo de rotación
	switch (dir) {
	case 'u': //UP
		vel.setY(velY*cos(angle) - velZ*sin(angle));  //Realiza rotaciones con los angulos de euler
		vel.setZ(velY*sin(angle) + velZ*cos(angle));
		break;
	case 'd': //DOWN
		angle = -angle;   //Misma rotación en la direccion contraria
		vel.setY(velY*cos(angle) - velZ*sin(angle));
		vel.setZ(velY*sin(angle) + velZ*cos(angle));
		break;
	case 'r': //RIGHT
		angle = -angle;
		vel.setX(velX*cos(angle) + velZ*sin(angle));
		vel.setZ(-velX*sin(angle) + velZ*cos(angle));
		break;
	case 'l': //LEFT
		vel.setX(velX*cos(angle) + velZ*sin(angle));
		vel.setZ(-velX*sin(angle) + velZ*cos(angle));
		break;
	}
	this->setVelNave(vel);
}

void Juego::disparar() {	   //Función de disparo
	Esfera *bala;
	Vector3D vel = this->getVelNave();  //Tomamos el vector de velocidad de la nave, que nos dirá la dirección de disparo.
	Vector3D pos = this->getPosNave();  //Posición de la nave desde donde sale la bala.
	vel.normalize();  //Se normaliza la velocidad, solo queremosla dirección.
	pos = pos + vel*5.5;  //Indicamos origen, direccion de disparo y la velocidad (mas rápida que la de la nave.)
	vel = vel * 25;
	bala = new Esfera(Vector3D(0, 0, 0), 0.3f);     //Creamos la bala
	bala->setV(vel);  //Le pasamos el valor de velocidad
	bala->setP(pos);  //Le pasamos su posicion
	bala->setColor(Vector3D(0.8f, 0.05f, 1.75f)); //Color de la bala
	e.add(bala);
}


void Juego::addNave(string path) {     //Función para añadir la nave
	string nombre("ufo.obj"); //Modelo de nave
	Modelo *nave = new Modelo(path + "OBJS/" + nombre);
	nave->setP(Vector3D(0, 0, 90));   //Fijamos posicion de la nave
	nave->setColor(Vector3D(0.27f, 0.5f, 0.45f)); //Fijamos color (azul grisáceo)
	nave->setV(Vector3D(0, 0, -10));  //Fijamos vector de velocidad
	e.add(nave);  //La añadimos a la escena
}

void Juego::addEnemy(string path, int posX, int posZ) {    //Función para añadir enemigos
	string nombre("navemala.obj");    //Modelo de nave enemiga
									  //string nombre("nave4.obj");
	Modelo *m;
	int y = rand() % 200; //NUMERO RANDOM para luego dar su posicion
	m = new Modelo(path + "OBJS/" + nombre);
	m->setColor(Vector3D(0.482f, 0.03f, 0.03f));     //Color de la nave (roja)
	m->setP(Vector3D(-99.0f + posX, -99.0f + y, -99.0f + posZ)); //Posicion
	m->setV(Vector3D(0, 0, 10));  //Vector de velocidad
	e.add(m);
}

void Juego::addObject(string path, int posX, int posZ) {   //Función para añadir asteroides
	string nombre("asteroide2.obj");  //Modelo de asteroide
	Modelo *m;
	int y = rand() % 200; //NUMERO RANDOM para luego dar su posicon
	m = new Modelo(path + "OBJS/" + nombre);
	m->setColor(Vector3D(0.5, 0.5, 0.5)); //Color gris
	m->setP(Vector3D(-99.0f + posX, -99.0f + y, -99.0f + posZ));   //posiciones
	m->setV(Vector3D(0, 0, 8));   //Vector de velocidad
	e.add(m); //Se añade a la escena
}

void Juego::cargarNivel(string path) {    //Funcion para cargar el nivel
	char cadena[120]; //cadena donde se guardan las filas de enemigos
	char numero[20];  //cadena donde se guarda el numero de nivel actual
	sprintf(numero, "%d", nivel);
	ifstream level(path + "levels/level" + numero + ".txt");  //cargamos el fichero correspondiente
	int j = 0;    //axiliar para calcular distancia en Z
	while (!level.eof()) {    //mientras no se llegue al final del fichero se lee
		j++;
		level >> cadena; //leemos la fila de enemigos
		for (int i = 0; i < 120; i++) {  //recoremos cada columna de la fila
			switch (cadena[i]) {    //añadimos un asteroide en la posicion indicada
			case '1':  //ASTEROIDE
				addObject(path, i * 5, j * 5);    //Añadimos una nave enemiga en la posición indicada
				break;
			case '2':  //NAVE ENEMIGA
				addEnemy(path, i * 5, j * 5);//Añadimos una nave enemiga en la posicion indicada
				break;

			}
		}
	}
	level.close();
}

void Juego::crearLimites() {
	Solido *p;
	p = new PlanoY(-100, 100); //suelo
	e.addLimite(p);
	p = new PlanoY(100, 100); //Techo
	e.addLimite(p);
	p = new PlanoX(-100, 100);  //izquierda
	e.addLimite(p);
	p = new PlanoX(100, 100); //Derecha
	e.addLimite(p);
	p = new PlanoZ(-100, 100);  //Delante
	e.addLimite(p);
	p = new PlanoZ(100, 100);  //Detras
	e.addLimite(p);
}