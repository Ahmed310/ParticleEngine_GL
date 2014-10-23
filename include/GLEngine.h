#ifndef GLENGINE_H
#define GLENGINE_H

#if defined(__APPLE__) && defined(__MACH__)
    #include<openGL/gl.h>
    #include <openGL/glu.h>
#else

    #include<GL/gl.h>
    #include <GL/glu.h>

#endif // defined

#define iGLEngine GLEngine::getEngine()

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <stdarg.h>
#include <cstdarg>
#include "Texture.h"
#include "Light.h"

class GLEngine
{
    public:
        GLEngine();
        ~GLEngine();

        static GLvoid Uninitialize();
        static GLEngine* getEngine();
        GLvoid Initialize(GLint width, GLint height);

        // Methods for Text
        GLvoid buildTextureFont();
        GLvoid drawText(GLint x, GLint y, const char* text, ...);
        GLuint getTextWidth(const char* text);
        GLuint getTextHeight(const char *text);

    private:
        GLint fontBase;
        Texture *fontTexture;
};

#endif // GLENGINE_H
