#include "Doodler.h"

void Doodler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

Doodler::Doodler(KeyboardState &m_keyboardState) : m_keyboardState(m_keyboardState)
{
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size.x / 2, m_size.x / 2);
    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(m_outlineThickness);
}

void Doodler::updatePosition(const float deltaTime)
{
    checkCollision();
    setVerticalPosition(MOVE_SPEED, deltaTime);
    m_timeAccumulator += deltaTime * TIME_ACCELERATOR;
    double nextY = m_position.y - m_initialSpeed * m_timeAccumulator + 0.5 * G * std::pow(m_timeAccumulator, 2);
    const sf::Vector2f nextPosition = {m_position.x, static_cast<float>(nextY)};
    m_shape.setPosition(nextPosition);
    setFalling(static_cast<float>(nextY));
    setPosition(nextPosition);
}

void Doodler::checkCollision()
{
    const float currentBottomPosition = m_shape.getPosition().y + m_size.x / 2 + m_outlineThickness;
    const bool isAtZeroLevel = currentBottomPosition >= m_floor;
    if (isAtZeroLevel && m_isFalling)
    {
        m_timeAccumulator = 0;
    }
}

// TODO: fix side collision check
void Doodler::setVerticalPosition(const float nextX, const float deltaTime)
{
    const KeysMap &keysMap = m_keyboardState.getKeysMap();
    if (keysMap.at(sf::Keyboard::Right) && m_position.x + m_size.x / 2 + m_outlineThickness < WINDOW_WIDTH)
    {
        m_position.x += nextX * deltaTime;
    } else if (keysMap.at(sf::Keyboard::Left) && m_position.x - m_size.x / 2 - m_outlineThickness > 0)
    {
        m_position.x -= nextX * deltaTime;
    }
}

Types Doodler::getType() const
{
    return Types::Doodler;
}

const sf::Vector2f &Doodler::getBounds() const
{
    return m_size;
}

void Doodler::setFloor(const float nextFloor)
{
    if (!m_isFalling)
    {
        return;
    }
    m_floor = nextFloor;
    m_position.y = m_floor - m_size.x / 2 - m_outlineThickness;
}

void Doodler::setFalling(const float nextY)
{
    m_isFalling = getPosition().y - nextY <= 0;
}
