#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include <utils.hpp>

class texture_handler
{
private:
    int width, height, nrChannels;  
    unsigned int texture_ID;
public:
texture_handler(std::string filename)
{
    // creating texture & binding it.
    glGenTextures(1, &texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // loading data to texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = texture_handler::load_img(filename);
      
    if(data)
    {
        if (".jpg" == ut::get_file_extension(filename))//jpg rgb
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }else if (".png" == ut::get_file_extension(filename))//png rgba
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }else
    {
    std::cout << "failed to load image\n";
    }
    stbi_image_free(data);
}

unsigned char* load_img(std::string filename){

    unsigned char *data = stbi_load((filename).c_str(), &width, &height, &nrChannels, 0);

    return data;
}

unsigned int get_textID(){

    return this->texture_ID;

} 

void bind(){

    glBindTexture(GL_TEXTURE_2D, this->texture_ID);

}

__always_inline static void active(int texture_unit){

    glActiveTexture(GL_TEXTURE0 + texture_unit);

}
};



