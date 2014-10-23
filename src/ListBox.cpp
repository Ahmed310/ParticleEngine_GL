#include "ListBox.h"

const int itemHeight  = 18 ;        // height of cell
ListBox::ListBox(int positionX, int positionY, int width, int height )
:   Control(positionX, positionY, width, height)
{
    index = 0 ;
}


void ListBox::addItem(string item)
{
    items.push_back(item);
}

void ListBox::removeItem(int index)
{
    int i = 0;

    for( vector<string>::iterator it = items.begin(); it != items.end() ; it++)
    {
        if(i == index)
        {
            items.erase(it);
            break;
        }
        i++;
    }

    if(index >= (int)items.size())
        index = (int)items.size() -1 ;
}

void ListBox::setCurrent(int index)
{
    this->index = index;
}


int ListBox::getIndex()
{
    return index;
}

int ListBox::getCount()
{
    return (int)items.size();
}

bool ListBox::updateControl(MouseState &state)
{
    Control::updateControl(state);

    int x = state.x;
    int y = state.y;

    if(inside && state.LeftButtonDown)
    {
        int tmpIndex = (y - posY) / itemHeight;

        if(tmpIndex >= 0 && tmpIndex < getCount())
        {
            index = tmpIndex;
            return true;
        }
    }
    return false;
}

void ListBox::drawControl()
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

    if(index >= 0)
    {
        glColor4f(0.3f, 0.3f, 1.0f, 0.5f);
        int currentY = posY + index * itemHeight;

        glBegin(GL_QUADS);
            glVertex2d(posX + width,    currentY);
            glVertex2d(posX        ,    currentY);
            glVertex2d(posX        ,    currentY + itemHeight);
            glVertex2d(posX + width,    currentY + itemHeight);
        glEnd();
    }

    glColor4f(0.7f, 0.7f, 0.7f, 1.0f);

    for(int i = 0; i < getCount(); i++)
        iGLEngine->drawText(posX + 2, posY + 2 + i * itemHeight, items[i].data());
}
string ListBox::getType()
{
    return "listbox";
}
