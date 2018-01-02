#include "Doodler.h"
#include "EventLoop.h"
#include "icon.h"

void EventLoop::createWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close, settings);
    m_window.setFramerateLimit(MAX_FPS);

    sf::Image icon;
    if (icon.loadFromMemory(ICON_IMAGE.data, std::size(ICON_IMAGE.data)))
    {
        m_window.setIcon(ICON_IMAGE.width, ICON_IMAGE.height, icon.getPixelsPtr());
    }
}

void EventLoop::pollEvents()
{
    m_deltaTime = m_clock.restart().asSeconds();
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        const sf::Vector2i &mousePosition = sf::Mouse::getPosition(m_window);
        m_stateMediator.triggerEventHandler(event);
        m_menu.eventHandler(event, {static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)});
    }
}

void EventLoop::redrawFrame()
{
    const State state = m_stateMediator.getGameState();
    switch (state)
    {
        case State::Game:
            drawGameScreen();
            break;
        case State::MainMenu:
            drawMenuScreen();
            break;
        default:
            break;
    }

}

void EventLoop::update()
{
    const State state = m_stateMediator.getGameState();
    switch (state)
    {
        case State::Game:
            for (auto &&m_entity : m_entities)
            {
                m_entity->updatePosition(m_deltaTime);
            }
            break;
        default:
            break;
    }
}

const sf::RenderWindow &EventLoop::getWindow() const
{
    return m_window;
}

EventLoop::EventLoop(const View &view,
                     sf::RenderWindow &window,
                     StateMediator &stateMediator,
                     Menu &menu,
                     Entities &entities)
        : m_view(view),
          m_window(window),
          m_stateMediator(stateMediator),
          m_menu(menu),
          m_entities(entities)
{
    createWindow();
}

void EventLoop::drawGameScreen()
{
    m_window.clear(sf::Color::White);
    m_window.setView(m_view.getView());
    for (auto &&m_entity : m_entities)
    {
        m_window.draw(*m_entity);
    }
    m_window.display();
}

void EventLoop::drawMenuScreen()
{
    m_window.clear(sf::Color::White);
    m_window.draw(m_menu);
    m_window.display();
}
