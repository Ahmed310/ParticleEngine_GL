#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"
#include "GLEngine.h"

#include <list>
using std::list;

class Particle
{
    public:
        Particle(int id);
        void Update(long time);

    public:
        int             id;

        Vector3         color;
        Vector3         position;
        Vector3         velocity;
        Vector3         accleration;
        Vector3         rotation;

        float           life;
        float           totalLife;
        float           alpha;
        float           size;
        float           bounciness;
        bool            active;

};

#endif // PARTICLE_H
