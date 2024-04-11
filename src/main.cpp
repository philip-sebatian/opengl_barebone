#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};
static ShaderProgramSource Parseshader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
                std::cout << "Detected Vertex Shader\n";
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
                std::cout << "Detected Fragment Shader\n";
            }
        }
        else {
            std::cout << "Appending line to type: " << (int)type << "\n";
            ss[(int)type] << line << "\n";
        }
    }

    
    return { ss[0].str(), ss[1].str() };
}



int main() {
    // Initialize GLFW
    ShaderProgramSource ss = Parseshader("res/shader/basic.shader");
    const char* vertexShaderSource = ss.VertexSource.c_str();
    const char* fragmentShaderSource = ss.FragmentSource.c_str();
    
    std::cout<<fragmentShaderSource<<std::endl;
   // std::cout << "Fragment Shader Source:\n" << fragmentShaderSource << std::endl;

    // Rest of the code...

   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Example", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
    // Compile and link shaders
    unsigned int VBO,VOA;
    float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    }; 
    glGenVertexArrays(1,&VOA);
    glBindVertexArray(VOA);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(0));
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    


   


    unsigned int vertexshader ,fragmentshader , shaderProgram ;
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexshader);

    fragmentshader= glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentshader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,fragmentshader);
    glAttachShader(shaderProgram,vertexshader);
    glDeleteShader(fragmentshader);
    glDeleteShader(vertexshader);
    glLinkProgram(shaderProgram);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VOA);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VOA);
    glDeleteBuffers(1, &VBO);
    
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
