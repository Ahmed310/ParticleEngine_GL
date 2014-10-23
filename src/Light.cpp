#include "Light.h"

int Light:: numLights;                   // total numbers of light
vector<int> Light:: avaliableLights;
vector<Light*> Light:: lights;

void Light::Initialize(void)
{
    glGetIntegerv(GL_MAX_LIGHTS, &numLights);

    for(int i=0; i < numLights ; i++)
        avaliableLights.push_back(GL_LIGHT0 + i);
}
Light::Light(Light_Type type)
{
    //ctor
    lights.push_back(this);
    if((int)avaliableLights.size() > 0)
    {
        lightNum = avaliableLights[0];
        avaliableLights.erase(avaliableLights.begin()); // remove first
        setVisible(true);
        setLightType(type);
        setPosition(0,0,0);
        setCutOff(45);
        setExponenet(12);
        setSpotDirection(0,1,0);
        setAmbient(0,0,0,1);
        setDiffuse(1,1,1,1);
        setSpecular(1,1,1,1);
        updateLight();

    }
    else
    {
        lightNum = 0;
        setVisible(false);
    }

}

Light::~Light()
{
    //ctor
    if(lightNum != 0)
        avaliableLights.push_back(lightNum);

     for(vector<Light*>::iterator it = lights.begin() ; it != lights.end() ; it++)
     {
         if((*it) == this)
         {
             lights.erase(it);
             break;
         }
     }


}

void Light::setDiffuse(float r, float g, float b, float a)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
    glLightfv(lightNum,GL_DIFFUSE,diffuse);
}
void Light::setAmbient(float r, float g, float b, float a)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
    glLightfv(lightNum,GL_AMBIENT,ambient);
}
void Light::setSpecular(float r, float g, float b, float a)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
    glLightfv(lightNum,GL_SPECULAR,specular);
}
void Light::setLightType(Light_Type type)
{
    lightType = type;
    if(lightType == LIGHT_POINT)
    {
        position[3] = 1.0f;
        setCutOff(180.0f);
    }
    else if(lightType == LIGHT_SPOT)
        position[3] = 1.0f;
    else if(lightType == LIGHT_DIRECTIONAL)
        position[3] = 0.0f;

    updateLight();
}
void Light::setPosition(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;

    glLightfv(lightNum, GL_POSITION, position);
}
void Light::setSpotDirection(float x, float y, float z)
{
    spotDirection[0] = x;
    spotDirection[1] = y;
    spotDirection[2] = z;

    glLightfv(lightNum, GL_SPOT_DIRECTION, spotDirection);
}
void Light::setCutOff(float value)        // in degrees
{
    cutoff = value;
    glLightf(lightNum, GL_SPOT_CUTOFF,cutoff);
}
void Light::setExponenet(float value)
{
    exponent = value;
    glLightf(lightNum,GL_SPOT_EXPONENT, exponent);
}
void Light::setAttenuat(float constant, float linear, float quadratic)
{
    glLightf(lightNum,GL_CONSTANT_ATTENUATION,constant);
    glLightf(lightNum,GL_LINEAR_ATTENUATION,linear);
    glLightf(lightNum, GL_QUADRATIC_ATTENUATION, quadratic);
}
int Light::getLightNum(void)
{
    return lightNum;
}
void Light::updateLight(void)
{
    glLightfv(lightNum, GL_POSITION, position);
    glLightfv(lightNum,GL_SPOT_DIRECTION,spotDirection);
}
void Light::setVisible(bool visible)
{
    this->visible = visible;
    if(visible)
        glEnable(lightNum);
    else
        glDisable(lightNum);
}
