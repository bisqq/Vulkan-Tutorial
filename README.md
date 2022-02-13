# Vulkron

I learned the graphics API Vulkan, by splitting them into specific classes and getting a 3d model to work with textures in the renderer

https://user-images.githubusercontent.com/29154540/153740810-4321d1fb-f986-4dde-98db-46fe3bd47d03.mp4


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

  window = glfwCreateWindow(1080, 720, "Engine", nullptr, nullptr);

  if (nullptr == window)
  {
    LOG("Failed to create GLFW window\n");
    shutdownGLFW();
    return;
  }

  glfwMakeContextCurrent(window);

  if (!glfwVulkanSupported())
  {
    LOG("GLFW: Vulkan Not Supported\n");
    return;
  }
}

void updateViewPort()
{
  glfwSwapBuffers(window);
  glClear(GL_COLOR_BUFFER_BIT);
}

void onGlfwWindowResized(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
  updateViewPort();
}

void Loop()
{
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    beginDrawFrame();

    updateViewPort();
  }
}

void shutdownGLFW()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}
```
