#include <SDL/SDL.h>
#include "GLEngine.h"
#include "Button.h"
#include "ListBox.h"
#include "Slider.h"
#include "Emitter.h"

using namespace std;

const GLsizei windowWidth  = 640;
const GLsizei windowHeight = 480;
Uint8 *keys = NULL;
GLfloat rotateX = 45.0f, rotateY = 0.0f, zoom = -5.0f;

Texture *tex = NULL;
Light   *mLight = NULL;
int *seed = NULL;

MouseState state;
Control *controlled = NULL;         // contains pointer to control currently being manipulating

float   testValue   = 5.0f;

bool navigating     = false;
GLvoid establishProjectionMatrix(GLsizei width, GLsizei height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat) width / (GLfloat)height, 0.1f, 200.0f);

    glMatrixMode(GL_MODELVIEW);
}

GLvoid setOrtho(GLsizei width, GLsizei height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0,width,height,0);
}
GLvoid initGL(GLsizei width, GLsizei height)
{
    iGLEngine->Initialize(width,height);

    establishProjectionMatrix(width, height);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // rgb A
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL);                 // draw if face less or equal

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // optional
    glEnable(GL_PERSPECTIVE_CORRECTION_HINT);


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    tex = new Texture("asserts/vtr.tga","brick");

    addControl(new Button("Run Away",0,0,200,50));
    ListBox *lstNames = (ListBox*) addControl(new ListBox(0,0,200,200));

    lstNames->addItem("HEALTH");
    lstNames->addItem("VELOCITY");
    lstNames->addItem("GRAVITY");
    lstNames->addItem("FRICTION");
    lstNames->addItem("DRAG");

    Slider *sliderControl = (Slider*) addControl(new Slider("SLIDER TEST",-5.0f,5.0f,0,0,300,40));

    sliderControl->setValue(&testValue);


}

GLvoid displayFPS()
{
    static long lastTime = SDL_GetTicks();
    static long loops = 0;
    static GLfloat fps = 0.0f;

    int newTime = SDL_GetTicks();
    loops++;

    if(newTime - lastTime > 100)
    {
        float newFps =  (float)loops / (float) (newTime - lastTime) * 100.0f;

        fps = (fps + newFps) / 2.0f;

        lastTime = newTime ;
        loops = 0;
    }

    iGLEngine->drawText(5,5,"SDL | OpenGL demo %.2f",fps);
}
void drawCube(float size)
{
	glBegin(GL_QUADS);
		// front face
		glNormal3f(0.0,0.0,1.0);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);
		// left face
		glNormal3f(-1.0,0.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(-size/2,size/2,-size/2);
		// back face
		glNormal3f(0.0,0.0,-1.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);
		// right face
		glNormal3f(1.0,0.0,0.0);
		glColor3f(1.0,1.0,0.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,-size/2);
		glVertex3f(size/2,size/2,-size/2);
		// top face
		glNormal3f(0.0,1.0,0.0);
		glColor3f(1.0,0.0,1.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,-size/2);
		// bottom face
		glNormal3f(0.0,-1.0,0.0);
		glColor3f(0.0,1.0,1.0);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
}

GLvoid drawGrid()
{
    const float width = 80.0f;
    const float height = 80.0f;
    const int divisions = 100;

    float incX = width / (float)divisions;
    float incY = height / (float)divisions;

  //  glColor3f(0.4f,0.3f,0.6f);
    glNormal3f(0,1,0);

    for(float x = -width/2 ; x < width/2 ; x += incX)
    {
        for(float y = -height/2 ; y < height/2 ; y += incY)
        {
            glBegin(GL_TRIANGLE_STRIP);

            glVertex3f(x + incX, 0 , y + incY);
            glVertex3f(x       , 0 , y + incY);
            glVertex3f(x + incX, 0 , y );
            glVertex3f(x       , 0 , y );
            glEnd();
        }
    }
}

GLvoid draw_cube()
{
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D,tex->texID);
    glBegin(GL_QUADS);
    // top
    //glColor3f(0.0f,0.2f,0.9f);
    glTexCoord2f(2.0f,2.0f);    glVertex3f(1.0f,1.0f,-1.0f);
    glTexCoord2f(0.0f,2.0f);    glVertex3f(-1.0f,1.0f,-1.0f);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(-1.0f,1.0f,1.0f);
    glTexCoord2f(2.0f,0.0f);    glVertex3f(1.0f,1.0f,1.0f);

    // bottom
    //glColor3f(1.0f,0.5f,0.5f);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(1.0f,-1.0f,-1.0f);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(-1.0f,-1.0f,-1.0f);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(-1.0f,-1.0f,1.0f);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(1.0f,-1.0f,1.0f);
    // front
    //glColor3f(0.5f,1.0f,1.0f);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(1.0f,1.0f,1.0f);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(-1.0f,1.0f,1.0f);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(-1.0f,-1.0f,1.0f);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(1.0f,-1.0f,1.0f);
    // back
    //glColor3f(0.0f,0.5f,0.3f);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(1.0f,1.0f,-1.0f);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(-1.0f,1.0f,-1.0f);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(-1.0f,-1.0f,-1.0f);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(1.0f,-1.0f,-1.0f);
    // left
    //glColor3f(1.0f,0.2f,0.5f);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(-1.0f, 1.0f,-1.0f);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(-1.0f,-1.0f,-1.0f);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(-1.0f,-1.0f, 1.0f);
    // right
    //glColor3f(1.0f,0.5f,1.0f);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(1.0f, 1.0f,-1.0f);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(1.0f,-1.0f,-1.0f);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(1.0f,-1.0f, 1.0f);
    glEnd();
}

