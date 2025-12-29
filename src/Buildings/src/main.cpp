#include "headers.h"
#include "texture.h"
#include "house.h"
#include "platform.h"
#include "weather.h" 

// ===================== 全局常量定义 =====================
// 单次调整角度步长
const float ANGLE_STEP_WIDTH = 0.05f;
// 单次调整相机距离步长
const float CRMERA_DISTANCE_STEP_WIDTH = 50.0f;
// 单词调整相机偏移步长
const float CRMERA_OFFSET_STEP_WIDTH = 25.0f;
// ===================== 全局变量定义 =====================
// 窗口指针及窗口大小
GLFWwindow* window;
int window_width = 1200, window_height = 800;

// ImGui 状态变量
bool showWeatherControls = true;
bool showDebugInfo = true;

// 相机参数相关
float rotate_x = 0.0f, rotate_y = 0.0f;
float camera_distance = 1500.0f;
float camera_offset[3] = {0.0f, 500.0f, 0.0f};

// 时间变量
double lastTime = 0.0;

// 键盘输入缓冲区
bool keyBuffer[1024] = {false};

// 光源参数
// float lightIntensity = 1.0f;
// glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
// glm::vec3 lightPosition = glm::vec3(100.0f, 100.0f, 100.0f);

void initLightSystem() {
    // 简易光照系统
    GLfloat sunDirection[] = { 100.0, 100.0, 100.0, 0.0 };
    GLfloat sunIntensity[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat ambientIntensity[] = { 0.5, 0.5, 0.5, 1.0 };
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntensity);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, sunDirection);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunIntensity);
}

// 实现键盘控制
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // ImGui处理键盘输入
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

    // 获取ImGui的IO状态
    ImGuiIO& io = ImGui::GetIO();
    
    // 如果ImGui想要捕获键盘事件，就跳过我们的处理
    if (io.WantCaptureKeyboard) {
        return;
    }
    
    // 安全检查：确保键值有效
    if (key < 0) {
        return;  // 忽略负值键（如GLFW_KEY_UNKNOWN）
    }
    
    if (action == GLFW_PRESS) {
        keyBuffer[key] = true;
    } else if (action == GLFW_RELEASE) {
        keyBuffer[key] = false;
    }
    
    // 处理特殊按键
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                if (rotate_x <= 1.55f) {
                    rotate_x += ANGLE_STEP_WIDTH;
                }
                break;
            case GLFW_KEY_DOWN:
                if (rotate_x >= -1.55f) {
                    rotate_x -= ANGLE_STEP_WIDTH;
                }
                break;
            case GLFW_KEY_RIGHT:
                if (rotate_y <= 1.55f) {
                    rotate_y += ANGLE_STEP_WIDTH;
                }
                break;
            case GLFW_KEY_LEFT:
                if (rotate_y >= -1.55f) {
                    rotate_y -= ANGLE_STEP_WIDTH;
                }
                break;
            case GLFW_KEY_F1:
                // F1键切换调试信息
                showDebugInfo = !showDebugInfo;
                std::cout << "调试面板: " << (showDebugInfo ? "显示" : "隐藏") << std::endl;
                break;
            case GLFW_KEY_F2:
                // F2键切换天气面板
                showWeatherControls = !showWeatherControls;
                std::cout << "天气面板: " << (showWeatherControls ? "显示" : "隐藏") << std::endl;
                break;
        }
    }
    
    // ESC键退出
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// 实现窗口大小回调函数
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
}

// 初始化项目函数
bool initProject() {
    // 1. 初始化 glfw 和 窗口 `window`
    if (!glfwInit()) {
        std::cerr << "GLFW 初始化失败！" << std::endl;
        return false;
    }
    initLightSystem();

    window = glfwCreateWindow(window_width, window_height, "界面", nullptr, nullptr);

    if (!window) {
        std::cerr << "窗口创建失败！" << std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    // 设置窗口调整函数
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); 
    glfwSwapInterval(1); // 垂直同步

    // 2. 初始化 ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // 使用微软自带的微软雅黑
    io.Fonts -> AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 14.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    
    // 默认设置为 深色模式
    ImGui::StyleColorsDark();
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cerr << "Failed to initialize ImGui for GLFW" << std::endl;
        return false;
    }
    
    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "Failed to initialize ImGui for OpenGL" << std::endl;
        return false;
    }

    // 3. 启用颜色
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // 4. 配置 OpenGL
    // 启动深色测试
    glEnable(GL_DEPTH_TEST);
    // 设置颜色混合模式及其参数
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 设置线段的渲染宽度
    glLineWidth(5);

    // 默认背景颜色为 天蓝色 天空
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    // 5. 启用纹理功能，并加载所有纹理
    glEnable(GL_TEXTURE_2D);
    loadTextures();

    // 6. 初始化天气系统
    weatherSystem.init(5000);  // 最多5000个粒子

    // 7. 初始化光照系统
    initLightSystem();

    // 8. 设置键盘处理函数
    glfwSetKeyCallback(window, keyCallback);

    // 9. 输出版本信息
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;

    return true;
}

