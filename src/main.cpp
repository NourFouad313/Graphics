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

    ut::vertex_data(ut::vertices, sizeof(ut::vertices));

    ///////////////////////////////////////////////////////////////////

    texture_handler* texture0 = new texture_handler("texture/cat.png");

    shaders->setInt("texture0", 0);

    ///////////////////////////////////////////////////////////////////
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3,0.3,0.3,1);
    ///////////////////////////////////////////////////////////////////

    while (state)
    {
        //handling events
        window->pollEvent(event);
        ut::handle_events(event, window,state);

        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaders->get_program_id(),"view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaders->get_program_id(),"projection"), 1, GL_FALSE, &projection[0][0]);

        // texture units activision
        texture_handler::active(0);
        texture0->bind();
        for (uint8_t i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, ut::cubePositions[i]);
            model = glm::rotate(model,ut::get_time(c,t),glm::vec3(1.0,0.5,1.0));
            glUniformMatrix4fv(glGetUniformLocation(shaders->get_program_id(),"model"), 1, GL_FALSE, &model[0][0]);   
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //Display on screen what has been rendered to the window so far  
        window->display();//suppressed: 24 bytes in 1 blocks
        //clear window for the next frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    ut::destroy_objects();
    delete window;
    delete texture0;
    delete shaders;
}
