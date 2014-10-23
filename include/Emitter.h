#ifndef EMITTER_H
#define EMITTER_H

#include "Particle.h"

class Emitter
{
    public:
        Emitter();
        ~Emitter();
        void Update(long time);
        void setTexture(Texture *texture);
        float frand(float start = 0, float end = 1);


    protected:
        void addParticle();

    public:
        list<Particle*>    particles;
        Texture*           texture;
        long               lastTime;    // elasped last time

        // Attributes
        //=====================================
        float               emmitionRate;
        float               emmitionRadius;
        float               life;
        float               lifeRange;
        float               size;
        float               sizeRange;
        float               saturation;
        float               alpha;
        float               spread;
        float               gravity;

        Vector3             position;
        Vector3             wind;
        Vector3             rotation;
};

#endif // EMITTER_H
