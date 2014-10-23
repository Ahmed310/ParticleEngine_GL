#include "Emitter.h"

Emitter::Emitter()
{
    //ctor
    texture         = NUL;
    emmitionRate    = 30.0f;
    emmitionRadius  = 0.0f;

    life            = 2.0f;
    lifeRange       = 0.5f;

    size            = 5.0f;
    sizeRange       = 2.0f;

    saturation      = 1.0f;
    alpha           = 0.5f;

    spread          = 1.0f;
    gravity         = 0.0f;
}

Emitter::~Emitter()
{
    for(list<Particle *>::iterator it = particles.begin(); it != particles.end() ; it++)
        delete(*it);
}

void Emitter::Update(long time)
{
    if(!texture)
        return;

    int numEmission = (int)((float)(time - lastTime) / 1000.0f * emmitionRate );

    for(int i = 0 ; i < numEmission ; i++)
        addParticle();

    if(numEmission > 0)
            lastTime = time;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->texID);

     for(list<Particle *>::iterator it = particles.begin(); it != particles.end() ; it++)
     {
         Particle *p = (*it);

         p->accleration.y = -gravity;
         p->accleration  += wind;
         p->alpha         = alpha;
         p->rotation      = rotation;

         p->Update(time);

         if(!p->active)
         {
             delete p;
             list<Particle*>::iterator tmp = it--;
             particles.erase(tmp);
         }
     }

     glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

}

void Emitter::setTexture(Texture *texture)
{
    this->texture       = texture;
}

void Emitter::addParticle()
{
    Particle * p = new Particle((int)particles.size());

    float r        = frand() * saturation + (1 - saturation);
    float g        = frand() * saturation + (1 - saturation);
    float b        = frand() * saturation + (1 - saturation);

    p->color       = Vector3(r,g,b);
    p->life        = frand(life - lifeRange, life + lifeRange);
    p->totalLife   = p->life;

    p->velocity    = Vector3(frand(-spread, spread), frand(3,20), frand(-spread, spread));
    p->accleration = Vector3(0.0f, -gravity, 0.0f);
    p-size         = frand(size - sizeRange, size + sizeRange);

    p->position.x  = frand(-emmitionRadius, emmitionRadius);
    p->position.z  = frand(-emmitionRadius, emmitionRadius);

    particles.push_back(p);

}

float Emitter::frand(float start, float end)
{
    float num   = (float)rand() / (float)RAND_MAX;

    return (start + (end - start) * num);
}
