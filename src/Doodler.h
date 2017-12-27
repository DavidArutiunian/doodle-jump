#ifndef DOODLE_JUMP_DOODLER_H
#define DOODLE_JUMP_DOODLER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "consts.h"
#include "KeyboardState.h"
#include "StateMediator.h"

class Doodler : public IEntity
{
public:
    explicit Doodler(const StateMediator &stateMediator);

    void updatePosition(float deltaTime) override;

    EntityType getType() const override;

    const sf::Vector2f &getSize() const override;

    bool getFallingState() const override;

    void setFallingState(float nextY);

    void setFloor(float nextFloor) override;

private:
    const StateMediator &m_stateMediator;

    const float m_outlineThickness = 2.f;
    const float m_initialSpeed = 75.f;

    float m_timeAccumulator{0.f};
    float m_floor{static_cast<float>(WINDOW_HEIGHT)};
    bool m_isFalling{false};
    sf::Vector2f m_size{sf::Vector2f(35.f, 50.f)};
    sf::Vector2f m_position{sf::Vector2f(WINDOW_WIDTH / 2, m_floor - m_size.x / 2 - m_outlineThickness)};
    sf::RectangleShape m_shape{sf::RectangleShape()};

    const std::function<bool(float, float)> m_areCloseAbsolute{[&](float lhs, float rhs) -> bool {
        constexpr float tolerance = 0.001f;
        return std::abs(lhs - rhs) < tolerance;
    }};

    const std::function<bool(float, float)> m_areCloseRelative{[&](float lhs, float rhs) -> bool {
        constexpr float tolerance = 0.001f;
        return std::abs((lhs - rhs) / rhs) < tolerance;
    }};

    const std::function<bool(float, float)> m_areFuzzyEqual{[&](float lhs, float rhs) -> bool {
        if (std::abs(rhs) > 1.f)
        {
            return m_areCloseRelative(lhs, rhs);
        }
        return m_areCloseAbsolute(lhs, rhs);
    }};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void checkCollision() override;

    void setVerticalPosition(float nextX, float deltaTime);

    void setNextY();

    sf::FloatRect getBounds() const override;

    float getNextY() const;
};

#endif //DOODLE_JUMP_DOODLER_H
