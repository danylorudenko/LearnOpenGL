#include "..\Include\Program.h"
#include "..\Include\Texture\DoubleTextureController.h"
#include "..\Include\RenderingSystem\GLObject\GLTestCube.h"
#include "..\Include\Util\Input.h"
#include <memory>

Program::Program()
{
    Initialize();
}

Program::~Program()
{
    glfwTerminate();
}

void Program::Initialize()
{
    if (InitGLFW() != 0) {
        throw std::runtime_error("Error initializing GLFW");
    }

    // ================

    main_window_ = nullptr;
    if (OpenWindow_SetContext(main_window_, default_resolution_X, default_resolution_Y) != 0) {
        throw std::runtime_error("Error opening window.");
    }

    // ================

    if (InitGLEW() != 0) {
        throw std::runtime_error("Error initializing GLEW.");
    }

    // Callbacks
    glfwSetKeyCallback(main_window_, key_callback);
    glfwSetFramebufferSizeCallback(main_window_, RenderingSystem::Instance().frame_buffer_size_callback);

    // ================


    // ������-������-�������������

    const int value_count = 180;

    auto vertex_data = std::make_shared<VertexData>(new GLfloat[value_count]{
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    }, value_count);


    auto main_camera = std::make_shared<Camera>(RenderingSystem::DEFAULT_FOW);
    RenderingSystem::Instance().Create(default_resolution_X, default_resolution_Y, main_camera);

    auto test_cube_shader = std::make_shared<ShaderProgram>("Shaders\\vertex_shader.vglsl", "Shaders\\fragment_shader.fglsl");
    auto test_cube_texture = std::make_shared<DoubleTextureController>("Resources\\container.jpg", "Resources\\awesomeface.png");

    auto test_cube_material = std::make_shared<Material>(test_cube_shader);
    test_cube_material->SetMainTexture(test_cube_texture);

    auto test_cube = std::make_shared<GLTestCube>(vertex_data, test_cube_material);

    RenderingSystem::Instance().AddToDrawList(test_cube);
}

void Program::StartMainLoop()
{
    while (glfwWindowShouldClose(main_window_)) {
        RenderingSystem::Instance().Iterate(main_window_);
    }
}

void Program::FrameBufferSizeCallBack(GLFWwindow * window, int width, int height)
{
    RenderingSystem::Instance().SetViewport(width, height);
}
