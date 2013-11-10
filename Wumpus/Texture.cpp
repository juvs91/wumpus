//
//  texture.cpp
//  Wumpus
//
//  Created by juvs on 4/30/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#include "Texture.h"
#include "Image.h"


//Makes the image into a texture, and returns the id of the texture
void Texture::loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}

 void Texture::init(){
    int i=0;
    //glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE); ///Users/mariaroque/Imagenes
    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(10, texName); //Make room for our texture
    Image* image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/alivewumpus.bmp");//wumpus esta vivo
    loadTexture(image,i++);
    
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/deadwumpus.bmp");//wumpus muesrto
    loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/olor.bmp");
     loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/brisa.bmp");
     loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/oro.bmp");
     loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/brisa_olor.bmp");//brisa y olor
    loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/brisa_oro.bmp");//brisa y oro
    loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/olor_oro.bmp");//olor y oro 
    loadTexture(image,i++);
    image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/3colores.bmp");//hay olor brisa y oro
    loadTexture(image,i++);
     image = loadBMP("/Users/usuario/Desktop/graficas/Wumpus/Wumpus/archBmp/happyFace.bmp");//hay olor brisa y oro
     loadTexture(image,i++);
     

    delete image;
}


GLuint Texture::getTexName(int k){
    return texName[k];
}

