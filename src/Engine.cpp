#include "Engine.h"

void Engine::checkCollision(Entities &entities)
{
    m_shouldSetFloor = false;

    m_p_doodler = *std::find_if(entities.begin(), entities.end(), m_isDoodler);
    std::for_each(entities.begin(), entities.end(), m_applyForEach);

    if (m_shouldSetFloor)
    {
        m_p_doodler->setFloor(m_floor);
    } else
    {
        m_p_doodler->setFloor(WINDOW_HEIGHT);
    }
}

void Engine::processCollision(const std::shared_ptr<IEntity> &p_entity)
{
    if (doesIntersect(p_entity) && m_p_doodler->getFallingState() && !m_shouldSetFloor)
    {
        m_shouldSetFloor = true;
        m_floor = p_entity->getPosition().y - p_entity->getSize().y;
    }
}

bool Engine::doesIntersect(const std::shared_ptr<IEntity> &p_entity) const
{
    sf::Rect<float> rhs(p_entity->getPosition(), p_entity->getSize());
    sf::Rect<float> lhs(m_p_doodler->getPosition(), m_p_doodler->getSize());
    return lhs.intersects(rhs);
}
