#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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
"   FragColor = vec4(0.1f, 0.1f, 0.1f, 0.5f);\n"
"}\n\0";
static const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.1f, 0.5f, 0.1f, 0.5f);\n"
"}\n\0";
int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
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
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
    glCompileShader(fragmentShader2);
    // check for shader compile errors
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader2);
    glLinkProgram(shaderProgram1);
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram1, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);





    struct shape {
        std::vector<GLfloat> vertices;
        GLuint VAO;
        GLuint VBO;
    };
    float Pi = 3.14159f;
    float twicePi = 2 * Pi;
    shape circle1;

    float x1 = 0.0f, y1 = 0.0f, z1 = 0.0f;
    float radius1 = 0.8f;

    int j;
    int side = 50;

    for (j = 0; j <= side + 1; j++) {

        circle1.vertices.push_back(x1 + (radius1 * cos(j * twicePi / side)));
        circle1.vertices.push_back(y1 + (0.4 * sin(j * twicePi / side)));
        circle1.vertices.push_back(z1);
    }

    glGenVertexArrays(1, &circle1.VAO);
    glGenBuffers(1, &circle1.VBO);
    glBindVertexArray(circle1.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, circle1.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circle1.vertices.size(), &circle1.vertices[0], GL_STATIC_DRAW);;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(0, circle1.VBO);
    glBindVertexArray(0);

    shape circle;

    float x = -0.3f, y = 0.0f, z = 0.0f;
    float radius = 0.1f;


    int i;
    int sides = 50;
    circle.vertices.push_back(x);
    circle.vertices.push_back(y);
    circle.vertices.push_back(z);
    for (i = 0; i <= sides + 1; i++) {

        circle.vertices.push_back(x + (radius * cos(i * twicePi / sides)));
        circle.vertices.push_back(y + (radius * sin(i * twicePi / sides)));
        circle.vertices.push_back(y);
    }

    glGenVertexArrays(1, &circle.VAO);
    glGenBuffers(1, &circle.VBO);
    glBindVertexArray(circle.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, circle.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circle.vertices.size(), &circle.vertices[0], GL_STATIC_DRAW);;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(0, circle.VBO);
    glBindVertexArray(0);

    shape circle2;

    float x2 = 0.3f, y2 = 0.0f, z2 = 0.0f;

    circle2.vertices.push_back(x2);
    circle2.vertices.push_back(y2);
    circle2.vertices.push_back(z2);
    for (i = 0; i <= sides + 1; i++) {

        circle2.vertices.push_back(x2 + (radius * cos(i * twicePi / sides)));
        circle2.vertices.push_back(y2 + (radius * sin(i * twicePi / sides)));
        circle2.vertices.push_back(y2);
    }

    glGenVertexArrays(1, &circle2.VAO);
    glGenBuffers(1, &circle2.VBO);
    glBindVertexArray(circle2.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, circle2.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circle2.vertices.size(), &circle2.vertices[0], GL_STATIC_DRAW);;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(0, circle2.VBO);
    glBindVertexArray(0);



   


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_LINE_STIPPLE);
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.7f, 0.7f, 0.7f, 0.5f);
        //  glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
        glBindVertexArray(circle.VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.vertices.size() / 3);

        glBindVertexArray(circle2.VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle2.vertices.size() / 3);
        glUseProgram(shaderProgram);
        glBindVertexArray(circle1.VAO);
        glDrawArrays(GL_LINE_STRIP, 0, circle1.vertices.size() / 3);

        // glDrawArrays(GL_LINE_LOOP, 0, circle.vertices.size() / 3); //zadaca3
        // glBindVertexArray(turbine.VAO);
       //  glDrawArrays(GL_LINE_STRIP, 0, turbine.vertices.size());
        glLineWidth(160.0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }



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