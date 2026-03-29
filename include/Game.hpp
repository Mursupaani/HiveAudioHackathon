#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cstddef>
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "EntityManager.hpp"
#include "LiveAudio.hpp"
#include "Vec2.hpp"

struct PlayerConfig {
		int	  SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
		float S;
};
struct EnemyConfig {
		int	  SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI;
		float SMIN, SMAX;
};
struct BulletConfig {
		int	  SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
		float S;
};

class Game {
	private:
		sf::RenderWindow m_window;
		unsigned int	 m_framerateLimit = 60;
		sf::State		 m_windowState = sf::State::Windowed;
		EntityManager	 m_entities;
		sf::Font		 m_font;
		sf::Text		*m_text = nullptr;
		PlayerConfig	 m_playerConfig;
		EnemyConfig		 m_enemyConfig;
		BulletConfig	 m_BulletConfig;
		int				 m_score = 0;
		size_t			 m_currentFrame = 0;
		size_t			 m_lastEnemySpawnTime = 0;
		bool			 m_paused = false;
		bool			 m_running = true;
		LiveAudio		 m_liveAudio;
		unsigned int	 m_currentAudioSourceIndex = 0;
		std::string		 m_currentAudioSourceName;

		unsigned int	m_movementSpeed = 1;
		float			m_bounciness = 0.8;
		Vec2			m_gravity{0, 2};
		sf::VertexArray m_plot = sf::VertexArray(sf::PrimitiveType::LineStrip, SAMPLES / 16);

		std::shared_ptr<Entity> m_player;

		void init(const std::string &path);
		void setPaused(const bool paused);

		// NOTE: Systems:
		void sMovement(void);
		void sUserInput(void);
		void sLifeSpan(void);
		void sRender(void);
		void sEnemySpawner(void);
		void sFrequencySpawner(void);
		void sCollision(void);

		void spawnPlayer(void);
		void spawnEnemy(void);
		void spawnFrequency(const Vec2 pos);
		void spawnSmallEnemies(std::shared_ptr<Entity> &entity);
		void spawnBullet(std::shared_ptr<Entity> &entity, const Vec2 &mousePos);
		void spawnSpecialWeapon(std::shared_ptr<Entity> &entity);

		bool entitiesCollide(const EntityPtr &a, const EntityPtr &b);
		bool entityAndVertexCollide(const EntityPtr &a, const Vec2 &v);

		void chooseAudioSource(void);
		void gameLoop(void);

		void reset(void);

		// const std::string m_homeDir = std::getenv("HOME");
		unsigned int m_fontSize = 12;
		sf::Vector2u windowSize{1920, 1080};

		void bounceObjectFromWalls(EntityPtr e);
		void reflectObjectVelocity(EntityPtr e, Vec2 surfaceNormal);
		void parseConfig(const std::string &config);

		float dot(Vec2 v1, Vec2 v2);

	public:
		Game(const std::string &config);
		~Game(void);

		void run(void);
};
