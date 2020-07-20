 /*
 * Escena.h
 *
 *  Created on: Oct 5, 2015
 *      Author: francisco
 */

#ifndef ESCENA_H_
#define ESCENA_H_
#include <vector>
#include "solido.h"
#include "modelo.h"

class Escena: public Solido {
	vector<Solido*> colisionables;
	vector<Solido*> limites;
public:
	Escena();
	virtual ~Escena();
	void add(Solido *s){
		colisionables.push_back(s);
	}

	void addLimite(Solido *s){
		limites.push_back(s);
	}

	// NOS DEVUELVE LOS COLISIONABLES
	vector<Solido*>& getColisionables(){
		return colisionables;
	}
	//NOS DEVUELVE LOS LIMITES
	vector<Solido*>& getLimites(){
		return limites;
	}
		
	inline void render(){
		for (Solido *r : colisionables) {
			r->render();
		}		
		for (Solido *l : limites) {
			l->render();
		}
	}
	inline void update(float dt){
		for(Solido *s: colisionables)
			s->update(dt);
	}
	//FUNCION PARA RESOLVER COLISIONES
	inline int resuelveColisiones(){
		int i, j=0; //axiliares para acceder conocer las posiciones

		//
		for(Solido *l:limites){
			i = 0;
			for(Solido *s:colisionables){
				if(l->colision(s)){
					if (i != 0) {
						colisionables.erase(colisionables.begin() + i);
						i--;
					}
					else {
						s->setP(s->getP() - s->getV());
					}
				}
				i++;
			}
		}
		for(Solido *m: colisionables){
			i = 0;
			for(Solido *c:colisionables){
				if(c!=m){
					if(m->colision(c)){
						if (j != 0) {
							colisionables.erase(colisionables.begin() + j);
							return 1; //colision normal
						}
						else {
							return 2; //colision con protagonista
						}
						
					}
				}
				i++;
			}
			j++;
		}
		return 0; //no hay colision
	}
	
};

#endif /* ESCENA_H_ */
