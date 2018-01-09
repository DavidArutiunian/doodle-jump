#ifndef DOODLE_JUMP_DOODLER_H
#define DOODLE_JUMP_DOODLER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Assets.h"
#include "Sprite.h"
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "consts.h"
#include "KeyboardState.h"
#include "StateMediator.h"

class Doodler : public IEntity
{
public:
    explicit Doodler(StateMediator &stateMediator);

    void updatePosition(float deltaTime) override;

    EntityType getType() const override;

    const sf::Vector2f &getSize() const override;

    bool getFallingState() const override;

    void setFloor(float nextFloor) override;

    void eventHandler(const sf::Event &event) override;

private:
    const float m_initialSpeed = DOODLER_SPEED;
    float m_timeAccumulator = 0.f;
    float m_floor = static_cast<float>(WINDOW_HEIGHT);
    bool m_isFalling = false;
    StateMediator &m_stateMediator;
    sf::Vector2f m_size = DOODLER_SPRITE_SIZE;
    sf::Vector2f m_position = sf::Vector2f(WINDOW_WIDTH / 2, m_floor - m_size.x / 2);
    sf::RectangleShape m_shape = sf::RectangleShape();
    Sprite m_spite = Sprite(SpriteOptions{Assets::DOODLER.length,
                                          Assets::DOODLER.data,
                                          DOODLER_SPRITE_SIZE,
                                          false, true});

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setHorizontalPosition(float nextX, float deltaTime);

    const std::function<bool(float, float)> areCloseAbsolute();

    const std::function<bool(float, float)> areFuzzyEqual();

    const std::function<bool(float, float)> areCloseRelative();

    void setFallingState(float nextY);

    void checkCollision() override;

    sf::FloatRect getBounds() const override;

    float getNextY() const;

    void setNextY(float nextY);
};

#endif //DOODLE_JUMP_DOODLER_H
