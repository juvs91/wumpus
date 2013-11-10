//
//  World.cpp
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//



#include "World.h"
#include <iostream>




void World::init(int gridSizeIn){
    gridSize=gridSizeIn;
    stateOfGame=OK;
    srand(time(NULL));
    

    //inicializar los puntos
    if (gridSizeIn==SMALL) points=SMALL_POINTS;
    if (gridSizeIn==MEDIUM) points=MEDIUM_POINTS;
    if (gridSizeIn==LARGE) points=LARGE_POINTS;

    
    //inicializar el wumpus oro y explorador
    glPushMatrix();
    wumpus.init(gridSize);
    gold.init(gridSize);
    explorer.init();
    arrow.init();
    texture.init();
    
    //asignar los posos con probabilidad y olores y brisa
    children.resize(gridSize);
    for (int row=0; row<gridSize; row++) {
        children[row].resize(gridSize);
        for (int col=0;col<gridSize; col++) {
            children[row][col].init(pitProbability,row,col);
            
        }
    }
    
    //validando condiciones del juego
    children[0][0].setVisited(true);
    children[0][0].noPit();
    children[gold.getX()][gold.getY()].noPit();
    
    
    //pongo las celdas con olor y con brisas
    setStenchyCells();
    setBreezyCells();
    setGlitteryCells();
    glPopMatrix();
}

void World::displayGameOver(){
    //dibujar puntos finales
    std::string gameOver="";
    switch (stateOfGame) {
        case END_GOLD:
            gameOver="Ganaste!!!";
            
            break;
        case END_PIT:
            gameOver="MORISTE! Te caiste al pozo!";
            break;
        case END_WUMPUS:
            gameOver="Te trago el WUMPUS!";
            break;
        default:
            break;
    }

    float centerOfScreen= gridSize/2;
    float halfOfText= (gameOver.length()/2)*.13;
    glColor3f(1, 0, 0);//No esta funcionando para cambiar el color de las letras.
    glRasterPos2f(centerOfScreen-halfOfText,centerOfScreen-.5);
    for (int i=0; i<gameOver.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,gameOver[i]);
    }
    
    
}

void World::draw(){
    
    //llamamos el draw de cada celda
    for (int i=0; i<gridSize; i++) {
        for (int j=0; j<gridSize; j++) {
            children[i][j].draw(texture);
        }
    }
   /*
    //dibujar la cuadricula de tamaño grid size
    glColor3f(0.55, 0.27, 0.07);
    glBegin(GL_LINES);
        for (int i=0; i<=gridSize; i++) {
            glVertex2d(i,0);
            glVertex2d(i, gridSize);
            glVertex2d(0,i);
            glVertex2d(gridSize,i);
        }
    glEnd();
 */
    
    //llamar el draw de la flecha
    arrow.draw();
    
     //si la celda es visible llamar el draw del wumpus
    if (children[wumpus.getX()][wumpus.getY()].getVisited()) {
        wumpus.draw(texture);
    }
    
     //si la celda es visible llamar el draw del oro
    if (children[gold.getX()][gold.getY()].getVisited()) {
        gold.draw(texture);
    }
    //llamar el draw del explorer
    explorer.draw();
    //dibujar puntos
    glColor3f(1, 0, 0);
    glRasterPos2f(0.1,gridSize-.3 );
    char puntosChar[15];
    sprintf(puntosChar,"Puntos: %d", points);
    std::string puntosStr(puntosChar);
    for (int i=0; i<puntosStr.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,puntosStr[i]);
    }
    
    displayGameOver();
}

endResult World::checkEndOfGame(){
    //se verifica las pocisiones del explorador y se verifica si en esa celda no hay un poso , oro o wumpus
    if (wumpus.getX()==explorer.getX()&&wumpus.getY()==explorer.getY()&&wumpus.getAlive()) {
        return END_WUMPUS;
    }
    if (gold.getX()==explorer.getX()&&gold.getY()==explorer.getY()) {
        return END_GOLD;
    }
    if (children[explorer.getX()][explorer.getY()].getPit()) {
        return END_PIT;
    }
    return OK;
}

void World::gameOver(endResult resultIn){
    //se verifica el resultado de checkEndOfGame si dferente de ok valida los resultados
    stateOfGame=resultIn;
    if (stateOfGame!=OK) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_COLOR_MATERIAL);
        //se acabo el juego
        explorer.setVisible(false);
        //aqui se pone todo el tablero para que se vea todo
        for (int row=0; row<gridSize; row++) {
            for (int col=0;col<gridSize; col++) {
                children[row][col].setVisited(true);
            }
        }
        switch (stateOfGame) {
            case END_PIT:
                setPoints(points - 20);
                break;
            case END_GOLD:
                break;
            case END_WUMPUS:
                setPoints(points - 50);
                break;
            default:
                break;
        }
    }
}


int World::getPoint(){
    return points;
}

void World::throwArrow(){
    if (explorer.getArrow()&&stateOfGame==OK) {
        arrow.setVisible(true);
        explorer.throwArrow();
        setPoints(points-10);
        animateArrow();
        if (checkWumpusInLine()) {
            setPoints(points+10);
            wumpus.killWumpus();
        }
        arrow.setVisible(false);
    }
}

