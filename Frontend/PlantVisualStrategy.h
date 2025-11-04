#ifndef PLANTVISUALSTRATEGY_H
#define PLANTVISUALSTRATEGY_H

#pragma once

#include "raylib.h"
#include <math.h>

// --- General Constants ---
/** @brief The mathematical constant Pi, used for trigonometric calculations. */
#define PI 3.14159265358979323846f
/** @brief The standardized size for rendering plant icons in the UI. */
#define STATIC_ICON_SIZE 32.0f

/**
 * @brief Helper function to perform linear interpolation (Lerp) between two colors.
 * @param c1 The starting color.
 * @param c2 The ending color.
 * @param t The interpolation factor (clamped between 0.0 and 1.0).
 * @return The interpolated Color.
 */
inline Color PlantColorLerp(Color c1, Color c2, float t)
{
    t = fmaxf(0.0f, fminf(1.0f, t));
    return Color{
        (unsigned char)(c1.r + (c2.r - c1.r) * t),
        (unsigned char)(c1.g + (c2.g - c1.g) * t),
        (unsigned char)(c1.b + (c2.b - c1.b) * t),
        (unsigned char)(c1.a + (c2.a - c1.a) * t)};
}

// --- Base Abstract Strategy Class ---
/**
 * @class PlantVisualStrategy
 * @brief The **Abstract Strategy** interface for rendering plant visuals.
 *
 * All concrete plant rendering strategies must inherit from this class and implement the pure virtual methods.
 */
class PlantVisualStrategy
{
protected:
    /** @brief The calculated width of the plant at the current growth stage. */
    float currentWidth;
    /** @brief The calculated height of the plant at the current growth stage. */
    float currentHeight;
    /** @brief The growth progress of the plant (0.0 to 1.0) used for scaling visuals. */
    float growthProgress; 
    /** @brief Flag indicating if the plant is currently dead (used to apply a visual filter). */
    bool isCurrentlyDead;

    /**
     * @brief Helper for applying a gray/brown filter to a color if the plant is dead.
     * @param baseColor The original color to filter.
     * @return The filtered color, or the original color if the plant is alive.
     */
    Color applyDeathFilter(Color baseColor) const
    {
        if (!isCurrentlyDead) return baseColor;
        
        // Simple grayscale/brown filter for dead plants
        unsigned char r = baseColor.r;
        unsigned char g = baseColor.g;
        unsigned char b = baseColor.b;
        
        // Simple conversion to gray
        unsigned char avg = (r + g + b) / 3;

        return Color{
            (unsigned char)fminf(255, avg + 50), // Light brown/gray R
            (unsigned char)fminf(255, avg * 0.5f), // Darker G
            (unsigned char)fminf(255, avg * 0.3f), // Darkest B
            baseColor.a
        };
    }

public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~PlantVisualStrategy() = default;

    /**
     * @brief Sets the state parameters required for rendering the plant.
     * * This method must be called before calling render or renderIcon.
     * @param width The base plot width.
     * @param height The base plot height.
     * @param growth The plant's growth percentage (0.0 to 100.0).
     * @param dead True if the plant is dead, false otherwise.
     */
    virtual void setRenderState(float width, float height, float growth, bool dead)
    {
        currentWidth = width;
        currentHeight = height;
        growthProgress = fmaxf(0.0f, fminf(1.0f, growth / 100.0f));
        isCurrentlyDead = dead;
    }

    /**
     * @brief Pure virtual function to render the plant in the world scene.
     * @param x The center X-coordinate of the plant plot.
     * @param y The center Y-coordinate of the plant plot.
     */
    virtual void render(float x, float y) const = 0;

    /**
     * @brief Pure virtual function to render a small icon representation of the plant (e.g., for inventory).
     * @param x The center X-coordinate of the icon draw area.
     * @param y The center Y-coordinate of the icon draw area.
     */
    virtual void renderIcon(float x, float y) const = 0;
};

// --- Concrete Strategy Implementations ---

/**
 * @class BasicPlantVisualStrategy
 * @brief A **Concrete Strategy** providing simple, color-based visual representation for a basic plant.
 *
 * Renders the plant as a simple circle that scales with growth and applies color based on the state.
 */
class BasicPlantVisualStrategy : public PlantVisualStrategy
{
private:
    /** @brief The base color of the plant (e.g., green for leaves). */
    Color baseColor;
    /** @brief The color of the soil or pot beneath the plant. */
    Color dirtColor;

public:
    /**
     * @brief Constructor.
     * @param plantColor The primary color for the plant's foliage.
     * @param soilColor The color for the base/dirt.
     */
    BasicPlantVisualStrategy(Color plantColor, Color soilColor)
        : baseColor(plantColor), dirtColor(soilColor) {}

