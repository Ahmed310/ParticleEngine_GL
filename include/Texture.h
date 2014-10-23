#ifndef TEXTURE_H
#define TEXTURE_H

#if defined(__APPLE__) && defined(__MACH__)
    #include<openGL/gl.h>
    #include <openGL/glu.h>
#else

    #include<GL/gl.h>
    #include <GL/glu.h>

#endif // defined

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>

using std::string;
using std::vector;
using std::ifstream;


/*
Header[TGA]
Field no.	Length	    Field name	                Description
1	        1 byte	    ID length	                Length of the image ID field
2	        1 byte	    Color map type	            Whether a color map is included
3	        1 byte	    Image type	                Compression and color types
4	        5 bytes	    Color map specification	    Describes the color map
5	        10 bytes	Image specification	        Image dimensions and format
*/

struct TGA_Header
{
    GLubyte ID_Length;
    GLubyte ColorMapType;
    GLubyte ImageType;
    GLubyte ColorMapSpecification[5];
    GLshort xOrigin;
    GLshort yOrigin;
    GLshort ImageWidth;
    GLshort ImageHeight;
    GLubyte PixelDepth;
    GLubyte ImageDescriptor;
};

class Texture
{
    public:
        Texture(string filename, string name);
        ~Texture();
    public:
        unsigned char*  imageData;
        unsigned int    bpp;
        unsigned int    width;
        unsigned int    height;
        unsigned int    texID;
        string          name;
        static vector<Texture*> textures;    // keep track of all textures created
    private:
        bool loadTGA(string filename);
        bool creatTexture(unsigned char* imageData, unsigned int width, unsigned int height, int type);

};


#endif // TEXTURE_H
