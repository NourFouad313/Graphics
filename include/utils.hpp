#pragma once
#include <string>

using std::string;

namespace ut
{
    uint32_t* VAO = new uint32_t;
    uint32_t* VBO = new uint32_t;
    uint32_t* EBO = new uint32_t;

    ///////////////////////////////////////////////////////////////////
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    ///////////////////////////////////////////////////////////////////
        glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};
    ///////////////////////////////////////////////////////////////////
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    ///////////////////////////////////////////////////////////////////
    /// @brief initializing window
    /// @param window 
    /// @param GLcontext 
    void init_window(sf::Window* window ,sf::ContextSettings &settings){
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 8;
        settings.majorVersion = 3;          
        settings.minorVersion = 0;
        window->create(sf::VideoMode(800, 600), "openGL", sf::Style::Default, settings);
        window->setVerticalSyncEnabled(true);
    }
    ////////////////////////////////////////////////////////////////////
    /// @brief initializing glad
    int init_openGL(){
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
        std::cout << "openGL VERSION: " << glGetString(GL_VERSION) << std::endl;
        return 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief sending vertex data to gpu
    void vertex_data(float positions[],size_t szposition,uint32_t indices[] = nullptr,size_t szindices = 0){
    glGenVertexArrays(1,VAO);
    //bind means choose that thing and all func calls after it will affect that thing 
    //VAO stores VBO & EBO
    glBindVertexArray(*(VAO));
    //when you bind a VBO all VBO changing operations (such as glBufferData) will affect the last bound VBO. 
    //AFTER binding the buffer any call to a buffer func on target GL_ARRAY_BUFFER will configure the currently binded buffer wich is VBO.
    glGenBuffers(1,VBO);
    glBindBuffer(GL_ARRAY_BUFFER,*(VBO));
    //is a function specifically targeted to copy user-defined data into the currently bound buffer
    glBufferData(GL_ARRAY_BUFFER,szposition,positions,GL_STATIC_DRAW);
    //EBO
    if(indices != nullptr && szindices == 0){
    glGenBuffers(1,EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(EBO));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, szindices, indices, GL_STATIC_DRAW);
    }
    // attributes
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
    int handle_events(sf::Event event , sf::Window* window , bool &state){
    switch (event.type)
    {
    case sf::Event::Closed:
        state = false;
        window->close();
        break;
    case sf::Event::Resized:
        glViewport(0, 0, event.size.width, event.size.height);
        break;
    }

    return 0;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////

    void destroy_objects(){
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    delete (VAO);
    delete (VBO);
    delete (EBO);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////
    float get_time(sf::Clock &c , sf::Time &t){
    t = c.getElapsedTime();
     if (t.asSeconds()==std::numeric_limits<float>::max()){
        c.restart();
     }
     return t.asSeconds();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// @param file_name 
    /// @return file extention
    string get_file_extension(string file_name){
        int idx = file_name.find_last_of(".");
        string extension;
        for (size_t i = idx; i < file_name.length(); i++)
        {
        extension += file_name[i];
        }
      return extension;
    }  
} // namespace ut


