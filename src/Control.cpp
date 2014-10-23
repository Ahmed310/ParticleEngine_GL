#include "Control.h"

list<Control *> Control::controls;

Control::Control(int positionX, int positionY, int width, int height)
{
    controls.push_back(this);

    setPosition(positionX,positionY);
    setSize(width, height);
}
Control:: ~Control()
{
    controls.remove(this);
}

bool Control::updateControl(MouseState &state)
{
    int x   = state.x;
    int y   = state.y;

    inside  = false;

    if(x >= posX && x <= posX + width && y >= posY && y <= posY + height)
        inside = true;

    return false;
}

void Control::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}
void Control::setSize(int width, int height)
{
    this->width  = width;
    this->height = height;
}

int Control::getWidth()
{
    return width;
}

int Control::getHeight()
{
    return height;
}

Control *addControl(Control *control)
{
    static int lastX = 5;
    static int lastY = 5;

    control->setPosition(lastX,lastY);
    lastY += control->getHeight() + 5;

    return control;
}
