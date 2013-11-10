//
//  World.h
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef World_H
#define World_H

#include "GlutHeader.h"


#include "Explorer.h"
#include "Gold.h"
#include "Wumpus.h"
#include "Cell.h"
#include "Arrow.h"
#include "Texture.h"


#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <thread>

enum endResult {END_WUMPUS,END_GOLD,END_PIT,OK};
void display();

class World{

public:
    void init(int gridSize);
    void draw();
    endResult checkEndOfGame();
    int getPoint();
    void throwArrow();
    void move(int angle);
    const int SMALL=5;
    const int MEDIUM=10;
    const int LARGE=15;

    
    
private:
    Wumpus wumpus;
    Explorer explorer;
    Gold gold;
    std::vector< std::vector<Cell> > children;
    int points;
    const float pitProbability= 0.2;
    int gridSize;
    void setPoints(int pointsIn);
    void animateExplorer();
    void setStenchyCells();
    void animateArrow();
    void setBreezyCells();
    void setGlitteryCells();
    bool checkWumpusInLine();
    bool isInLimits(int coord);
    const int SMALL_POINTS=50;
    const int MEDIUM_POINTS=100;
    const int LARGE_POINTS=150;
    bool isMoveValid(int angle);
    void gameOver(endResult result);
    void displayGameOver();
    endResult stateOfGame;
    Arrow arrow;
    Texture texture;


    
};

#endif /* defined(__Wumpus__World__) */
