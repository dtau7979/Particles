#include "Engine.h"

Engine::Engine()
{
	// Get screen resolution and display to user
	VideoMode desktop = VideoMode::getDesktopMode();
	m_Window.create(VideoMode(desktop.width, desktop.height), "Particles");
}

void Engine::run()
{
	sf::Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		input();
		update(dt);
		draw();
	}
}

void Engine::input()
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Window.close();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			m_Window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			// Create n particles at mouse position
			for (int i = 0; i < 5; i++)
			{
				int numPoints = 25 + rand() % 26; // Ranges [25:50]
				sf::Vector2i pos = sf::Mouse::getPosition(m_Window);
				m_particles.push_back(Particle(m_Window, numPoints, { pos.x, pos.y }));
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (m_particles[i].getTTL() > 0.0)
		{
			m_particles[i].update(dtAsSeconds);
		}
		else
		{
			m_particles.erase(m_particles.begin() + i);
			--i;
		}
	}
}

void Engine::draw()
{
	m_Window.clear();

	for (int i = 0; i < m_particles.size(); ++i)
	{
		m_Window.draw(m_particles[i]);
	}

	m_Window.display();
}
