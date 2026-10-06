#include<shader.hpp>

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
    compile_and_link(vertex,fragment);
}
void Shader::use()
{
    glUseProgram(shaderProgram);
}
void Shader::compile_and_link(const std::string& vertex, const std::string& fragment)
{
    
    std::ifstream vertexFile(vertex);
    if (!vertexFile) {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND::" << vertex << std::endl;
        shaderProgram = 0;
        return;
    }

    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    const std::string vertexString = vertexStream.str();
    const char* vertexShaderCode = vertexString.c_str();
    vertexFile.close();
    std::ifstream fragmentFile(fragment);
    if (!fragmentFile) {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND::" << fragment << std::endl;
        shaderProgram = 0;
        return;
    }

    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    const std::string fragmentString = fragmentStream.str();
    const char* fragmentShaderCode = fragmentString.c_str();
    fragmentFile.close();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderCode,NULL);
    glCompileShader(vertexShader);
    char infoLog[255];
    int success;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,sizeof(infoLog),NULL,infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::\n"<<infoLog<<std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderCode,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,sizeof(infoLog),NULL,infoLog);
        std::cout<<"ERROR::SHADER::FRAGMENT::\n"<<infoLog<<std::endl;
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram,sizeof(infoLog),NULL,infoLog);
        std::cout<<"ERROR::LINKING::"<<infoLog<<std::endl;  
    }
    glDeleteShader(vertexShader);   
    glDeleteShader(fragmentShader);
}