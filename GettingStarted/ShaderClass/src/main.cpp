#include<shader.hpp>
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


    //Input data
    float vertices[]={
        0.5f,0.5f,0.0f, //top right
        0.5f,-0.5f,0.0f,//bottom right
        -0.5f,-0.5f,0.0f, //bottom left 
        -0.5f,0.5f,0.0f //top left

    };
    unsigned int indices[] = { //note that we start from 0!
        0,1,3, //first triangle
        1,2,3 //second triangle
    };
    //Description about the vertex data 
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    //Creating buffer object , allocating the memory in the GPU and copying the vertices data into the buffer object
    unsigned int VBO;
    glGenBuffers(1,&VBO);

    unsigned int EBO;
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    //Tells OpenGL how to link the vertex data to vertex shader's attributes.
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    Shader myShader = Shader("Shaders/vertexShader.vert","Shaders/fragmentShader.frag");

    //render loop
    while(!glfwWindowShouldClose(window))
    {
        //input 
        processInput(window);

        //rendering commands here 
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        myShader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);  //glDrawArrays(GL_TRIANGLES,0,3);
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