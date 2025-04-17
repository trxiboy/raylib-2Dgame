#ifndef CALCULATIONS_
#define CALCULATIONS_

#include <raylib.h>
#include <cmath>

inline Vector2 LerpPosition(Vector2 startPos, Vector2 endPos, float t) {
    float x = startPos.x + t * (endPos.x - startPos.x);
    float y = startPos.y + t * (endPos.y - startPos.y);
    return {x, y};
}

inline Vector2 NormalizeVector(Vector2 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y);
    if (length == 0) return (Vector2){0, 0};
    return (Vector2){v.x / length, v.y / length};
}

inline Vector2 GetRectRandomPosition(const Rectangle& rect) {
    return {
        (float)GetRandomValue((int)rect.x, (int)(rect.x + rect.width)), 
        (float)GetRandomValue((int)rect.y, (int)(rect.y + rect.height))
    };
}


inline float Distance(Vector2 start, Vector2 end) {
    return sqrtf((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

inline float GetRotationAngle(Vector2 startPos, Vector2 endPos) {
    float deltaX = endPos.x - startPos.x;
    float deltaY = endPos.y - startPos.y;
    
    float angleRad = atan2(deltaY, deltaX);
    float angleDeg = angleRad * (180.0f / 3.14);

    return angleDeg;
}


#endif