#ifndef LIGHT_H
#define LIGHT_H

#if defined(__APPLE__) && defined(__MACH__)
    #include<openGL/gl.h>
    #include <openGL/glu.h>
#else

#include<GL/gl.h>
#include <GL/glu.h>

#endif // defined

#include <vector>

using std::vector;

enum Light_Type
{
    LIGHT_SPOT,
    LIGHT_POINT,
    LIGHT_DIRECTIONAL

};


class Light
{
    public:
        Light(Light_Type lightType);
        ~Light();

        static int numLights;                   // total numbers of light
        static vector<int> avaliableLights;
        static vector<Light*> lights;

        static void Initialize(void);
        void setVisible(bool visible = true);
        void setDiffuse(float r, float g, float b, float a);
        void setAmbient(float r, float g, float b, float a);
        void setSpecular(float r, float g, float b, float a);
        void setLightType(Light_Type type);
        void setPosition(float x, float y, float z);
        void setSpotDirection(float x, float y, float z);
        void setCutOff(float value);        // in degrees
        void setExponenet(float value);
        void setAttenuat(float constant, float linear, float quadratic);
        int getLightNum(void);
        void updateLight(void);

    private:
        GLfloat position[4];
        GLfloat diffuse[4];
        GLfloat ambient[4];
        GLfloat specular[4];
        GLfloat spotDirection[4];

        float cutoff;
        float exponent;             // for spot light

        bool visible;
        int lightType;
        int lightNum;

};

#endif // LIGHT_H