// 渲染天气控制面板
void renderWeatherPanel() {
    // 假如不渲染天气，跳过渲染天气控制面板
    if (!showWeatherControls) {
        return ;
    }

    ImGui::Begin(
        "天气控制面板", 
        &showWeatherControls, 
        ImGuiWindowFlags_AlwaysAutoResize
    );
    
    WeatherState currentWeather = weatherSystem.getWeather();
    // 天气选择
    ImGui::Separator();
    ImGui::Text("天气选择");
    
    // 检测选择变量
    int selected = static_cast<int>(currentWeather);
    bool weatherChanged = false;
    
    // 使用互斥复选框，未被点击时，始终返回 false
    weatherChanged |= ImGui::RadioButton("晴天", &selected, WEATHER_SUNNY);
    ImGui::SameLine();
    weatherChanged |= ImGui::RadioButton("雨天", &selected, WEATHER_RAINING);
    ImGui::SameLine();
    weatherChanged |= ImGui::RadioButton("雪天", &selected, WEATHER_SNOWING);
    
    // 如果选择变化，更新天气系统
    if (weatherChanged) {
        WeatherState newWeather = static_cast<WeatherState>(selected);
        weatherSystem.setWeather(newWeather);
    }

    ImGui::End();
}

// 渲染调试控制面板
void renderDebugPanel() {
    /// 假如不需要调试，跳过渲染参数控制面板
    if (!showDebugInfo) {
        return ;
    }

    ImGui::Begin(
        "调试控制面板",
        &showDebugInfo,
        ImGuiWindowFlags_AlwaysAutoResize
    );

    ImGui::Text("相机控制");
    ImGui::DragFloat("相机距离", &camera_distance, CRMERA_DISTANCE_STEP_WIDTH, 500.0f, 5000.0f);
    ImGui::DragFloat("相机 X 轴偏移", &camera_offset[0], CRMERA_OFFSET_STEP_WIDTH, -2000.0f, 2000.0f);
    ImGui::DragFloat("相机 Y 轴偏移", &camera_offset[1], CRMERA_OFFSET_STEP_WIDTH, -2000.0f, 2000.0f);
    ImGui::DragFloat("相机 Z 轴偏移", &camera_offset[2], CRMERA_OFFSET_STEP_WIDTH, -2000.0f, 2000.0f);

    if (ImGui::Button("重置相机位置")) {
        camera_offset[0] = 0.0f;
        camera_offset[1] = 500.0f;
        camera_offset[2] = 0.0f;
    }

    ImGui::Separator();
    ImGui::Text("旋转控制");
    ImGui::DragFloat("X 轴旋转角度", &rotate_x, ANGLE_STEP_WIDTH, -1.57f, 1.57f);
    ImGui::DragFloat("Y 轴旋转角度", &rotate_y, ANGLE_STEP_WIDTH, -1.57f, 1.57f);

    if (ImGui::Button("重置旋转")) {
        rotate_x = 0.0f;
        rotate_y = 0.0f;
    }
    ImGui::Text("当前旋转角度: X=%.1f°, Y=%.1f°", rotate_x, rotate_y);

    ImGui::Separator();
    ImGui::Text("键盘控制:");
    ImGui::BulletText("方向键 ↑/↓: 控制X轴旋转");
    ImGui::BulletText("方向键 ←/→: 控制Y轴旋转");
    ImGui::BulletText("ESC: 退出程序");

    ImGui::End();
}

// 主渲染函数
void renderScene() {
    // 清除颜色和深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 设置投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // 使用透视投影，适合3D场景
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), 
        (float)window_width / (float)window_height, 
        1.0f, 
        5000.0f
    );

    glm::vec3 camera_pos = glm::vec3(
        camera_distance * sin(rotate_y) * cos(rotate_x) + camera_offset[0], 
        camera_distance * sin(rotate_x) + camera_offset[1],
        camera_distance * cos(rotate_y) * cos(rotate_x) + camera_offset[2]
    );

    glm::mat4 view = glm::lookAt(
        camera_pos,                     // 相机位置
        glm::vec3(0.0f, 0.0f, 0.0f),    // 观察目标
        glm::vec3(0.0f, 1.0f, 0.0f)     // 上向量
    );

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate_x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotate_y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-300.0f, -200.0f, -300.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    // 设置投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));

    // 设置模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glm::mat4 modelView = view * model;  // 注意：OpenGL使用列主序，矩阵乘法顺序为 view * model
    glLoadMatrixf(glm::value_ptr(modelView));

    // 保存当前矩阵状态
    glPushMatrix();  
    
    // 渲染雪积累效果（如果当前是雪天）
    weatherSystem.renderSnowAccumulation();
    
    // 绘制森林地面平台
    drawForestGround();
    
    // 绘制溪流河流
    drawRiver();
    
    // 恢复之前的矩阵状态
    glPopMatrix(); 

    // 绘制房子
    drawHouse();
    
    // 渲染雨积累效果
    weatherSystem.renderRainAccumulation();
}


// 主函数入口
int main() {
    if (!initProject()) {
        return -1;
    }
    lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        // 计算时间增量 
        auto currentTime = glfwGetTime();
        auto deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // 事件处理
        glfwPollEvents();

        // 开启 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // 渲染场景 
        renderScene();

        // 渲染天气面板
        renderWeatherPanel();

        // 渲染调试面板
        renderDebugPanel();

        // 渲染 ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 交换缓冲
        glfwSwapBuffers(window);
    }

    // 资源清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}