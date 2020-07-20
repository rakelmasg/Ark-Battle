/*
 * Juego.h
 *
 *  Created on: Dec 31, 2015
 *      Author: Raquel Más
 * 
 */

#ifndef JUEGO_H_
#define JUEGO_H_
#include <vector>
#include <math.h>
#include <string>
#include "vector3d.h"
#include "solido.h"
#include "esfera.h"
#include "escena.h"
#include "planoY.h"
#include "planoX.h"
#include "planoZ.h"
#include <fstream>

#define PI 3.14159265f

using namespace std;

class Juego {
private:
	Escena e;  
	bool vivo=true; //True=nave viva, false=game over
	int score=0;   //Inicializamos la puntuación a 0.
	vector<string> niveles = { "Nivel 1", "Nivel 2", "Nivel 3", "Nivel 4","Nivel 5"};    
	int nivel=0;   //Niveles, vamos a tener 5.
public:
	Juego();
	virtual ~Juego();
	
	inline Vector3D getPosNave(){ //Devuelve la posicion de la nave, obtenida de escena.
		Vector3D aux=e.getColisionables().front()->getP();
		return aux;
	}
	
	inline void setPosNave(Vector3D pos){  //Fija la posicion de la nave al valor que metamos.
		e.getColisionables().front()->setP(pos);
	}	
	inline void setVelNave(Vector3D vel){  //Fija la velocidad de la nave al valor que metamos.
		e.getColisionables().front()->setV(vel);
	}	
	inline Vector3D getVelNave(){    //Devuelve la velocidad de la nave
		Vector3D aux =e.getColisionables().front()->getV();
		return aux;
	}
	void moverNave(char dir);
	
	void disparar();

	inline void inicializar(string path) { //Inicia el nivel
		nivel++;  //Pasa de nivel (por eso el nivel se pone en 0, para que al empezar sea Nivel 1)
		e.getColisionables().clear(); //Limpia la escena
		e.getLimites().clear();
		vivo = true; 
		addNave(path);    //Añade la nave
		cargarNivel(path);    //Carca el nivel y los límites
		crearLimites();
	}

	void addNave(string path);

	void addEnemy(string path, int posX, int posZ);

	void addObject(string path, int posX, int posZ);

	void cargarNivel(string path);
	
	void crearLimites();

	inline void render(){
		e.render();
	}
	inline int update(float dt){
		e.update(dt);
		if (!vivo) {			
			nivel = 0;
			return 2; //game over
		}
		else if (e.getColisionables().size() == 1) {
			return 1; //pasar de nivel
		}
			
		return 0; //continuar
	}	
	inline void resuelveColisiones(){  //Colisiones
		int col = e.resuelveColisiones();
		if (col==2) { //colision con la nave principal, Game Over
			vivo = false;
		}
		else if(col==1){
			score += 100;    //Si acertamos con una bala ganamos 100 puntos
		}
	}
	inline char* getScore() {    //Devuelve la puntuacion
		char s[10];
		sprintf(s, "%d", score);
		return s;
	}	
	inline string getNivel() {  //Devuelve el numero del nivel
		return niveles.at(nivel - 1);
	}
	inline void reiniciarJuego() {  //Devuelve el numero del nivel
		score = 0;
		nivel = 0;
		vivo = true;
	}
	
};
#endif /* JUEGO_H_ */