void World::move(int angle){
    //chequeo que no se vallan para atras
    if (stateOfGame==OK) {
        if (isMoveValid(angle)) {
            setPoints(points-1);
            if (explorer.getDirectionAngle()==angle) {
                //requiere movimiento
                animateExplorer();
                //poner la celda visible dependiendo del angulo para donde quiso ir
                
                children[explorer.getX()][explorer.getY()].setVisited(true);
                
                //verifica el fin del juego o mostrar game over
                gameOver(checkEndOfGame());
            }
            else{
                explorer.setDirectionAngle(angle);
            }
        }
    }
}

bool World::isMoveValid(int angle){
    if(fabs(angle-explorer.getDirectionAngle())==180){
        return false;
    }
    if (explorer.getDirectionAngle()==angle) {
        switch (angle) {
            case 0:
                return isInLimits(explorer.getX()+1);
            case 90:
                return isInLimits(explorer.getY()+1);
            case 180:
               return isInLimits(explorer.getX()-1);
            case 270:
                return isInLimits(explorer.getY()-1);
        }
    }
    return true;
}

void World::setPoints(int pointsIn){
    points=pointsIn;
}

void World::animateExplorer(){
    int x=explorer.getX();
    int y=explorer.getY();
    int directionAngle=explorer.getDirectionAngle();
    int numberOfSteps=4;
    float stepSize=0;
    for (int i=1; i<=numberOfSteps; i++) {
        
        //con esto se animara al explorador , hay que trabajarlo
        explorer.setMoveAngles(explorer.getMoveAngles());
        
        //movemos en el tablero edpendiendo de la direccion del angulo
        stepSize= (float)i/numberOfSteps;
        switch (directionAngle) {
            case 0:
                explorer.setPosition(x+stepSize, y);
                break;
            case 90:
                explorer.setPosition(x, y+stepSize);
                break;
            case 180:
                explorer.setPosition(x-stepSize, y);
                break;
            case 270:
                explorer.setPosition(x, y-stepSize);
                break;
        }
    
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/numberOfSteps));
        //glutPostRedisplay();
        display();
    }
    
    //poner posiciones finales del explorer
    switch (directionAngle) {
        case 0:
            explorer.setPosition(x+1, y);
            break;
        case 90:
            explorer.setPosition(x, y+1);
            break;
        case 180:
            explorer.setPosition(x-1, y);
            break;
        case 270:
            explorer.setPosition(x, y-1);
            break;
    }
}

void World::setGlitteryCells(){
    int row=gold.getX();
    int col=gold.getY();
    
    if (isInLimits(row-1)) children[row-1][col].setGlitter(true);
    
    if (isInLimits(row+1)) children[row+1][col].setGlitter(true);
    
    if (isInLimits(col-1)) children[row][col-1].setGlitter(true);
    
    if (isInLimits(col+1)) children[row][col+1].setGlitter(true);

}

void World::setStenchyCells(){
    
    int row=wumpus.getX();
    int col=wumpus.getY();
    
    if (isInLimits(row-1)) children[row-1][col].setStench(true);
    
    if (isInLimits(row+1)) children[row+1][col].setStench(true);
    
    if (isInLimits(col-1)) children[row][col-1].setStench(true);
    
    if (isInLimits(col+1)) children[row][col+1].setStench(true);
}


bool World::isInLimits(int coord){
    return coord>=0&&coord<gridSize;
}

void World::animateArrow(){
    
    arrow.setX(explorer.getX());
    arrow.setY(explorer.getY());
    int i;
    
    
    arrow.setAngle(explorer.getDirectionAngle());
    
    switch (arrow.getAngle()) {
        case 0:
            for (int i=arrow.getX();i<gridSize;i++) {
                arrow.setX(i);
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
            break;
        case 90:
            for (int i=arrow.getY();i<gridSize;i++) {
                arrow.setY(i);
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
            
            break;
        case 180:
            i=arrow.getX();
            std::cout<<i;

            for (int i=arrow.getX();i>=0;i--) {
                arrow.setX(i);
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
            break;
        case 270:
            for (int i=arrow.getY();i>=0;i--) {
                arrow.setY(i);
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }

            break;
    }
    
}



void World::setBreezyCells(){
    for (int row=0; row<gridSize; row++) {
        for (int col=0; col<gridSize; col++) {
            if (children[row][col].getPit()) {
                if (isInLimits(row-1)) children[row-1][col].setBreeze(true);
                
                if (isInLimits(row+1)) children[row+1][col].setBreeze(true);
                
                if (isInLimits(col-1)) children[row][col-1].setBreeze(true);
                
                if (isInLimits(col+1)) children[row][col+1].setBreeze(true);
            }
        }
    }
}

bool World::checkWumpusInLine(){
    switch (explorer.getDirectionAngle()) {
        case 0:
            return explorer.getY()==wumpus.getY()&&wumpus.getX()>explorer.getX();
            break;
        case 90:
            return explorer.getX()==wumpus.getX()&&wumpus.getY()>explorer.getY();
            break;
            
        case 180:
            return explorer.getY()==wumpus.getY()&&wumpus.getX()<explorer.getX();
            break;
            
        case 270:
            return explorer.getX()==wumpus.getX()&&wumpus.getY()<explorer.getY();
            break;
    
    }
    return false;
}