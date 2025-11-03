#ifndef PLANTVISUALSTRATEGY_H
#define PLANTVISUALSTRATEGY_H

#pragma once

#include "raylib.h"
#include <math.h>

// --- General Constants ---
#define PI 3.14159265358979323846f
<<<<<<< HEAD
#define STATIC_ICON_SIZE 16.0f

// Helper to interpolate colors (Assuming this utility is available globally)
inline Color ColorLerp(Color c1, Color c2, float t)
{
    t = fmaxf(0.0f, fminf(1.0f, t));
    return (Color){
=======
#define STATIC_ICON_SIZE 32.0f

// Helper to interpolate colors (Assuming this utility is available globally)
inline Color PlantColorLerp(Color c1, Color c2, float t)
{
    t = fmaxf(0.0f, fminf(1.0f, t));
    return Color{
>>>>>>> origin/Frontend
        (unsigned char)(c1.r + (c2.r - c1.r) * t),
        (unsigned char)(c1.g + (c2.g - c1.g) * t),
        (unsigned char)(c1.b + (c2.b - c1.b) * t),
        (unsigned char)(c1.a + (c2.a - c1.a) * t)};
}

// --- Base Abstract Strategy Class ---
class PlantVisualStrategy
{
protected:
    float currentWidth;
    float currentHeight;
    float growthProgress; // 0.0 to 1.0 (from PlantState::getGrowth() / 100.0f)
    bool isCurrentlyDead;

    // Helper for applying death filter
    Color applyDeathFilter(Color baseColor) const
    {
        if (isCurrentlyDead)
        {
            // Fades color towards a dark, unhealthy brown/black
<<<<<<< HEAD
            return ColorLerp(baseColor, Color{50, 40, 30, 255}, 0.8f);
=======
            return PlantColorLerp(baseColor, Color{50, 40, 30, 255}, 0.8f);
>>>>>>> origin/Frontend
        }
        return baseColor;
    }

public:
    PlantVisualStrategy(float width, float height) : currentWidth(width), currentHeight(height), growthProgress(0.0f), isCurrentlyDead(false) {}
    virtual ~PlantVisualStrategy() = default;

    void setGrowth(float progress) { growthProgress = fmaxf(0.0f, fminf(1.0f, progress)); }
    void setDimensions(float width, float height)
    {
        currentWidth = width;
        currentHeight = height;
    }
    void setDead(bool dead) { isCurrentlyDead = dead; }

    // DYNAMIC VISUAL: Uses growth and death state (for in-plot rendering)
    virtual void drawDetailed(float x, float y) = 0;

    // STATIC VISUAL: Used for menus/icons, fixed size, fixed color (for clarity)
    virtual void drawStatic(float x, float y) = 0;
};

// --- Concrete Visual Strategies ---

// ============ LETTUCE ============
class LettuceVisualStrategy : public PlantVisualStrategy
{
public:
    LettuceVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
<<<<<<< HEAD
        Color color = applyDeathFilter(ColorLerp(DARKGREEN, LIME, growthProgress * 0.3f + 0.7f));
=======
        Color color = applyDeathFilter(PlantColorLerp(DARKGREEN, LIME, growthProgress * 0.3f + 0.7f));
>>>>>>> origin/Frontend
        DrawCircle(x, y - currentHeight * 0.3f, currentWidth * 0.5f, color);

        if (growthProgress > 0.3f)
        {
            float leafDensity = growthProgress * 8.0f;
            for (int i = 0; i < (int)leafDensity; i++)
            {
                float angle = (i / leafDensity) * 360.0f;
                float leafX = x + cosf(angle * PI / 180.0f) * currentWidth * 0.35f;
                float leafY = y - currentHeight * 0.2f + sinf(angle * PI / 180.0f) * currentHeight * 0.2f;
                DrawCircle(leafX, leafY, currentWidth * 0.15f, color);
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawCircle(x, y, STATIC_ICON_SIZE * 0.5f, DARKGREEN);
        DrawCircle(x, y, STATIC_ICON_SIZE * 0.3f, LIME);
    }
};

// ============ CARROT ============
class CarrotVisualStrategy : public PlantVisualStrategy
{
public:
    CarrotVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
<<<<<<< HEAD
        Color rootColor = applyDeathFilter(ColorLerp(ORANGE, Color{255, 150, 0, 255}, growthProgress));
=======
        Color rootColor = applyDeathFilter(PlantColorLerp(ORANGE, Color{255, 150, 0, 255}, growthProgress));
>>>>>>> origin/Frontend
        float rootWidth = currentWidth * 0.6f;
        DrawTriangle(Vector2{x - rootWidth / 2, y - currentHeight * 0.7f}, Vector2{x + rootWidth / 2, y - currentHeight * 0.7f}, Vector2{x, y}, rootColor);

        if (growthProgress > 0.2f)
        {
<<<<<<< HEAD
            Color leafColor = applyDeathFilter(ColorLerp(DARKGREEN, LIME, growthProgress * 0.5f));
=======
            Color leafColor = applyDeathFilter(PlantColorLerp(DARKGREEN, LIME, growthProgress * 0.5f));
>>>>>>> origin/Frontend
            for (int i = 0; i < 5; i++)
            {
                float angle = (i / 5.0f) * 180.0f - 90.0f;
                float leafLen = currentHeight * 0.4f * growthProgress;
                float startX = x + cosf(angle * PI / 180.0f) * currentWidth * 0.2f;
                float startY = y - currentHeight * 0.7f;
                float endX = startX + cosf(angle * PI / 180.0f) * leafLen;
                float endY = startY + sinf(angle * PI / 180.0f) * leafLen;
                DrawLineEx(Vector2{startX, startY}, Vector2{endX, endY}, 3.0f, leafColor);
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawTriangle(Vector2{x - STATIC_ICON_SIZE * 0.3f, y + STATIC_ICON_SIZE * 0.5f}, Vector2{x + STATIC_ICON_SIZE * 0.3f, y + STATIC_ICON_SIZE * 0.5f}, Vector2{x, y - STATIC_ICON_SIZE * 0.5f}, ORANGE);
        DrawRectangle(x - 2, y - STATIC_ICON_SIZE * 0.5f, 4, 8, DARKGREEN);
    }
};

// ============ POTATO ============
class PotatoVisualStrategy : public PlantVisualStrategy
{
public:
    PotatoVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
<<<<<<< HEAD
        Color potatoColor = applyDeathFilter(ColorLerp(Color{139, 90, 43, 255}, Color{180, 120, 60, 255}, growthProgress));
=======
        Color potatoColor = applyDeathFilter(PlantColorLerp(Color{139, 90, 43, 255}, Color{180, 120, 60, 255}, growthProgress));
>>>>>>> origin/Frontend
        DrawCircle(x, y, currentWidth * 0.5f, potatoColor);

        // Bumpy texture
        float bumpSize = currentWidth * 0.1f;
        for (int i = 0; i < 4; i++)
        {
            float angle = (i / 4.0f) * 360.0f;
            float bumpX = x + cosf(angle * PI / 180.0f) * currentWidth * 0.35f;
            float bumpY = y + sinf(angle * PI / 180.0f) * currentWidth * 0.3f;
            DrawCircle(bumpX, bumpY, bumpSize, Color{160, 110, 70, 255});
        }

        // Green sprouts on top
        if (growthProgress > 0.25f)
        {
<<<<<<< HEAD
            Color sproutColor = applyDeathFilter(ColorLerp(DARKGREEN, LIME, growthProgress * 0.6f));
=======
            Color sproutColor = applyDeathFilter(PlantColorLerp(DARKGREEN, LIME, growthProgress * 0.6f));
>>>>>>> origin/Frontend
            int sproutCount = 2 + (int)(growthProgress * 3.0f);
            for (int i = 0; i < sproutCount; i++)
            {
                float angle = (i / (float)sproutCount) * 180.0f;
                float sproutLen = currentHeight * 0.8f * growthProgress;
                float startX = x + cosf(angle * PI / 180.0f) * currentWidth * 0.2f;
                float startY = y - currentWidth * 0.5f;
                float endX = startX + cosf(angle * PI / 180.0f) * sproutLen;
                float endY = startY - sproutLen;
                DrawLineEx(Vector2{startX, startY}, Vector2{endX, endY}, 2.5f, sproutColor);
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawCircle(x, y, STATIC_ICON_SIZE * 0.5f, BROWN);
        DrawCircle(x + STATIC_ICON_SIZE * 0.3f, y - STATIC_ICON_SIZE * 0.3f, 4, LIME);
    }
};

// ============ CUCUMBER ============
class CucumberVisualStrategy : public PlantVisualStrategy
{
public:
    CucumberVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
<<<<<<< HEAD
        Color cucColor = applyDeathFilter(ColorLerp(DARKGREEN, LIME, growthProgress * 0.4f + 0.6f));
=======
        Color cucColor = applyDeathFilter(PlantColorLerp(DARKGREEN, LIME, growthProgress * 0.4f + 0.6f));
>>>>>>> origin/Frontend
        DrawRectangleRounded(
            Rectangle{x - currentWidth / 2, y - currentHeight, currentWidth, currentHeight}, // Corrected: Only 4 values
            0.5f, 8, cucColor);

        // Bumpy texture
        float bumpCount = 8.0f * growthProgress;
        for (int i = 0; i < (int)bumpCount; i++)
        {
            float yPos = y - currentHeight + (i / bumpCount) * currentHeight;
            float offset = (i % 2) ? currentWidth * 0.3f : -currentWidth * 0.3f;
            DrawCircle(x + offset, yPos, 4.0f, Color{34, 139, 34, 255});
        }

        // Curling vine when mature
        if (growthProgress > 0.4f)
        {
            Color vineColor = DARKGREEN;
            float vineLen = currentHeight * 0.5f * growthProgress;
            for (float t = 0.0f; t < 1.0f; t += 0.05f)
            {
                float angle = t * 720.0f * PI / 180.0f;
                float vX1 = x + currentWidth / 2 + cosf(angle) * 15.0f;
                float vY1 = y - currentHeight - t * vineLen;
                float vX2 = x + currentWidth / 2 + cosf(angle + 0.1f) * 15.0f;
                float vY2 = y - currentHeight - (t + 0.05f) * vineLen;
                DrawLineEx(Vector2{vX1, vY1}, Vector2{vX2, vY2}, 2.0f, vineColor);
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawRectangle(x - STATIC_ICON_SIZE * 0.15f, y - STATIC_ICON_SIZE * 0.5f, STATIC_ICON_SIZE * 0.3f, STATIC_ICON_SIZE, DARKGREEN);
        DrawCircle(x + STATIC_ICON_SIZE * 0.15f, y - STATIC_ICON_SIZE * 0.3f, 3, LIME);
    }
};

// ============ TOMATO ============
class TomatoVisualStrategy : public PlantVisualStrategy
{
public:
    TomatoVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
        Color stemColor = applyDeathFilter(DARKGREEN);
<<<<<<< HEAD
        Color fruitColor = applyDeathFilter(ColorLerp(ORANGE, RED, growthProgress * 0.7f + 0.3f));
=======
        Color fruitColor = applyDeathFilter(PlantColorLerp(ORANGE, RED, growthProgress * 0.7f + 0.3f));
>>>>>>> origin/Frontend

        DrawLineEx(Vector2{x, y}, Vector2{x, y - currentHeight}, 4.0f, stemColor);

        float branchCount = 2.0f + growthProgress * 2.0f;
        for (int i = 0; i < (int)branchCount; i++)
        {
            float angle = (i / branchCount) * 180.0f - 90.0f + 30.0f;
            float branchLen = currentHeight * 0.4f;
            float branchX = x + cosf(angle * PI / 180.0f) * branchLen;
            float branchY = y - currentHeight * 0.5f + sinf(angle * PI / 180.0f) * branchLen;
            DrawLineEx(Vector2{x}, Vector2{branchX, branchY}, 2.0f, stemColor);

            if (growthProgress > 0.5f)
            {
                DrawCircle(branchX, branchY, currentWidth * 0.25f, fruitColor);
                DrawCircle(branchX + 5, branchY - 5, 2.0f, YELLOW);
            }
        }

        if (growthProgress > 0.4f)
        {
            DrawCircle(x, y - currentHeight * 0.3f, currentWidth * 0.35f, fruitColor);
            DrawCircle(x + 7, y - currentHeight * 0.3f - 7, 3.0f, YELLOW);
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawCircle(x, y, STATIC_ICON_SIZE * 0.5f, DARKGREEN);
        DrawCircle(x, y - STATIC_ICON_SIZE * 0.2f, STATIC_ICON_SIZE * 0.3f, RED);
    }
};

// ============ PEPPER ============
class PepperVisualStrategy : public PlantVisualStrategy
{
public:
    PepperVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
        Color stemColor = applyDeathFilter(DARKGREEN);
<<<<<<< HEAD
        Color pepperColor = applyDeathFilter(ColorLerp(DARKGREEN, Color{255, 165, 0, 255}, growthProgress * 0.8f));
=======
        Color pepperColor = applyDeathFilter(PlantColorLerp(DARKGREEN, Color{255, 165, 0, 255}, growthProgress * 0.8f));
>>>>>>> origin/Frontend

        DrawLineEx(Vector2{x, y}, Vector2{x, y - currentHeight * 0.3f}, 3.0f, stemColor);

        float pepperY = y - currentHeight * 0.5f;
        DrawRectangleRounded(
            Rectangle{x - currentWidth / 2, pepperY - currentHeight * 0.5f, currentWidth, currentHeight * 0.6f}, // Corrected
            0.4f, 8, pepperColor                                                                                 // The '0.4f' is the roundness factor
        );

        if (growthProgress > 0.3f)
        {
            float ridgeCount = 4.0f;
            for (int i = 0; i < (int)ridgeCount; i++)
            {
                float ridgeX = x - currentWidth * 0.35f + (i / ridgeCount) * currentWidth * 0.7f;
                DrawLineEx(Vector2{ridgeX, pepperY - currentHeight * 0.5f}, Vector2{ridgeX, pepperY + currentHeight * 0.1f}, 1.5f, Color{200, 140, 70, 255});
            }
        }

        for (int i = 0; i < 4; i++)
        {
            float angle = (i / 4.0f) * 360.0f;
            float tipX = x + cosf(angle * PI / 180.0f) * currentWidth * 0.2f;
            float tipY = pepperY - currentHeight * 0.5f - 5;
            DrawCircle(tipX, tipY, 3.0f, stemColor);
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawRectangle(x - STATIC_ICON_SIZE * 0.25f, y - STATIC_ICON_SIZE * 0.5f, STATIC_ICON_SIZE * 0.5f, STATIC_ICON_SIZE, ORANGE);
        DrawCircle(x, y - STATIC_ICON_SIZE * 0.5f, 4, DARKGREEN);
    }
};

// ============ SUNFLOWER ============
class SunflowerVisualStrategy : public PlantVisualStrategy
{
public:
    SunflowerVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
        Color stemColor = applyDeathFilter(DARKGREEN);
        Color petalColor = YELLOW;
        Color centerColor = applyDeathFilter(Color{184, 134, 11, 255});

        DrawLineEx(Vector2{x, y}, Vector2{x, y - currentHeight}, 5.0f, stemColor);

        if (growthProgress > 0.2f)
        {
            int leafCount = 3 + (int)(growthProgress * 2.0f);
            for (int i = 0; i < leafCount; i++)
            {
                float leafY = y - (i / (float)leafCount) * currentHeight * 0.8f;
                float angle = (i % 2) ? 45.0f : -45.0f;
                float leafLen = currentWidth * 0.4f;
                float leafX = x + cosf(angle * PI / 180.0f) * leafLen;
                float leafEndY = leafY + sinf(angle * PI / 180.0f) * leafLen;
                DrawLineEx(Vector2{x, leafY}, Vector2{leafX, leafEndY}, 3.0f, stemColor);
            }
        }

        if (growthProgress > 0.5f)
        {
            float flowerRadius = currentWidth * 0.5f * growthProgress;
            int petalCount = 16 + (int)(growthProgress * 8.0f);
            for (int i = 0; i < petalCount; i++)
            {
                float angle = (i / (float)petalCount) * 360.0f;
                float startX = x + cosf(angle * PI / 180.0f) * flowerRadius * 0.3f;
                float startY = y - currentHeight + sinf(angle * PI / 180.0f) * flowerRadius * 0.3f;
                float endX = x + cosf(angle * PI / 180.0f) * flowerRadius;
                float endY = y - currentHeight + sinf(angle * PI / 180.0f) * flowerRadius;
                DrawTriangle(Vector2{startX - 3, startY}, Vector2{startX + 3, startY}, Vector2{endX, endY}, petalColor);
            }

            DrawCircle(x, y - currentHeight, flowerRadius * 0.35f, centerColor);

            int seedCount = 30 * growthProgress;
            for (int i = 0; i < (int)seedCount; i++)
            {
                float seedAngle = (i / (float)seedCount) * 360.0f;
                float seedDist = 5.0f + (i % 3) * 3.0f;
                float seedX = x + cosf(seedAngle * PI / 180.0f) * seedDist;
                float seedY = y - currentHeight + sinf(seedAngle * PI / 180.0f) * seedDist;
                DrawCircle(seedX, seedY, 1.5f, Color{139, 90, 43, 255});
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawCircle(x, y - STATIC_ICON_SIZE * 0.3f, STATIC_ICON_SIZE * 0.3f, YELLOW);
        DrawCircle(x, y - STATIC_ICON_SIZE * 0.3f, STATIC_ICON_SIZE * 0.15f, Color{184, 134, 11, 255});
        DrawRectangle(x - 2, y - STATIC_ICON_SIZE * 0.3f, 4, STATIC_ICON_SIZE * 0.5f, DARKGREEN);
    }
};

// ============ CORN ============
class CornVisualStrategy : public PlantVisualStrategy
{
public:
    CornVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
        Color stalkColor = applyDeathFilter(DARKGREEN);
        Color leafColor = applyDeathFilter(LIME);
        Color earColor = applyDeathFilter(YELLOW);

        // Main stalk
        DrawLineEx(Vector2{x, y}, Vector2{x, y - currentHeight}, 6.0f, stalkColor);

        // Leaves along stalk (Restored original logic)
        int leafCount = 4 + (int)(growthProgress * 4.0f);
        for (int i = 0; i < leafCount; i++)
        {
            float leafY = y - (i / (float)leafCount) * currentHeight * 0.85f;
            float angle = (i % 2) ? 40.0f : -40.0f;
            float leafLen = currentWidth * 0.6f;
            
            // --- RESTORED LEAF BLADE DRAWING ---
            DrawRectangleRounded(
                Rectangle{x, leafY, leafLen * 0.7f, currentWidth * 0.4f},
                0.3f, 4, leafColor
            );
        }

        // Corn ear (cob with kernels) - Only visible when grown
        if (growthProgress > 0.5f)
        {
            // --- earX and earY are defined here, ensuring scope is correct ---
            float earY = y - currentHeight * 0.4f;
            float earX = x + currentWidth * 0.4f;

            // Cob (DrawRectangleRounded is now correct)
            DrawRectangleRounded(
                Rectangle{earX - 8, earY - 15, 16, 30}, 
                0.5f, 4, Color{184, 134, 11, 255});

            int kernelRows = 6;
            int kernelCols = 4;
            for (int row = 0; row < kernelRows; row++)
            {
                for (int col = 0; col < kernelCols; col++)
                {
                    float kX = earX - 6 + col * 3.0f;
                    float kY = earY - 12 + row * 5.0f;
                    DrawCircle(kX, kY, 1.5f, earColor);
                }
            }

            for (int i = 0; i < 4; i++)
            {
                float silkX = earX + 10 + i * 3;
                float silkY = earY;
                DrawLineEx(Vector2{silkX, silkY}, Vector2{silkX + 15, silkY + 10}, 1.5f, Color{210, 180, 140, 255});
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawRectangle(x - 3, y - STATIC_ICON_SIZE * 0.5f, 6, STATIC_ICON_SIZE, DARKGREEN);
        DrawRectangle(x + 5, y - 5, 4, 10, YELLOW);
    }
};
// ============ STRAWBERRY ============
class StrawberryVisualStrategy : public PlantVisualStrategy
{
public:
    StrawberryVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
        Color leafColor = applyDeathFilter(DARKGREEN);
<<<<<<< HEAD
        Color fruitColor = applyDeathFilter(ColorLerp(ORANGE, RED, growthProgress * 0.8f + 0.2f));
=======
        Color fruitColor = applyDeathFilter(PlantColorLerp(ORANGE, RED, growthProgress * 0.8f + 0.2f));
>>>>>>> origin/Frontend

        int leafCount = 6 + (int)(growthProgress * 3.0f);
        for (int i = 0; i < leafCount; i++)
        {
            float angle = (i / (float)leafCount) * 360.0f;
            float leafLen = currentHeight * 0.4f * growthProgress;
            float endX = x + cosf(angle * PI / 180.0f) * leafLen;
            float endY = y - sinf(angle * PI / 180.0f) * leafLen;
            DrawLineEx(Vector2{x, y}, Vector2{endX, endY}, 3.0f, leafColor);
        }

        if (growthProgress > 0.4f)
        {
            int berryCount = 1 + (int)(growthProgress * 2.0f);
            for (int i = 0; i < berryCount; i++)
            {
                float angle = (i / (float)berryCount) * 360.0f - 90.0f;
                float berryDist = currentWidth * 0.3f;
                float berryX = x + cosf(angle * PI / 180.0f) * berryDist;
                float berryY = y - currentHeight * 0.2f + sinf(angle * PI / 180.0f) * berryDist;

                DrawCircle(berryX - 5, berryY - 3, 6.0f, fruitColor);
                DrawCircle(berryX + 5, berryY - 3, 6.0f, fruitColor);
                DrawCircle(berryX, berryY + 4, 7.0f, fruitColor);

                DrawCircle(berryX - 3, berryY, 1.5f, YELLOW);
                DrawCircle(berryX + 3, berryY, 1.5f, YELLOW);
                DrawCircle(berryX, berryY + 3, 1.5f, YELLOW);
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawCircle(x, y, STATIC_ICON_SIZE * 0.5f, DARKGREEN);
        DrawCircle(x, y + STATIC_ICON_SIZE * 0.2f, STATIC_ICON_SIZE * 0.3f, RED);
    }
};

// ============ PUMPKIN ============
class PumpkinVisualStrategy : public PlantVisualStrategy
{
public:
    PumpkinVisualStrategy(float width, float height) : PlantVisualStrategy(width, height) {}

    void drawDetailed(float x, float y) override
    {
<<<<<<< HEAD
        Color pumpkinColor = applyDeathFilter(ColorLerp(ORANGE, Color{255, 100, 0, 255}, growthProgress * 0.5f));
=======
        Color pumpkinColor = applyDeathFilter(PlantColorLerp(ORANGE, Color{255, 100, 0, 255}, growthProgress * 0.5f));
>>>>>>> origin/Frontend
        Color vineColor = applyDeathFilter(DARKGREEN);
        Color leafColor = applyDeathFilter(LIME);

        float pumpkinRadius = currentWidth * 0.5f;

        int ridgeCount = 8 + (int)(growthProgress * 4.0f);
        for (int i = 0; i < ridgeCount; i++)
        {
            float angle = (i / (float)ridgeCount) * 360.0f;
            float startX = x + cosf(angle * PI / 180.0f) * pumpkinRadius * 0.7f;
            float startY = y - currentHeight * 0.3f + sinf(angle * PI / 180.0f) * pumpkinRadius * 0.7f;
            float endX = x + cosf(angle * PI / 180.0f) * pumpkinRadius;
            float endY = y - currentHeight * 0.3f + sinf(angle * PI / 180.0f) * pumpkinRadius;
            DrawLineEx(Vector2{startX, startY}, Vector2{endX, endY}, 2.0f, Color{200, 80, 0, 255});
        }

        DrawCircle(x, y - currentHeight * 0.3f, pumpkinRadius * 0.9f, pumpkinColor);
        DrawCircle(x - pumpkinRadius * 0.4f, y - currentHeight * 0.3f, pumpkinRadius * 0.8f, pumpkinColor);
        DrawCircle(x + pumpkinRadius * 0.4f, y - currentHeight * 0.3f, pumpkinRadius * 0.8f, pumpkinColor);

        float stemLen = currentHeight * 0.4f;
        DrawLineEx(Vector2{x, y - currentHeight * 0.3f - pumpkinRadius}, Vector2{x, y - currentHeight * 0.3f - pumpkinRadius - stemLen}, 5.0f, vineColor);

        if (growthProgress > 0.3f)
        {
            float vineLength = currentWidth * growthProgress;
            float vineStartX = x + pumpkinRadius * 0.5f;
            float vineStartY = y - currentHeight * 0.3f;

            for (float t = 0.0f; t < 1.0f; t += 0.05f)
            {
                float angle = t * 1080.0f * PI / 180.0f;
                float vX1 = vineStartX + cosf(angle) * 20.0f;
                float vY1 = vineStartY + t * vineLength;
                float vX2 = vineStartX + cosf(angle + 0.1f) * 20.0f;
                float vY2 = vineStartY + (t + 0.05f) * vineLength;
                DrawLineEx(Vector2{vX1, vY1}, Vector2{vX2, vY2}, 3.0f, vineColor);
            }
        }
    }
    void drawStatic(float x, float y) override
    {
        DrawCircle(x, y, STATIC_ICON_SIZE * 0.5f, ORANGE);
        DrawRectangle(x - 2, y - STATIC_ICON_SIZE * 0.6f, 4, 8, DARKGREEN);
    }
};

#endif // PLANTVISUALSTRATEGY_H