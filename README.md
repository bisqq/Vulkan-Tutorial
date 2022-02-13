# Vulkron

I learned the graphics API Vulkan, by splitting them into specific classes and getting a 3d model to work with textures in the renderer

![](https://user-images.githubusercontent.com/29154540/153740324-8d64e08d-08db-43b6-b5bb-10b7e4bdb904.png)

## Getting Started
To get started install GLFW, glm and the vulkan sdk in your project. In your main function I recommend having the setup as so:

```c++
#define LOG(x) std::cout << x << std::endl;

int main()
{
  VulkronApplicationInfo Info;
  Info.enableValidationLayers = true;
  Info.major = 1;
  Info.minor = 0;
  Info.patch = 0;

  //Glfw and vulkan --------------------------------------------
  beginGLFW();
  beginVulkan();
  Loop();
  shutdownVulkan();
  shutdownGLFW();
  //End of Glfw and vulkan -------------------------------------

  return 0;
}

void beginGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  vkInit.window = glfwCreateWindow(1080, 720, "Engine", nullptr, nullptr);

  if (nullptr == vkInit.window)
  {
    LOG("Failed to create GLFW window\n");
    shutdownGLFW();
    return;
  }

  glfwMakeContextCurrent(vkInit.window);

  glfwSetWindowRefreshCallback(vkInit.window, windowRefreshFun);

  if (!glfwVulkanSupported())
  {
    LOG("GLFW: Vulkan Not Supported\n");
    return;
  }
}

void updateViewPort()
{
  glfwSwapBuffers(vkInit.window);
  glClear(GL_COLOR_BUFFER_BIT);
}

void onGlfwWindowResized(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
  updateViewPort();
}

void Loop()
{
  while (!glfwWindowShouldClose(vkInit.window))
  {
    glfwPollEvents();

    vkInit.beginDrawFrame();

    updateViewPort();
  }
}

void shutdownGLFW()
{
  glfwDestroyWindow(vkInit.window);
  glfwTerminate();
}
```
