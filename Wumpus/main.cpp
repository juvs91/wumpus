//
//  main.cpp
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//


#include "GlutHeader.h"

#include "World.h"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>



World world;
int gridSize;

double anguloParaDibujar(){
    switch (gridSize) {
        case 5:
            return 13;
            
        case 10:
            return 7.2;
            
        case 15:
            return 5;
        default:
            return 0;
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
    
    
    /*
    
    
   //Iluminacion
   
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   GLfloat ambientLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
   
   GLfloat directedLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
   GLfloat directedLightPos[] = {0.0f, 0.0f, 1.0f, 1.0f};
   glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
   glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
   //termina iluminacion
    
    */
    
    

    glPushMatrix();
    //Esta es la unica funcion que cambia para centrar el tablero
    glTranslatef(0.0,1.3*gridSize/15,3.1);
    //Esta funcion se utiliza para que el tablero cubra la pantalla completa
    glRotatef(anguloParaDibujar(), 1, 0, 0);
    world.draw();
    
    
    /*
    
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    
    */
    
    
    
    glPopMatrix();
    glutSwapBuffers();
}







void init(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, gridSize,0, gridSize);
    //Iluminacion
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambientLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    GLfloat directedLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat directedLightPos[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
    //termina iluminacion
    

    glClearColor(0,0,0,1);//DEFINE EL COLOR DEL FONDO DE TU PANTALLA
    world.init(gridSize);
   
    glutPostRedisplay();
}


void keyboard(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_DOWN:
            world.move(270);
            break;
        case GLUT_KEY_UP:
            world.move(90);
            break;
        case GLUT_KEY_RIGHT:
            world.move(0);
            break;
        case GLUT_KEY_LEFT:
            world.move(180);
            break;
     
    }
    glutPostRedisplay();
}

void onMenu(int opcion){
    //switch para seleccionar la opcion del menu 0 para salir , 1 para reiniciar y 2 para lanzar la flecha
    switch (opcion) {
            //Reiniciar el juego en facil
        case 0:
            gridSize=world.SMALL;
            init();
            break;
            
        case 1:
            gridSize=world.MEDIUM;
            init();
            break;
            
        case 2:
            gridSize=world.LARGE;
            init();
            break;
            
        case 3:
            //lanza la flecha
            world.throwArrow();
            break;
            
        case 4:
            exit(0);//sale de la aplicacion
            break;
    }
    glutPostRedisplay();
    
}
void reshape(int w,int h){
    glViewport(0, 0, (GLint)w, (GLint)h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30,(GLfloat)w/(GLfloat)h, 1, 20);
    
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
}




void menu(){
    int menuOpciones, menuDificultad;
    
    menuDificultad= glutCreateMenu(onMenu);
    glutAddMenuEntry("Fácil", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Difícil", 2);
    
    
	menuOpciones = glutCreateMenu(onMenu);
    glutAddSubMenu("Reinicializar",menuDificultad);
    glutAddMenuEntry("Lanzar flecha", 3);
    glutAddMenuEntry("EXIT", 4);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(870,720);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Wumpus");
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);
      glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);
    gridSize=world.SMALL;
    init();//hay que checar el gride size , para escojer el tamaño del grid
  
    

    menu();
    glutMainLoop();
    
    
    
    return 0;
}

