#pragma once

// Libraries:
#include <raylib.h>
#include <string>

using std::string;


// Window Class:
class Window {
    public:
        // Public Variables:
        int defaultPixel = 16;
        float worldScale = 6.0f;

        Vector2 windowSize;
        string windowTitle;

        // Window Constructor:
        Window(Vector2 size, string title) {   
            InitWindow(size.x, size.y, title.c_str());
            SetTargetFPS(60);

            windowSize = size;
            windowTitle = title;
        }

        // Clear Window:
        void Clear() {
            ClearBackground(Color{120, 159, 222, 255});
        }
};