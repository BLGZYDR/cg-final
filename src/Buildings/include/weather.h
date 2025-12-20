#ifndef RAIN_H
#define RAIN_H

#include "headers.h"

// 天气状态枚举
enum WeatherState {
    WEATHER_SUNNY = 0,   // 晴天
    WEATHER_RAINING = 1, // 下雨
    WEATHER_SNOWING = 2  // 下雪
};

// 粒子结构体
struct WeatherParticle {
    float x, y, z;          // 位置
    float vx, vy, vz;       // 速度
    float life;             // 生命周期
    float size;             // 粒子大小
    bool active;            // 是否活跃
    int type;               // 粒子类型：0-雨滴，1-水花，2-雪花
};

// 天气系统类（现在包含下雨和下雪）
class WeatherSystem {
private:
    std::vector<WeatherParticle> particles;
    float snowAccumulation;  // 积雪厚度

    // 创建新的雨滴粒子
    void createRaindrop();

    // 创建新的雪花粒子
    void createSnowflake();

    // 创建水花粒子
    void createSplash(float x, float y, float z);

public:
    WeatherSystem();
    ~WeatherSystem();

    WeatherState currentWeather;

    // 初始化系统
    void init(int maxParticles = 5000);

    // 更新粒子系统
    void update(float deltaTime);

    // 绘制粒子
    void renderRainAccumulation();

    // 绘制积雪效果
    void renderSnowAccumulation();

    // 设置天气状态
    void setWeather(WeatherState state);

    // 获取当前天气状态
    WeatherState getWeather() const;

    // 清除所有粒子
    void clear();

    // 清除积雪
    void clearSnow();
};

// 全局天气系统实例
extern WeatherSystem weatherSystem;

#endif
