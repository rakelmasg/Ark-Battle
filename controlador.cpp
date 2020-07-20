
#include <string>
#include <GL/glut.h>
#include "juego.h"
#include <string.h>

GLint ancho=1500; //ancho ventana
GLint alto=1500; //alto ventana
int lastX=-1, lastY=-1; //coordenadas raton
float dt=0.01f; //tiempo transcurrido
Juego jg; //objeto juego
Vector3D view(0.0f,3.0f,20.0f); //vector de la camara
string extra = ""; //muestra el game over
int state; //controla el flujo del programa
Vector3D color(0.0f,0.0f,0.0f); //NEGRO
bool vista3 = true; //vista en tercera persona/primera persona si false



void volverMenu(int i) {
	state = 0; 
	jg.reiniciarJuego();
}

void empezarNivel(int i) {
	state = 1; //inicia el juego 
}

void drawString(string s) //funcion para pintar texto por ventana
{
	unsigned int i;
	for (i = 0; i<s.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void drawMenu() {    //Menu principal
	glDisable(GL_LIGHTING);

	glColor3f(0.0f, 0.0f, 1.0f);//AZUL
	glRasterPos3f(-5.3f, 6.8f, 0.0f); //Funcion para decir la posicion del texto
	drawString("------------");
	glRasterPos3f(-5.5f, 6.0f, 0.0f);
	drawString("| ARK BATTLE |"); //Titulo del juego
	glRasterPos3f(-5.3f, 5.4f, 0.0f); 
	drawString("------------");

	glColor3f(1.0f, 1.0f, 1.0f);//BLANCO
	glRasterPos3f(-6.5f, 3.0f, 0.0f);
	drawString("Pulse E para empezar");//empezar

	glColor3f(1.0f, 1.0f, 1.0f);//BLANCO
	glRasterPos3f(-6.0f, 1.0f, 0.0f);
	drawString("Pulse Esc para salir");//Opción de salir

	glEnable(GL_LIGHTING);
}

void drawNivel(string nivel) {   //Escena donde nos indica el nivel actual
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);   //BLANCO
	drawString(nivel); //Pintar el numero de nivel
	glRasterPos3f(-2, 5, 0);   //Posicion del texto
	glEnable(GL_LIGHTING);

}

void drawScore() {  //Puntuacion indicada al lado de la nave
	glDisable(GL_LIGHTING);
	glColor3f(0.8f, 0.05f, 1.0f);
	drawString(jg.getScore()); //Pintar la puntuacion
	glRasterPos3f(jg.getPosNave().getX() + 4, jg.getPosNave().getY() + 4, jg.getPosNave().getZ() + 4); //Posicion relativa a la nave
	glEnable(GL_LIGHTING);
}

void drawFinal() {   //Pantalla de game over
	glDisable(GL_LIGHTING);
	glColor3f(color.getX(), color.getY(), color.getZ()); //color extra
	glRasterPos3f(-4.5f, 1.0f, 0.0f);
	drawString(extra); //game over/win

	glColor3f(1.0f, 1.0f, 0.0f); //color extra
	glRasterPos3f(-2.0f, -3.0f, 0.0f);
	drawString(jg.getScore()); //puntuacion final
	glEnable(GL_LIGHTING);
}
void displayMe(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //
	if(state==1){ //Cuando el juego se está ejecutando
		Vector3D vel = jg.getVelNave();//Tomamos vector velocidad de la nave
		if (!vista3) { //camara en primera persona
			view = Vector3D(jg.getPosNave().getX() + vel.getX() / 4, (jg.getPosNave().getY()) + vel.getY() / 4, (jg.getPosNave().getZ()) + vel.getZ() / 4);
		}
		else { //camara en tercera persona
			view = Vector3D(jg.getPosNave().getX() - vel.getX(), (jg.getPosNave().getY()) - vel.getY() + 10.0f, (jg.getPosNave().getZ()) - vel.getZ());
		}
		//La posicion de la cámara se indica en "view" y es en relacion de la nave y definida por el contrario del vector velocidad,
        //de esta manera siempre la vemos desde atrás y podemos apuntar en el centro. 
        //La cámara esta inclinada un poco hacia arriba para que la dirección de las balas no sea la misma que el lookat y no nos tape la nave de ver donde disparamos.
        //Si la nave sube la cámara esta mas cerca y al bajar al contrario para dar dicha sensacion y que no parezca que ni bajamos ni subimos.
		//gluLookAt(view.getX(), view.getY(), view.getZ(), jg.getPosNave().getX(), jg.getPosNave().getY(), jg.getPosNave().getZ(), 0.0, 2, 0.0);
		gluLookAt(view.getX(), view.getY(), view.getZ(), jg.getPosNave().getX()+ vel.getX(), jg.getPosNave().getY()+vel.getY(), jg.getPosNave().getZ()+ vel.getZ(), 0.0, 2, 0.0);
		//Definimos el lookAt -> Posicion cámara, hacia dónde mira(posición nave), vector up siempre hacia arriba en todos los casos.
		drawScore();  //Pintamos la puntuación en todo momento
		jg.render();
	}else if(state==0) {   //si el juego no se está ejecutando
		gluLookAt(0, 3, 20, 0, 0, 0, 0, 1, 0);
		drawMenu(); // pintar el menú
	}
	else if(state==2)  {
		gluLookAt(0, 3, 20, 0, 0, 0, 0, 1, 0);
		drawNivel(jg.getNivel()); //Pintar el nivel
	}
	else {
		gluLookAt(0, 3, 20, 0, 0, 0, 0, 1, 0);
		drawFinal();
	}
	

    glutSwapBuffers();
}
void ratonControl(int x, int y) {   //Función para movernos con el ratón, esta en relacion a las zonas de la pantalla
	if(state==1){
		if (x > (ancho / 2)) {    //Derecha
		if (x > (ancho / 2 + 2 * ancho / 6)) {    //Ratón en el borde=girar más rapido
			jg.moverNave('r');
			jg.moverNave('r');
		}
		else if (x > (ancho / 2 + ancho / 6)) //Antes del borde=girar mas lento
			jg.moverNave('r');
	}
		else if (x < (ancho / 2)) {   //Izquierda
		if (x < ancho / 2 - 2 * ancho / 6) {
			jg.moverNave('l');
			jg.moverNave('l');
		}
		else if (x < (ancho / 2 - ancho / 6))
		{
			jg.moverNave('l');
		}

	}
		if (y >(alto / 2)) {  //Arriba
		if (y >(alto / 2 + alto / 6)) //Aqui no se puede girar mas rapido hacia arriba o abajo
			jg.moverNave('u');
	}
		if (y < (alto / 2)) {//Abajo
		if (y <(alto / 2 - alto / 6))
			jg.moverNave('d');
	}
	}
}
void init (void) 
{
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor (0.0,0.0,0.0,0.0);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, (GLfloat)width/(GLfloat)height, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

void idle()
{
     ratonControl(lastX, lastY); //actualizamos las coordenadas del raton
    displayMe(); //funcion de pintado
    if (state==1) { //si el juego se esta ejecutando
        int estadoJuego = jg.update(dt); //actualizamos las posiciones y comprobamos el estado de la partida
        if (estadoJuego ==0) { //si el juego prosigue
            jg.resuelveColisiones(); //se resuelven las colisiones entre objetos
            }
        else if(estadoJuego ==1) {//si no hay mas enemigos
            if(jg.getNivel()!="Nivel 5"){//si no es el ultimo nivel
                jg.inicializar("./juego/");//cargamos el siguiente nivel
                state = 2;//mostramos el texto con el numero nivel
                glutTimerFunc(1500, empezarNivel, 0); //pasado el tiempo empieza el nivel
                }
            else { //si se han superado todos los niveles sin morir
				color = Vector3D(0.0f, 1.0f, 0.0f);
				extra = "YOU WIN!"; //indicamos que ha perdido				
				state = 3; //mostramos la pantalla de fin
				glutTimerFunc(2500, volverMenu, 0); //volvemos a cargar el menu indicando 
            }
   
        }else { //si nos han alcanzado, la nave esta muerta
			color = Vector3D(1.0f,0.0f,0.0f);
            extra = "GAME OVER"; //indicamos que ha perdido			
            state = 3; //mostramos la pantalla de fin
			glutTimerFunc(2500, volverMenu, 0); //volvemos a cargar el menu indicando 
        }
    }
}

//FUNCION PARA CONTROL DEL RATON
void keyPressed (unsigned char key, int x, int y) {
	switch(key)
    {
	case 'E':
	case 'e':
		if (state == 0) {
			jg.inicializar("./juego/");
			state = 2;
			glutTimerFunc(1500, empezarNivel, 0);
			//pantalla nivel (1)
		}
		break;
	case 'V':
	case 'v':
		if (state == 1) { //cambiar tercera persona a primera
			vista3 = !vista3;
		}
		break;
	case 32:  //espacio
		if (state==1)
			jg.disparar();
		break;
    case 27:   // escape
		exit(0);
		break;
    }
}
void motionControler(int x, int y) {    //Cada vez que se mueva el ratón nos da su posicion, no incluimos aqui la función por que si el ratón no se mueve no se lleva a cabo. ratonControl() se ejecuta en todo momento y se actualiza gracias a motionControler
	lastX=x;
	lastY=y;
}

int main(int argc, char** argv)
{
	state = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(ancho, alto);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ARK BATTLE");
    init();
    glutDisplayFunc(displayMe);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed); 
    glutPassiveMotionFunc(motionControler); 
    glutMainLoop();
    return 0;
}

