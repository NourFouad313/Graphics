#pragma once
#include <fstream>
#include <sstream>
#include <iostream>

class shaders_handler
{
private:
    unsigned int programID;
public:
    shaders_handler(std::string vertex_shader_path ,std::string fragment_shader_path){
        //2 strings to store code
        std::string vertex_shader_code,fragment_shader_code;
        try
        {
            std::fstream vertex_shader_file;
            std::fstream fragment_shader_file;
            //ensure object can throw exceptions
            vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            vertex_shader_file.open(vertex_shader_path);
            fragment_shader_file.open(fragment_shader_path); 
            //initialize 2 obj 1 for vertex , 1 for fragment      
            std::stringstream vShaderStream, fShaderStream;
            // read file’s buffer contents into streams
            vShaderStream << vertex_shader_file.rdbuf();
            fShaderStream << fragment_shader_file.rdbuf();  
            //convert streaams to string
            vertex_shader_code = vShaderStream.str();       
            fragment_shader_code = fShaderStream.str();
            //close file handlers
            vertex_shader_file.close();          
            fragment_shader_file.close();   
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "FILE NOT READ......\n" ;
        }
        //converting to const char c for c_string
        const char* c_vertex_shader = vertex_shader_code.c_str();
        const char* c_fragment_shader = fragment_shader_code.c_str();
        //compileing and linking shaders to programID
        unsigned int vertex , fragment;
        int vsuccess,fsuccess,psuccess;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&c_vertex_shader,NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex,GL_COMPILE_STATUS,&vsuccess);
        if(vsuccess==GL_FALSE){
        char vinfolog[512];
        glGetShaderInfoLog(vertex,512,NULL,vinfolog);
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" <<vinfolog << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&c_fragment_shader,NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment,GL_COMPILE_STATUS,&fsuccess);
        if(fsuccess==GL_FALSE){
        char finfolog[512];
        glGetShaderInfoLog(fragment,512,NULL,finfolog);
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n"
                  << finfolog << std::endl;
        }
        this->programID =glCreateProgram();
        glAttachShader(programID,vertex);
        glAttachShader(programID,fragment);
        glLinkProgram(programID);
        glGetProgramiv(programID,GL_LINK_STATUS,&psuccess);
        if (psuccess==GL_FALSE)
        {
            char pinfolog[512];
            glGetProgramInfoLog(programID,512,NULL,pinfolog);
            std::cout << "ERROR::PROGRAM::SHADER::LINKING_FAILED\n" <<pinfolog << std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);  
    }
    void use(){
        glUseProgram(this->programID);
    }
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);
    }
     unsigned int get_program_id(){
        return this->programID;
    }
};
