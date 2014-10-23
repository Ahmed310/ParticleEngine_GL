#include "Slider.h"

const int tickSize  = 5 ;

Slider::Slider(string lable, float minV, float maxV, int xPos, int yPos, int width, int height )
:        Control(xPos, yPos, width, height)
{
    defaultV        = 0.0f;
    current         = NULL;
    this->minV      = minV;
    this->maxV      = maxV;
    this->lable     = lable;
    dragging        = false;
}

void Slider::setValue(float *value)
{
    current     = value;

    if(current)
        defaultV    = *value;
}

bool Slider::updateControl(MouseState &state)
{
    Control::updateControl(state);

    int x = state.x;
    int y = state.y;

    if(inside)
    {
        if(state.LeftButtonDown)
        {
            dragging    = true;
        }

        if(state.RightButtonDown)
        {
            *current    = defaultV;
        }
    }

    if(!state.LeftButtonDown)
        dragging    = false;
    if(dragging)
    {
        *current    = (float) ( x - posX) / (float) width * (maxV - minV) + minV;

        if(*current > maxV)
            *current    = maxV;
        else if(*current < minV)
            *current    = minV;

    }

    return dragging;
}
void Slider::drawControl()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);

    glColor4f(0.7f, 0.7f, 0.7f, 0.8f);

    glBegin(GL_QUADS);
        glVertex2d(posX + width,    posY);
        glVertex2d(posX        ,    posY);
        glVertex2d(posX        ,    posY + height);
        glVertex2d(posX + width,    posY + height);
    glEnd();

    if(inside)
    {
        glColor4f(0.2f, 0.2f, 0.7f, 0.8f);
        glLineWidth(2.0f);
    }
    else
    {
        glColor4f(0.2f, 0.2f, 0.7f, 0.5f);
        glLineWidth(1.0f);
    }

    glBegin(GL_LINE_STRIP);
        glVertex2d(posX + width,    posY);
        glVertex2d(posX        ,    posY);
        glVertex2d(posX        ,    posY + height);
        glVertex2d(posX + width,    posY + height);
        glVertex2d(posX + width,    posY);
    glEnd();

    int currentX = (int)(*current - minV)/ (maxV - minV) * (width - tickSize) + posX;

    glColor4f(0.3f, 0.3f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2d(currentX + tickSize,    posY);
        glVertex2d(currentX           ,    posY);
        glVertex2d(currentX           ,    posY + height);
        glVertex2d(currentX + tickSize,    posY + height);
    glEnd();

    glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
    iGLEngine->drawText(posX + 2, posY + 2, lable.data());

}
string Slider::getType()
{
    return "slider";
}
