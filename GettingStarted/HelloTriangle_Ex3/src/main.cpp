#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow*window);


int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);

    if(window==NULL)
    {
        std::cout << "Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD"<<std::endl;
        return -1;
    }
    glViewport(0,0,800,600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    float vertices[]{
        0.0f,0.0f,0.0f,
        0.5f, 0.0f,0.0f,
        0.5f,0.5f,0.0f,
        0.0f,0.0f,0.0f,
        0.0f,0.5f,0.0f,
        -0.5f,0.0f,0.0f

    };

    unsigned int VAO;
    unsigned int VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    const char* vertexShaderSource="#version 330 core\n"
    "layout(location=0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position= vec4(aPos,1.0f);\n"
    "}\n";

    const char* fragmentShaderSource1="#version 330 core\n"
    "out vec4 oColor;\n"
    "void main()\n"
    "{\n"
    "oColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";
    
    const char* fragmentShaderSource2="#version 330 core\n"
    "out vec4 yColor;\n"
    "void main()\n"
    "{\n"
    "yColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n";
    
    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "SHADER::COMPILE_ERROR_::VERTEX::"<<infoLog<<std::endl;
    }
    unsigned int fragmentShader1;
    fragmentShader1=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1,1,&fragmentShaderSource1,NULL);
    glCompileShader(fragmentShader1);
    glGetShaderiv(fragmentShader1,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader1,512,NULL,infoLog);
        std::cout<<"SHADER::COMPILE_ERROR::FRAGMENT::"<<infoLog<<std::endl;
    }
    unsigned int fragmentShader2;
    fragmentShader2=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShaderSource2,NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader2,512,NULL,infoLog);
        std::cout<<"SHADER::COMPILE_ERROR::FRAGMENT::"<<infoLog<<std::endl;
    }
    unsigned int shaderProgram1;
    shaderProgram1=glCreateProgram();
    glAttachShader(shaderProgram1,vertexShader);
    glAttachShader(shaderProgram1,fragmentShader1);
    glLinkProgram(shaderProgram1);
    unsigned int shaderProgram2;
    shaderProgram2=glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);
    

    //render loop
    while(!glfwWindowShouldClose(window))
    {
        //input 
        processInput(window);

        //rendering commands here 
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram1);
        glDrawArrays(GL_TRIANGLES,0,3);
        glUseProgram(shaderProgram2);
        glDrawArrays(GL_TRIANGLES,3,3);
        glBindVertexArray(0);

        //check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}