#include "Player.h"
#include "Store.h"

Player::Player()
    : position{750.0f, 450.0f},
      radius(30.0f),
      color(MAROON)
{
}

void Player::update(Store& store)
{
    Vector2 oldPos = position;

    // Movement input
    if (IsKeyDown(KEY_RIGHT))
        position.x += 2.0f;
    if (IsKeyDown(KEY_LEFT))
        position.x -= 2.0f;
    if (IsKeyDown(KEY_UP))
        position.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))
        position.y += 2.0f;

    // Clamp to screen bounds
    position.x = Clamp(position.x, 30, 770);
    position.y = Clamp(position.y, 30, 470);

    // Collision detection with store objects
    if (CheckCollisionCircleRec(position, radius, store.boundaryWall) ||
        CheckCollisionCircleRec(position, radius, store.sDoor) ||
        CheckCollisionCircleRec(position, radius, store.counterHitBox) ||
        CheckCollisionCircleRec(position, radius, store.plotHitBox))
    {
        position = oldPos;
    }
}

void Player::render()
{
    DrawCircleV(position, radius, color);
}