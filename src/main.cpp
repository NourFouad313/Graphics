////////////////////////////////////////////////////////////////////
#include <iostream>
#include <limits>
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <shaders_handler.hpp>
#include <texture_handler.hpp>
#include <utils.hpp>
////////////////////////////////////////////////////////////////////

sf::Window *window = new sf::Window();

//openGL context settings
sf::ContextSettings settings;

// window state
bool state = true;

sf::Event event;

sf::Clock c;
sf::Time t ;

int main(int argc, char *argv[])
{
    ////////////////////////////////////////////////////////////////////

    ut::init_window(window,settings);

    ////////////////////////////////////////////////////////////////////

    ut::init_openGL();

    ////////////////////////////////////////////////////////////////////

    shaders_handler* shaders =new shaders_handler("shader/shader.vert","shader/shader.frag");

    shaders->use();

    ///////////////////////////////////////////////////////////////////

    ut::vertex_data(ut::positions, sizeof(ut::positions), ut::indices, sizeof(ut::indices));

    ///////////////////////////////////////////////////////////////////

    texture_handler* texture0 = new texture_handler("texture/cat.png");

    shaders->setInt("texture0", 0);

    ///////////////////////////////////////////////////////////////////

    glClearColor(1.0,1.0,0.5,1);

    ///////////////////////////////////////////////////////////////////

    while (state)
    {
        //handling events
        window->pollEvent(event);
        ut::handle_events(event, window,state);

        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations & reseting it
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

        // moving vertices by the glm::vec3 values
        //  transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f) /*these are added to vertices in vertex shader*/);
        transform = glm::rotate(transform /*identity mat*/,
        glm::radians((float) ut::get_time(c,t) ) /*angle*/,
        glm::vec3(0.5f, 0.5f, -0.5f) /*rotation axis*/);

        // get matrix's uniform location and set matrix &sending it to gpu
        unsigned int transformLoc = glGetUniformLocation(shaders->get_program_id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

        // texture units activision
        texture_handler::active(0);
        texture0->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Display on screen what has been rendered to the window so far  
        window->display();//suppressed: 24 bytes in 1 blocks
    }
    ut::destroy_objects();
    delete window;
    delete texture0;
    delete shaders;
}
