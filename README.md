# Vulkron

I learned the graphics API, Vulkan, through the [Vulkan tutorial](https://vulkan-tutorial.com/) and some experimentation on my own. 

The difficult part about about this project was abstracting/creating a wrapper for it. It was hard to know what needs to be wrapped/abstracted, but I for sure did not want to keep everything in a file or two. My goal for this project is to make it easier for others work with a lower level graphics API. I defninitly will come back and rework the design. 

For now I created a main header file, `Vulkron.h`, containing the main method declarations and fields for Vulkan to operate. I also seperated the `Vertex` and `index` buffers into it's own file for ease of use when adding data to the buffer. From there I created `.cpp` files for each section of vulkan to keep it a bit more organized. I also included a debugging methods to better understand the underlying initialization from Vulkan, it allows the user to see what Vulkan calls and retrieves from your local computer. 

Overall I learned how each part of vulkan operate with each other. At the end I managed to get a 3d model to work with textures in the renderer

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

    // drawing code here

    updateViewPort();
  }
}

void shutdownGLFW()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}
```
