#include "Texture.h"

vector<Texture*> Texture::textures;
Texture::Texture(string in_filename, string in_name)
{
    //ctor
    imageData = NULL;
    if(!loadTGA(in_filename))
    {
        fprintf(stderr,"Unable to load TGA file");
    }

    name = in_name;
    textures.push_back(this);

}
Texture::~Texture()
{
    for(vector<Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
        if((*it) == this)
            textures.erase(it);

    if(imageData)
        delete[] imageData;
}
bool Texture:: loadTGA(string filename)
{
    TGA_Header header;

    ifstream file(filename.data(), std::ios_base::binary);

    if(!file.is_open())
        return false;

    if(!file.read((char*)&header, sizeof(header)))
        return false;

    if(header.ImageType != 2)           // 2 uncompressed true-color image
        return false;

    width  = header.ImageWidth;
    height = header.ImageWidth;
    bpp    = header.PixelDepth;

    if(width  <= 0   ||
       height <= 0   ||
       (bpp != 24 && bpp != 32)  )
    {
        return false;
    }

    GLuint type = GL_RGBA;
    if(bpp == 24)
            type = GL_RGB;

    GLuint bytesPerPixel = bpp / 8;
    GLuint imageSize = width * height * bytesPerPixel;

    imageData = new GLubyte[imageSize];

    if(imageData == NULL)
        return false;

    if(!file.read((char*)imageData,imageSize))
    {
        delete[] imageData;
        return false;
    }

    // Convert BGR --> RGB
#if 1
    for(GLuint i = 0 ; i < (int)imageSize ; i += bytesPerPixel)
    {
        GLuint tmp     = imageData[i];
        imageData[i]   = imageData[i+2];
        imageData[i+2] = tmp;
    }
#endif // 0
    creatTexture(imageData,width,height,type);
    return true;

}
bool Texture:: creatTexture(unsigned char* imageData, unsigned int width, unsigned int height, int type)
{
    glGenTextures(1,&texID);
    glBindTexture(GL_TEXTURE_2D , texID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE,imageData);
    return true;

}
