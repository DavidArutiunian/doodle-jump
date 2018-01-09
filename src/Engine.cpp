#include "Engine.h"
#include "Platform.h"

Engine::Engine(const std::shared_ptr<IEntity> &p_doodler) : m_p_doodler(p_doodler)
{}

void Engine::checkCollision(Entities &entities)
{
    bool isInCollision = false;

    std::find_if(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_entity) -> bool {
        if (isDoodler()(p_entity))
        {
            return false;
        }
        isInCollision = processCollision(p_entity);
        return isInCollision;
    });


    if (!isInCollision)
    {
        m_p_doodler->setFloor(-1.f);
        return;
    }

    m_p_doodler->setFloor(m_floor);
}

bool Engine::processCollision(const std::shared_ptr<IEntity> &p_entity)
{
    if (intersect(p_entity) && m_p_doodler->getFallingState())
    {
        m_floor = p_entity->getPosition().y + (p_entity->getSize() / 4.f).y;
        return true;
    }
    return false;
}

bool Engine::intersect(const std::shared_ptr<IEntity> &p_entity) const
{
    sf::FloatRect rhs(p_entity->getPosition(), p_entity->getSize());
    sf::FloatRect lhs(m_p_doodler->getPosition(), m_p_doodler->getSize());
    if (rhs.height - lhs.height > 0)
    {
        return false;
    }
    return lhs.intersects(rhs) && rhs.height - lhs.height <= 0;
}

void Engine::addPlatforms(Entities &entities)
{
    long long int index = std::find_if(entities.begin(), entities.end(), isDoodler()) - entities.begin();
    if (std::size(entities) >= PLATFORM_COUNT * 2 + 1)
    {
        return;
    }
    if (!m_p_doodler->getFallingState())
    {
        Platform::increment();
    }
    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        entities.push_back(std::make_shared<Platform>(Platform()));
    }
    std::swap(entities.at(static_cast<unsigned long long>(index)), entities.back());
}

void Engine::removePlatforms(Entities &entities)
{
    size_t index = 0;
    entities.erase(
            std::remove_if(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_entity) -> bool {
                const bool isNotPlatform = p_entity->getType() != EntityType::Platform;
                const bool isNotFirstPart = index > PLATFORM_COUNT;
                if (isNotPlatform || m_p_doodler == nullptr || isNotFirstPart)
                {
                    return false;
                }
                const float doodlerY = m_p_doodler->getPosition().y;
                const float platformY = p_entity->getPosition().y;
                const float distance = std::abs(doodlerY - platformY);
                const bool isUnderDoodler = doodlerY < platformY;
                ++index;
                return distance > WINDOW_HEIGHT / 2 && isUnderDoodler;
            }),
            entities.end()
    );
}

const std::function<bool(const std::shared_ptr<IEntity> &)> Engine::isDoodler()
{
    return [](const std::shared_ptr<IEntity> &p_entity) -> bool {
        return p_entity != nullptr && p_entity->getType() == EntityType::Doodler;
    };
}

void Engine::reset()
{
    m_floor = static_cast<float>(WINDOW_HEIGHT);
}
