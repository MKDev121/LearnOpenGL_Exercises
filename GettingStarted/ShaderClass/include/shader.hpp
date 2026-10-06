#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader{

    unsigned int shaderProgram;

public:
    Shader(const std::string& vertex, const std::string& fragment);
    void compile_and_link(const std::string& vertex, const std::string& fragment); //compile and link the shaders
    void use();//use the shader


    void setBool(const std::string &name,bool value) const;
    void setInt(const std::string &name,int value) const;
    void setFloat(const std::string &name,float value) const;


};

#endif