//
//  Cell.cpp
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#include "Cell.h"
#include "Image.h"



void Cell::draw(Texture texture){
    
    if (isVisited) {
        //dibujar celda
        glColor4f(1,1,1,1);
        glBegin(GL_QUADS);
            glVertex2d(x,y+1);
            glVertex2d(x, y);
            glVertex2d(x+1,y);
            glVertex2d(x+1, y+1);
        glEnd();
        
        
        //dibuja pit
        if (hasPit) {
            glPushMatrix();
                glTranslated(x+.5, y+.5, 0);
                glColor4f(0, 0, 0, 1);
                drawCircle(.4);
            glPopMatrix();
        }
        else{
            int texNumber;
            
            if(hasBreeze){
                if(hasGlitter){
                    if(hasStench) texNumber=8 ;//brisa, brillo y olor
                    else texNumber= 6;//brisa, brillo y no olor
                }else{
                    if(hasStench) texNumber=5 ;//brisa, no brillo y olor
                    else texNumber=3 ;//brisa, no brillo y no olor
                }
            }
            else{
                if(hasGlitter){
                    if(hasStench) texNumber= 7;//no brisa, brillo y olor
                    else texNumber= 4;//no brisa, brillo y no olor
                }else{
                    if(hasStench) texNumber= 2;//no brisa, no brillo y olor
                    else texNumber= -1;//no brisa, no brillo y no olor
                }
            }
            if (texNumber>=0) {
                glColor3f(1, 1, 1);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,texture.getTexName(texNumber));
                
                //Asignarle a las coordenadas.
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f( x, y, 0 );
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f( x+1, y,  0 );
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(  x+1, y+1,  0 );
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(  x, y+1, 0 );
                glEnd();
                
                glDisable(GL_TEXTURE_2D);
   
            }
            
            
            
        }
    
    }
    else{
        //dibujar un cuadro cafe
        glColor4f(.2549,.1960,.0007,1);
        glBegin(GL_QUADS);
            glVertex2d(x,y+1);
            glVertex2d(x, y);
            glVertex2d(x+1,y);
            glVertex2d(x+1, y+1);

        glEnd();
    }
}
void Cell::setVisited(bool val){
    isVisited=val;
}
void Cell::setBreeze(bool val){
    hasBreeze=val;
}
void Cell::setStench(bool val){
    hasStench=val;
}
void Cell::init(const float pitProbability,int xIn,int yIn){
    setVisited(false); //si lo pones en false el mapa se pone negro y se esconde todo
    //setVisited(true);
    setBreeze(false);
    setStench(false);
    setGlitter(false);
    setPosition(xIn, yIn);
    setPit(pitProbability);
    
}
void Cell::setPit(const float pitProbability){
    float random=((rand()%100)+1)/100.0;
    if (random<pitProbability) {
        hasPit=true;
    }
    else{
        hasPit=false;
    }
}
bool Cell::getPit(){
    return hasPit;
}
void Cell::setPosition(int xIn,int yIn){
    x=xIn;
    y=yIn;
}
bool Cell::getVisited(){
    return isVisited;
}

void Cell::noPit(){
    hasPit=false;
}

void Cell::setGlitter(bool val){
    hasGlitter=val;
}

void Cell::drawCircle(float radio){
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(0,0,0);
    for (int angle=1; angle<=360;angle++) {
        glVertex2f(sin(angle)*radio, cos(angle)*radio);
    }
    glEnd();
}