    /**
     * @brief Renders the basic plant visual using a scaled circle.
     * @param x The center X-coordinate.
     * @param y The center Y-coordinate.
     */
    void render(float x, float y) const override
    {
        float size = currentWidth * growthProgress * 0.7f;
        
        // Draw the base (soil/pot)
        DrawCircle(x, y + currentHeight * 0.1f, currentWidth * 0.3f, dirtColor);

        // Draw the foliage, applying the death filter if necessary
        Color finalColor = applyDeathFilter(baseColor);
        DrawCircle(x, y - currentHeight * 0.1f, size, finalColor);
        
        if (isCurrentlyDead) {
            DrawText("X", x - 5, y - currentHeight * 0.1f - 10, 20, RED);
        }
    }

    /**
     * @brief Renders the basic plant as a small icon.
     * @param x The center X-coordinate.
     * @param y The center Y-coordinate.
     */
    void renderIcon(float x, float y) const override
    {
        float size = STATIC_ICON_SIZE * 0.4f;
        Color finalColor = applyDeathFilter(baseColor);
        
        // Draw background soil/pot
        DrawRectangle(x - size, y, size * 2, size * 0.5f, dirtColor);
        // Draw foliage
        DrawCircle(x, y - size * 0.5f, size, finalColor);
    }
};

/**
 * @class PumpkinVisualStrategy
 * @brief A **Concrete Strategy** for a pumpkin, using specific shapes and growth stages.
 */
class PumpkinVisualStrategy : public PlantVisualStrategy
{
private:
    /** @brief The color of the pumpkin fruit. */
    Color pumpkinColor;
    /** @brief The color of the vines/stem. */
    Color vineColor;

public:
    /**
     * @brief Constructor.
     */
    PumpkinVisualStrategy()
        : pumpkinColor({255, 140, 0, 255}), // Orange
          vineColor({34, 139, 34, 255}) {}   // Green

    /**
     * @brief Renders a stylized pumpkin visual that grows from a seed to a large fruit.
     * @param x The center X-coordinate.
     * @param y The center Y-coordinate.
     */
    void render(float x, float y) const override
    {
        Color finalVineColor = applyDeathFilter(vineColor);
        Color finalPumpkinColor = applyDeathFilter(pumpkinColor);
        
        // Early stage: Draw a small sprout/vine
        if (growthProgress < 0.2f)
        {
            float sproutLen = currentHeight * growthProgress * 2.0f;
            DrawLineEx(Vector2{x, y}, Vector2{x, y - sproutLen}, 5.0f, finalVineColor);
            return;
        }

        // Mid to late stage: Draw pumpkin fruit and detailed vines
        float pumpkinRadius = currentWidth * 0.4f * growthProgress;

        // Draw ground area
        DrawCircle(x, y + 5, currentWidth * 0.3f, {139, 69, 19, 255});

        DrawCircle(x, y - currentHeight * 0.3f, pumpkinRadius * 0.9f, finalPumpkinColor);
        DrawCircle(x - pumpkinRadius * 0.4f, y - currentHeight * 0.3f, pumpkinRadius * 0.8f, finalPumpkinColor);
        DrawCircle(x + pumpkinRadius * 0.4f, y - currentHeight * 0.3f, pumpkinRadius * 0.8f, finalPumpkinColor);

        float stemLen = currentHeight * 0.4f;
        DrawLineEx(Vector2{x, y - currentHeight * 0.3f - pumpkinRadius}, Vector2{x, y - currentHeight * 0.3f - pumpkinRadius - stemLen}, 5.0f, finalVineColor);

        if (growthProgress > 0.3f)
        {
            float vineLength = currentWidth * growthProgress;
            float vineStartX = x + pumpkinRadius * 0.5f;
            float vineStartY = y - currentHeight * 0.3f;

            // Draw winding vines (simplified)
            for (float t = 0.0f; t < 1.0f; t += 0.05f)
            {
                float angle = t * 1080.0f * PI / 180.0f;
                float vX1 = vineStartX + cosf(angle) * 20.0f;
                float vY1 = vineStartY + t * vineLength;
                
                // Draw tiny leaf/dot
                DrawCircle(vX1, vY1, 3.0f, finalVineColor); 
            }
        }
    }

    /**
     * @brief Renders the pumpkin as a small icon.
     * @param x The center X-coordinate.
     * @param y The center Y-coordinate.
     */
    void renderIcon(float x, float y) const override
    {
        float size = STATIC_ICON_SIZE * 0.3f;
        Color finalColor = applyDeathFilter(pumpkinColor);
        
        // Draw pumpkin shape
        DrawCircle(x, y, size, finalColor);
        DrawCircle(x - size * 0.5f, y, size * 0.8f, finalColor);
        DrawCircle(x + size * 0.5f, y, size * 0.8f, finalColor);
        
        // Draw stem
        DrawRectangle(x - 2, y - size - 5, 4, 10, applyDeathFilter(vineColor));
    }
};

#endif // PLANTVISUALSTRATEGY_H