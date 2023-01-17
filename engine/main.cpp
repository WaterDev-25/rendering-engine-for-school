#include <iostream>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "cwindowopengl46.hpp"
#include "cshader.hpp"
#include "cmodel.hpp"
#include "ccubemap.hpp"

glm::mat4 GetViewMatrix()
{
    float radius = 10.0f;
    float camX = static_cast<float>(sin((SDL_GetTicks() / 1000.0f)) * radius);
    float camZ = static_cast<float>(cos((SDL_GetTicks() / 1000.0f)) * radius);

    //return glm::lookAt(glm::vec3(camX, 3.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    double currentTime = SDL_GetTicks() / 1000.0f;
    double angle = currentTime * 1.0f;

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f) + glm::vec3(camX, 3.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotatedView = glm::rotate(view, (float)angle, glm::vec3(1.0f, 0.0f, 0.0f));

    return rotatedView;
}

int main(int argc, char** argv)
{
    const int wWidth = 1920;
    const int wHeight = 1080;

    CWindowOpenGL46 window(wWidth, wHeight, "engine");

    SDL_SetWindowFullscreen(window.GetHandle(), SDL_WINDOW_FULLSCREEN_DESKTOP);

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    CShader baseShader("shaders/base_vs.glsl", "shaders/base_fs.glsl");
    CShader cubeMapShader("shaders/cubemap_vs.glsl", "shaders/cubemap_fs.glsl");

    //CModel baseModel("models/nfc/asm.obj");
    CModel partOne("models/nfc/part1.obj");
    CModel partTwo("models/nfc/part2.obj");

    std::vector<std::string> cubeMapTextures = {
        "textures/cubemap/maskonaive/right.jpg",
        "textures/cubemap/maskonaive/left.jpg",
        "textures/cubemap/maskonaive/top.jpg",
        "textures/cubemap/maskonaive/bottom.jpg",
        "textures/cubemap/maskonaive/front.jpg",
        "textures/cubemap/maskonaive/back.jpg"
    };

    CCubeMap cubeMap(cubeMapTextures);

    baseShader.Use();
    baseShader.SetInt("material.diffuse", 0);
    baseShader.SetInt("material.specular", 1);

    cubeMapShader.Use();
    cubeMapShader.SetInt("skybox", 0);

    SDL_Event windowEvent;

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (true)
    {
        float currentFrame = static_cast<float>(SDL_GetTicks() / 1000.0f);
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT)
                break;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        baseShader.Use();

        baseShader.SetVec3("viewPos", GetViewMatrix()[3]);
        baseShader.SetFloat("material.shininess", 32.0f);

        baseShader.SetVec3("pointLights[0].position", 0.0f, -1.0f, 0.0f);
        baseShader.SetVec3("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
        baseShader.SetVec3("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
        baseShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        baseShader.SetFloat("pointLights[0].constant", 1.0f);
        baseShader.SetFloat("pointLights[0].linear", 0.09f);
        baseShader.SetFloat("pointLights[0].quadratic", 0.032f);

        baseShader.SetVec3("pointLights[1].position", 0.0f, 2.0f, 0.0f);
        baseShader.SetVec3("pointLights[1].ambient", 0.2f, 0.2f, 0.2f);
        baseShader.SetVec3("pointLights[1].diffuse", 1.0f, 1.0f, 1.0f);
        baseShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        baseShader.SetFloat("pointLights[1].constant", 1.0f);
        baseShader.SetFloat("pointLights[1].linear", 0.09f);
        baseShader.SetFloat("pointLights[1].quadratic", 0.032f);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)wWidth / (float)wHeight, 0.1f, 100.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        baseShader.SetMat4("model", model);
        baseShader.SetMat4("projection", projection);
        baseShader.SetMat4("view", view);
        
        //baseModel.Draw(baseShader);
        partOne.Draw(baseShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        baseShader.SetMat4("model", model);

        partTwo.Draw(baseShader);

        cubeMapShader.Use();
        view = glm::mat4(glm::mat3(GetViewMatrix()));
        cubeMapShader.SetMat4("view", view);
        cubeMapShader.SetMat4("projection", projection);

        cubeMap.Draw();

        SDL_GL_SwapWindow(window.GetHandle());
    }

    return 0;
}
