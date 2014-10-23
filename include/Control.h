/*
    this class is abstract class which contains basic functionality which all
    GUI items needed.


*/

#ifndef CONTROL_H
#define CONTROL_H

#include <list>
#include <string>

#include"GLEngine.h"

using std::list;
using std::string;

struct MouseState
{
    int LeftButtonDown;
    int RightButtonDown;
    int MiddleButtonDown;

    int x, y ;

    MouseState()
    {
        LeftButtonDown = 0;
        RightButtonDown = 0;
        MiddleButtonDown = 0;
        x = y = 0 ;
    }
};
class Control
{
    public:
        static list<Control *> controls;

    public:
        Control(int positionX, int positionY, int width, int height);
        virtual ~Control();

        virtual bool updateControl(MouseState &state);
        virtual void drawControl() = 0;
        virtual string getType() = 0;                   // return type of control
        void setPosition(int x, int y);
        void setSize(int width, int height);
        int getWidth();
        int getHeight();

    protected:
        bool    inside;             // mouse is inside of window or not
        int     posX, posY;
        int     width, height;

    private:
};

Control *addControl(Control *control);
#endif // CONTROL_H
