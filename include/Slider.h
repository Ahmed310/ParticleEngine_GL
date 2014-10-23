#ifndef SLIDER_H
#define SLIDER_H

#include "Control.h"

class Slider : public Control
{
    public:

        Slider(string lable, float minV, float maxV, int xPos, int yPos, int width, int height );

        void setValue(float *value);

        virtual bool updateControl(MouseState &state);
        virtual void drawControl() ;
        virtual string getType() ;

    protected:
        float       defaultV;
        float       minV;
        float       maxV;
        float       *current;
        string      lable;
        bool        dragging ;
};

#endif // SLIDER_H
