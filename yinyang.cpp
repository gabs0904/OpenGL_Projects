#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
static const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

static const char* fragmentShaderSourceBlack = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShaderBlack = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderBlack, 1, &fragmentShaderSourceBlack, nullptr);
    glCompileShader(fragmentShaderBlack);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderBlack, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderBlack, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint shaderProgramBlack = glCreateProgram();
    glAttachShader(shaderProgramBlack, vertexShader);
    glAttachShader(shaderProgramBlack, fragmentShaderBlack);
    glLinkProgram(shaderProgramBlack);
    // check for linking errors
    glGetProgramiv(shaderProgramBlack, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramBlack, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderBlack);


    int circle_points = 50;
    float angle; 
    std::vector<float> vertices;
    float PI = 3.14;
    float x, y, z;
    float rx = 0.04;
    float ry = 0.05;
    x = 0.0f;
    y = 0.34f;
    z = 0.0f;
    for (int i = 0; i < (circle_points); i++)
    {
        vertices.push_back(x + (rx * cos(2 *PI * i / circle_points)));
        vertices.push_back(y + (ry * sin(2* PI * i / circle_points)));
        vertices.push_back(z);
    }
    x = 0.0f;
    y = -0.34f;
    z = 0.0f;
    std::vector<float> verticessmallcircle;

    for (int i = 0; i < (circle_points); i++)
    {
        verticessmallcircle.push_back(x + (rx * cos(2 * PI * i / circle_points)));
        verticessmallcircle.push_back(y + (ry * sin(2 * PI * i / circle_points)));
        verticessmallcircle.push_back(z);
    }

    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    std::vector<float> verticeswhite;
    std::vector<float> verticeswhitehalf;
    rx = 0.5;
    ry = 0.6;
    for (int i = 36; i < (circle_points+15); i++)
    {
        verticeswhitehalf.push_back(x + (rx * cos(2*PI * i / circle_points)));
        verticeswhitehalf.push_back(y + (ry * sin(2*PI * i / circle_points)));
        verticeswhitehalf.push_back(z);
    }
    x = 0.0f;
    y = 0.3f;
    z = 0.0f;
    rx = 0.26;
    ry = 0.29;
    for (int i = 0; i < (circle_points ); i++)
    {
        verticeswhite.push_back(x + (rx * cos(2 * PI * i / circle_points)));
        verticeswhite.push_back(y + (ry * sin(2 * PI * i / circle_points)));
        verticeswhite.push_back(z);
    }


    std::vector<float> verticesblackhalf;
    rx = 0.5;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    ry = 0.6;
    for (int i = 13; i < (circle_points - 11); i++)
    {
        verticesblackhalf.push_back(x + (rx * cos(2 * PI * i / circle_points)));
        verticesblackhalf.push_back(y + (ry * sin(2 * PI * i / circle_points)));
        verticesblackhalf.push_back(z);
    }
    std::vector<float> verticesblack;

    x = 0.0f;
    y = -0.3f;
    z = 0.0f;
    rx = 0.26;
    ry = 0.3;
    for (int i = 0; i < (circle_points); i++)
    {
        verticesblack.push_back(x + (rx * cos(2 * PI * i / circle_points)));
        verticesblack.push_back(y + (ry * sin(2 * PI * i / circle_points)));
        verticesblack.push_back(z);
    }


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, verticessmallcircle.size() * sizeof(verticessmallcircle), &verticessmallcircle[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, verticeswhite.size() * sizeof(verticeswhite), &verticeswhite[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VBO3, VAO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, verticesblack.size() * sizeof(verticesblack), &verticesblack[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VBO4, VAO4;
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);
    glBindVertexArray(VAO4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, verticesblackhalf.size() * sizeof(verticesblackhalf), &verticesblackhalf[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VBO5, VAO5;
    glGenVertexArrays(1, &VAO5);
    glGenBuffers(1, &VBO5);
    glBindVertexArray(VAO5);

    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(GL_ARRAY_BUFFER, verticeswhitehalf.size() * sizeof(verticeswhitehalf), &verticeswhitehalf[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
   
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO5);
        glDrawArrays(GL_TRIANGLE_FAN, 0, verticeswhitehalf.size() / 3);
        glUseProgram(shaderProgramBlack);
        glBindVertexArray(VAO4);
        glDrawArrays(GL_TRIANGLE_FAN, 0, verticesblackhalf.size() / 3);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, verticeswhite.size() / 3);
        glUseProgram(shaderProgramBlack);

        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLE_FAN, 0, verticesblack.size() / 3);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()/3);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, verticessmallcircle.size() / 3);

        
       
        
     

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

 
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}