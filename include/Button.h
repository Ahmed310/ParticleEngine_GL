#ifndef BUTTON_H
#define BUTTON_H

#include "Control.h"


class Button : public Control
{
    public:
        Button(string lable, int posX, int posY, int width, int height);
        virtual bool updateControl(MouseState &state);
        virtual void drawControl();
        virtual string getType();

    protected:
        bool    down;
        string  lable;
    private:
};

#endif // BUTTON_H
