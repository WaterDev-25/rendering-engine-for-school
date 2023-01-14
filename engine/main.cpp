#include <SDL2/SDL.h>
#include <iostream>

#include "cwindowopengl46.hpp"

int main(int argc, char** argv)
{
    CWindowOpenGL46 window(1280, 720, "engine");

    // Shaders section
    // 
    // Vertex shader
    //

    const char* vShaderSource = "#version 460 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "WARNING --- Vertex shader compilation failed ---" << std::endl << infoLog << std::endl;
    }

    //
    // Fragment shader
    //

    const char* fShaderSource = "#version 460 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "WARNING --- Fragment shader compilation failed ---" << std::endl << infoLog << std::endl;
    }

    //
    // Program shader
    //

    unsigned int sProgram = glCreateProgram();

    glAttachShader(sProgram, vShader);
    glAttachShader(sProgram, fShader);

    glLinkProgram(sProgram);

    glGetProgramiv(sProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(sProgram, 512, NULL, infoLog);
        std::cout << "WARNING --- Program shader linking failed ---" << std::endl << infoLog << std::endl;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int vbo, vao;
    
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    SDL_Event windowEvent;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT)
                break;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glUseProgram(sProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window.GetHandle());
    }

    return 0;
}
