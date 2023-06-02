#pragma once
#include <string>

using std::string;

namespace ut
{
    uint32_t* VAO = new uint32_t;
    uint32_t* VBO = new uint32_t;
    uint32_t* EBO = new uint32_t;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief initializing window
    /// @param window 
    /// @param GLcontext 
    void init_window(SDL_Window* &window ,SDL_GLContext GLcontext){
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("window", 600, 600, SDL_WINDOW_OPENGL);
        GLcontext = SDL_GL_CreateContext(window);
        if(window == NULL){
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_GetError();
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief initializing glew
    void init_openGL(){
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << glewGetErrorString(err) << std::endl;
        }
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 30);
        // VERSION DATA
        std::cout <<"GLEW VERSION: " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "openGL VERSION: " << glGetString(GL_VERSION) << std::endl;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    void create_pipeline(float positions[],size_t szposition,uint32_t indices[],size_t szindices){
    glGenVertexArrays(1,VAO);
    glGenBuffers(1,VBO);
    glGenBuffers(1,EBO);
    //bind means choose that thing and all func calls after it will affect that thing 
    //VAO stores VBO & EBO
    glBindVertexArray(*(VAO));
    //when you bind a VBO all VBO changing operations (such as glBufferData) will affect the last bound VBO. 
    //AFTER binding the buffer any call to a buffer func on target GL_ARRAY_BUFFER will configure the currently binded buffer wich is VBO.
    glBindBuffer(GL_ARRAY_BUFFER,*(VBO));
    //is a function specifically targeted to copy user-defined data into the currently bound buffer
    glBufferData(GL_ARRAY_BUFFER,szposition,positions,GL_STATIC_DRAW);
    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(EBO));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, szindices, indices, GL_STATIC_DRAW);
    // attributes
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
    int handle_events(SDL_Event event , SDL_Window *window){
        if (event.type == SDL_EVENT_QUIT)
            {
        return 1;
            }
    return 0;
    }
    void destroy(){
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


