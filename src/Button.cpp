#include "Button.h"

Button::Button(string lable, int posX, int posY, int width, int height)
:   Control(posX, posY, width, height)
{
    this->lable = lable;
    down        = false;
}

bool Button::updateControl(MouseState &state)
{
    Control::updateControl(state);

    if(inside)
    {
        if(state.LeftButtonDown)
            down = true;
        else if(down)
        {
            down = false;
            return true;
        }
    }
    return false;
}

void Button::drawControl()
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

    glColor4f(0.7f, 0.7f, 0.7f, 1.0f);

    int texX = posX + (width - iGLEngine->getTextWidth(lable.data() )) / 2 ;
    int texY = posY + (height- iGLEngine->getTextHeight(lable.data() ))/ 2 ;

    iGLEngine->drawText(texX, texY, lable.data());
}

string Button::getType()
{
   return "button";
}
