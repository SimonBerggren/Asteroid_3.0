#include "GameSession.h"

GameSession::GameSession()
{
	Init();
}

GameSession::~GameSession()
{
	Clear();
}

void GameSession::Update(float delta)
{
	if (m_PreGameTimer.getElapsedTime().asSeconds() <= PRE_GAME_TIME)			// wait if game hasn't started
		return;

	if (m_SpawnTimer.getElapsedTime().asSeconds() >= m_SpawnTime)			// spawn new asteroid if reached spawn limit
	{
		m_SpawnTime = utils::Clamp(m_SpawnTime - SPAWN_TICK, MIN_SPAWN_TIME, MAX_SPAWN_TIME);
		SpawnAsteroid();
		m_SpawnTimer.restart();
	}

	for (int i = 0; i < m_Projectiles.size(); ++i)
	{
		m_Projectiles[i]->Update(delta);						// update projectiles
		if (m_Projectiles[i]->IsDead())						// if projectile's lifetime is up, remove it
		{
			delete m_Projectiles[i];
			m_Projectiles.erase(m_Projectiles.begin() + i);
		}
	}

	for (int i = 0; i < m_Asteroids.size(); ++i)			// update asteroids
		m_Asteroids[i]->Update(delta);

#if FSM
	m_FsmController->Update();									// update controller
#elif FuSM
	m_FusmController->Update();									// update controller
#elif DT
	m_DTController->Update();
#endif

	m_Ship->Update(delta);										// update ship
	CheckCollisions();												// check for collision after updating objects' positions

#if HUMAN_CONTROL
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_Ship->Steer(-1.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_Ship->Steer(1.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_Ship->Thrust(1.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_Ship->Thrust(-1.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_Ship->Shoot();
#endif
}

void GameSession::SpawnAsteroid()
{
	// random side which asteroid is going to spawn on
	int rndPos = utils::rnd::Int(0, 3);

	// random position along sides
	float xPos = utils::rnd::Float(0.0f, WINDOW_WIDTH);
	float yPos = utils::rnd::Float(0.0f, WINDOW_HEIGHT);

	// save offset for convencience
	float xOffset = textures::Asteroid()->getSize().x / 2.0f;
	float yOffset = textures::Asteroid()->getSize().y / 2.0f;

	if (rndPos == 1)										// top side
		yPos = -yOffset;
	else if (rndPos == 2)								// right side
		xPos = WINDOW_WIDTH + xOffset;
	else if (rndPos == 3)								// bottom side
		yPos = WINDOW_HEIGHT + yOffset;
	else														// left side
		xPos = -xOffset;

	m_Asteroids.push_back(new Asteroid(sf::Vector2f(xPos, yPos)));
}

void GameSession::CheckCollisions()
{
	for (int a = 0; a < m_Asteroids.size(); ++a)
	{
		if (m_Ship->GetRect().intersects(m_Asteroids[a]->GetRect()))			// handle ship vs asteroid collision
		{
			Clear();
			Init();
		}

		for (int p = 0; p < m_Projectiles.size(); ++p)
		{
			if (m_Asteroids[a]->GetRect().intersects(m_Projectiles[p]->GetRect()))		// handle projectile vs asteroid collision
			{
				delete m_Asteroids[a];
				m_Asteroids.erase(m_Asteroids.begin() + a);

				delete m_Projectiles[p];
				m_Projectiles.erase(m_Projectiles.begin() + p);
				break;
			}
		}
	}

	// check if we removed a current target
#if FSM
	m_FsmController->FindClosestAsteroid();
#elif FuSM
	m_FusmController->FindClosestAsteroid();
#elif DT
	m_DTController->FindClosestAsteroid();
#endif
}

void GameSession::Init()
{
	m_Ship = new Ship(m_Projectiles);
#if FSM
	m_FsmController = new fsm::FSMController(m_Ship, m_Asteroids);
#elif FuSM
	m_FusmController = new fusm::FuSMController(m_Ship, m_Asteroids);
	m_FusmController->GetFuSM()->AddState(new fusm::state::Idle(m_FusmController, 0.0f));
	m_FusmController->GetFuSM()->AddState(new fusm::state::Approach(m_FusmController, 0.6f));
	m_FusmController->GetFuSM()->AddState(new fusm::state::Evade(m_FusmController, 0.2f));
	m_FusmController->GetFuSM()->AddState(new fusm::state::Attack(m_FusmController, 0.0f));
#elif DT
	m_DTController = new DTController(m_Ship, m_Asteroids);
#endif
	m_SpawnTime = MAX_SPAWN_TIME;
	m_SpawnTimer.restart();
	m_PreGameTimer.restart();
}

void GameSession::Clear()
{
#if FSM
	delete m_FsmController;
#elif FuSM
	delete m_FusmController;
#elif DT
	delete m_DTController;
#endif
	delete m_Ship;

	for (int i = 0; i < m_Projectiles.size(); ++i)	// delete projectiles before clearing = happy heap
		delete m_Projectiles[i];
	m_Projectiles.clear();

	for (int i = 0; i < m_Asteroids.size(); ++i)	// delete projectiles before clearing = happy heap
		delete m_Asteroids[i];
	m_Asteroids.clear();
}

void GameSession::Draw()
{
	for (int i = 0; i < m_Asteroids.size(); ++i)		// draw asteroids to window
		m_Asteroids[i]->Draw();

	for (int i = 0; i < m_Projectiles.size(); ++i)		// draw projectiles to window
		m_Projectiles[i]->Draw();

	m_Ship->Draw();											// draw ship to window

#if DEBUG
#if FSM
	if (m_FsmController->GetClosestAsteroid())
		m_FsmController->GetClosestAsteroid()->Display();
#elif FuSM
	if (m_FusmController->GetClosestAsteroid())
		m_FusmController->GetClosestAsteroid()->Display();
#elif DT
	if (m_DTController->GetClosestAsteroid())
		m_DTController->GetClosestAsteroid()->Display();
#endif
#endif

	if (m_PreGameTimer.getElapsedTime().asSeconds() <= PRE_GAME_TIME)			// if game hasn't started, display timer
	{
		sf::Text timer(utils::ToString(utils::Round(PRE_GAME_TIME - m_PreGameTimer.getElapsedTime().asSeconds(), 1)), *fonts::Standard());
		timer.setOrigin(timer.getLocalBounds().width / 2.0f, timer.getLocalBounds().height / 2.0f);
		timer.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT * 0.25f);
		timer.setColor(sf::Color::Cyan);
		window->draw(timer);
	}
}