GLvoid drawControls()
{
    for( list<Control*>::iterator it = Control::controls.begin(); it != Control::controls.end(); it++)
    {
        Control *control = (*it);
        control->drawControl();

        if(controlled != NULL && controlled != control || navigating)
        {
            continue;
        }

        if(control->updateControl(state))
        {
            controlled = control;
            // handle events here
        }
        else if(control == controlled)
        {
            controlled == NULL;
        }
        else
        {
            // control has been updates ... but has no message to update
        }

    }
}
GLvoid drawScene()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // pass 1
   // glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   // rgb A
    establishProjectionMatrix(640,480);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glTranslatef(0.0f,0.0f,zoom);

    glRotatef(rotateX,1.0f,0.0f,0.0f);
    glRotatef(rotateY,0.0f,1.0f,0.0f);



    draw_cube();
    //glColor3f(1.0f,1.0f,1.0f);
  //  glBindTexture(GL_TEXTURE_2D, tex->texID);
    //drawCube(10);
  //drawGrid();
 // for(int i = 0 ; i < (int)Light::lights.size() ; i++)
 // {
  //    double rndNo = (double)SDL_GetTicks() + (seed[i]);
   //   float x = (float)sin(rndNo/1600.0f) * (float)cos(rndNo/1200.0f) * 50.0f ;
   //   float y = (float)sin(rndNo/900.0f) * (float)cos(rndNo/1400.0f) * 50.0f ;
   //   Light::lights[i]->setPosition(x,30.0f,y);
   //   Light::lights[i]->updateLight();
//  }

  // pass 2
  glDisable(GL_LIGHTING);
  setOrtho(640,480);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  drawControls();
  //displayFPS();
  glFlush();

  SDL_GL_SwapBuffers();


}


GLboolean updateNavigation()
{
    const GLfloat speed         = 0.2f;
    const GLfloat zoomSpeed     = 0.01f;
    static int lastX            = -1;
    static int lastY            = -1;

    if(keys[SDLK_ESCAPE])
        return true;

    if(lastX == -1 && lastY == -1)
    {
       // lastX   = state.x;
       // lastY   = state.y;
    }

    int deltaX  = lastX - state.x;
    int deltaY  = lastY - state.y;

    lastX   = state.x;
    lastY   = state.y;


    if(state.LeftButtonDown && controlled == NULL)
    {
        SDL_WM_GrabInput(SDL_GRAB_ON);

        rotateX     -= (float)deltaY * speed;
        rotateY     -= (float)deltaX * speed;
        navigating   = true;
    }

    else if(state.MiddleButtonDown && controlled == NULL)
    {
        SDL_WM_GrabInput(SDL_GRAB_ON);
        zoom    -= (float)deltaX * zoomSpeed;
    }
    else
    {
        SDL_WM_GrabInput(SDL_GRAB_OFF);
        navigating  = false;
    }

    return false;

}

int main(int argc, char** argv)
{
    if( SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // throw exception
        fprintf(stderr,"Unable to init SDL %s", SDL_GetError());
        exit(1);
    }
    if( SDL_SetVideoMode(640,480,0,SDL_OPENGL) == NULL )
    {
        // through opengl not initilized
        fprintf(stderr,"Unable to init SDL %s", SDL_GetError());
        exit(2);
    }

    initGL(640, 480);
#if 0
    seed = new int[Light::numLights];
    for(int i = 0 ; i < Light::numLights ; i++)
    {
        Light *light = new Light(LIGHT_SPOT);
        float r = (float)rand() / (float)RAND_MAX;
        float g = (float)rand() / (float)RAND_MAX;
        float b = (float)rand() / (float)RAND_MAX;

        light->setDiffuse(r,g,b,1);
        light->setAmbient(0,0,0,1);
        light->setSpotDirection(0,-1,0);

        float cutOff = 20.0f + (float)rand() / (float)RAND_MAX * 60.0f;

        light->setCutOff(cutOff);
        light->setExponenet(20.0f * cutOff);

        seed[i] = rand();

    }
    #endif // 0

    int done = 0;
    while(!done)
    {
        SDL_GetMouseState(&state.x, &state.y);

        state.LeftButtonDown    = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
        state.MiddleButtonDown  = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
        state.RightButtonDown   = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);

        drawScene();
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                done = 1;

            keys = SDL_GetKeyState(NULL);
        }

        if(updateNavigation())
            done = 1;
    }

    for(GLuint i = 0 ; i < Light::lights.size() ; i++)
        delete Light::lights[i];

    delete[] seed;
    GLEngine::Uninitialize();

    for( list<Control*>::iterator it = Control::controls.begin(); it != Control::controls.end(); it++)
    {
        delete (*it);
        it = Control::controls.begin();
    }


    SDL_Quit();
    return 0;
}
