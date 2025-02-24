#include <cmath>
#include <iostream>
#include <vector>

#include "../include//mk-array.hpp"

struct SkPoint {
    float fX{0};
    float fY{0};
};

// 计算两个 SkPoint 的点积
double dotProduct(const SkPoint& v1, const SkPoint& v2) {
    return v1.fX * v2.fX + v1.fY * v2.fY;
}

// 计算两个 SkPoint 的叉积
double crossProduct(const SkPoint& v1, const SkPoint& v2) {
    return v1.fX * v2.fY - v1.fY * v2.fX;
}

// 检测是否“经过” v_start
bool isPassingThrough(const SkPoint& v_start, const SkPoint& v_end, const SkPoint& v_prev,
                      double threshold = 0.9999) {
    // 计算点积
    double dot = dotProduct(v_start, v_end);

    // 计算旋转方向
    double cross = crossProduct(v_prev, v_end);
    int current_direction = (cross > 0) ? 1 : -1;  // 1 表示逆时针，-1 表示顺时针

    // 判断是否接近 v_start
    if (dot > threshold) {
        // 记录旋转方向
        static int rotation_direction = 0;
        static bool is_near_start = false;

        if (!is_near_start) {
            // 第一次接近 v_start，记录旋转方向
            rotation_direction = current_direction;
            is_near_start = true;
        }

        // 离开 v_start，检查是否沿同一方向离开
        if (is_near_start && current_direction == rotation_direction) {
            is_near_start = false;  // 重置状态
            return true;            // 算“经过”
        }
    }

    return false;  // 不算“经过”
}

int main() {
    // 固定开始向量
    SkPoint v_start = {1.0f, 0.0f};  // 单位向量 (1, 0)

    // 模拟动态传入的结束向量
    std::vector<SkPoint> v_end_list = {
        {1.0f, 0.0f},       // 重合
        {0.9998f, 0.02f},   // 接近
        {0.9999f, 0.01f},   // 更接近
        {1.0f, 0.0f},       // 重合
        {0.9999f, -0.01f},  // 离开
        {0.9998f, -0.02f}   // 继续离开
    };

    SkPoint v_prev = {1.0f, 0.0f};  // 上一个 v_end

    for (const auto& v_end : v_end_list) {
        if (isPassingThrough(v_start, v_end, v_prev)) {
            std::cout << "v_end passed through v_start at: (" << v_end.fX << ", " << v_end.fY
                      << ")\n";
        }
        v_prev = v_end;  // 更新上一个 v_end
    }
    return 0;
}
