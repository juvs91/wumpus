//
//  Wumpus.h
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef Wumpus_H
#define Wumpus_H

#include "GlutHeader.h"
#include "Texture.h"
//#include "SDL.framework/Headers/SDL.h"
//#include "SDL.framework/Headers/SDL_audio.h"

#import <AudioToolbox/AudioServices.h>


#include <stdlib.h>

class Wumpus{
public:
    void draw(Texture texture);
    void init(int gridSize);
    bool getAlive();
    int getX();
    int getY();
    void killWumpus();
private:
    //CWave wave1,wave2;
    //SDL_AudioSpec fmt;
    std::string soundFile;
    int x;
    int y;
    bool isAlive;
    void yell();
    void generateNewRandomPosition(int gridSize);
    void setAlive();
};
#endif /* defined(__Wumpus__Wumpus__) */
