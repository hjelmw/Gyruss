#pragma once

bool change_direction = false;

class Game : public GameObject
{
private:
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* engine;

	Player* player;
	Sprite* life_sprite;
	AliensGrid* aliens_grid;

	ObjectPool<Rocket> rockets_pool;	// used to instantiate rockets
	ObjectPool<Alien> aliens_pool;		// pool of aliens

	ObjectPool<AlienBomb> bombs_pool;

	bool game_over = false;
	bool canSpawn = true;

	unsigned int score = 0;
public:

	virtual void Create(AvancezLib* engine)
	{
		SDL_Log("Game::Create");

		this->engine = engine;

		// Player
		player = new Player();
		PlayerBehaviourComponent* player_behaviour = new PlayerBehaviourComponent();
		player_behaviour->Create(engine, player, &game_objects, &rockets_pool);
		RenderComponent* player_render = new RenderComponent();
		player_render->Create(engine, player, &game_objects, "data/player.bmp");
		CollideComponent* player_bomb_collision = new CollideComponent();
		player_bomb_collision->Create(engine, player, &game_objects, reinterpret_cast<ObjectPool<GameObject>*>(&bombs_pool));
		CollideComponent* player_alien_collision = new CollideComponent();
		player_alien_collision->Create(engine, player, &game_objects, reinterpret_cast<ObjectPool<GameObject>*>(&aliens_pool));

		player->Create();
		player->AddComponent(player_behaviour);
		player->AddComponent(player_render);
		player->AddComponent(player_bomb_collision);
		player->AddComponent(player_alien_collision);
		player->AddReceiver(this);
		game_objects.insert(player);

		// Player rocket pool
		rockets_pool.Create(30);
		for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++)
		{
			RocketBehaviourComponent* behaviour = new RocketBehaviourComponent();
			behaviour->Create(engine, *rocket, &game_objects);
			RenderComponent* render = new RenderComponent();
			render->Create(engine, *rocket, &game_objects, "data/rocket.bmp");

			(*rocket)->Create();
			(*rocket)->AddComponent(behaviour);
			(*rocket)->AddComponent(render);
		}

		aliens_pool.Create(11);
		for (auto alien = aliens_pool.pool.begin(); alien != aliens_pool.pool.end(); alien++)
		{
			AlienBehaviorComponent* alien_behavior = new AlienBehaviorComponent();
			alien_behavior->Create(engine, *alien, &game_objects, &bombs_pool);
			RenderComponent* alien_render = new RenderComponent();
			alien_render->Create(engine, *alien, &game_objects, "data/enemy_0.bmp");

			// Alien player collision
			CollideComponent* alien_player_collision = new CollideComponent();
			alien_player_collision->Create(engine, player, &game_objects, (ObjectPool<GameObject>*) & aliens_pool);

			// Alien rocket collision
			CollideComponent* alien_rocket_collision = new CollideComponent();
			alien_rocket_collision->Create(engine, *alien, &game_objects, (ObjectPool<GameObject>*) & rockets_pool);

			(*alien)->AddComponent(alien_behavior);
			(*alien)->AddComponent(alien_render);
			(*alien)->AddComponent(alien_player_collision);
			(*alien)->AddComponent(alien_rocket_collision);
			(*alien)->AddReceiver(this);
		}

		bombs_pool.Create(50);
		for (auto bomb = bombs_pool.pool.begin(); bomb != bombs_pool.pool.end(); bomb++)
		{
			AlienBombBehaviorComponent* bomb_behaviour = new AlienBombBehaviorComponent();
			bomb_behaviour->Create(engine, *bomb, &game_objects);
			RenderComponent* bomb_render = new RenderComponent();
			bomb_render->Create(engine, *bomb, &game_objects, "data/bomb.bmp");

			(*bomb)->Create();
			(*bomb)->AddComponent(bomb_behaviour);
			(*bomb)->AddComponent(bomb_render);
		}

		aliens_grid = new AliensGrid();
		AliensGridBehaviourComponent* aliensgrid_behaviour = new AliensGridBehaviourComponent();
		aliensgrid_behaviour->Create(engine, aliens_grid, &game_objects, &aliens_pool, &bombs_pool, player);
		aliens_grid->Create();
		aliens_grid->AddComponent(aliensgrid_behaviour);
		
		// Aliens shoud spawn immediately
		game_objects.insert(aliens_grid);
	}

	virtual void Init()
	{
		player->Init();
		aliens_grid->Init(); // Spawn aliens in grid
		enabled = true;
	}

	virtual void Update(float dt)
	{
		AvancezLib::KeyStatus keys;
		engine->getKeyStatus(keys);
		if (keys.esc) {
			Destroy();
			engine->quit();
		}

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Update(dt);

		// Transfer text and sprites to framebuffer
		Draw();
	}

	// Draw UI and text elements here
	virtual void Draw()
	{
		engine->drawText(GAME_CENTER_X - 20, 10, "Gyruss");
	}

	virtual void Receive(Message m)
	{
		if (m == GAME_OVER)
		{
			engine->drawText(200, 400, "--- Game Over ---");
			game_over = true;
		}

		if (m == ALIEN_HIT)
		{
			canSpawn = true;
			score += 100;
		}

	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();

		life_sprite->destroy();

		game_objects.clear();
		delete player;
	}


};