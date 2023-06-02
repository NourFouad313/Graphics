#define STB_IMAGE_IMPLEMENTATION
#include <SDL3/SDL.h>
#include <GLEW/glew.h>
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <openGL/shaders_handler.hpp>
#include <openGL/texture_handler.hpp>
#include <openGL/utils.hpp>
SDL_Window *window;
SDL_GLContext GLcontext;
uint32_t angle = 1;

int main(int argc ,char *argv[]){
    ////////////////////////////////////////////////////////////////////
    ut::init_window(window, GLcontext);
    ////////////////////////////////////////////////////////////////////
    ut::init_openGL();
    ////////////////////////////////////////////////////////////////////
    shaders_handler* shaders =new shaders_handler("shader/shader.vert","shader/shader.frag");
    shaders->use();
    ///////////////////////////////////////////////////////////////////
    float positions[] = {
         // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    ///////////////////////////////////////////////////////////////////
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    ///////////////////////////////////////////////////////////////////
    ut::create_pipeline(positions, sizeof(positions), indices, sizeof(indices));
    ///////////////////////////////////////////////////////////////////
    texture_handler* texture0 = new texture_handler("texture/cat.png");
    shaders->setInt("texture0", 0);
    ///////////////////////////////////////////////////////////////////
    glClearColor(0.2,0.5,0.5,1);
    ///////////////////////////////////////////////////////////////////
    SDL_Event event;
    while(true){
        glClear(GL_COLOR_BUFFER_BIT);
        // create transformations & reseting it
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // moving vertices by the glm::vec3 values
        //  transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f) /*these are added to vertices in vertex shader*/);
        transform = glm::rotate(transform /*identity mat*/, glm::radians((float)angle) /*angle*/, glm::vec3(0.5f, 0.5f, -0.5f) /*rotation axis*/);

        // get matrix's uniform location and set matrix
        unsigned int transformLoc = glGetUniformLocation(shaders->get_program_id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        angle++;

        // texture units activision
        texture_handler::active(0);
        texture0->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);

        SDL_PollEvent(&event);
        if(ut::handle_events(event , window)==1){
            break;
        };
    }
    delete (texture0);
    delete (shaders);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
