#ifndef GAME_H
#define GAME_H

#include "polygine.h"

typedef enum class GameState : uint {
    RUNNING = 0,
	TITLE = 1,    
	PAUSED = 2,
	GAME_OVER = 3
} GS;


class Game {
public:
	Game(cc *name, int w, int h, unsigned int f);
	~Game();
	
	void run();
	
    // Delete copy constructor and copy assignment operator
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Default move constructor and move assignment operator
    Game(Game&&) noexcept = default;
    Game& operator=(Game&&) noexcept = default;
	
private:
	std::uniform_real_distribution<float> _uni_dist;
	
	std::shared_ptr<POLYGINE::Timer> _timer;
	std::shared_ptr<POLYGINE::Window> _window;
	std::shared_ptr<POLYGINE::Input> _inputter;
	
	std::unique_ptr<POLYGINE::Camera> _camera;
	
	std::vector<std::shared_ptr<POLYGINE::Shader>> _shaderVec;
	std::vector<std::shared_ptr<POLYGINE::Thing>> _thingVec;
	std::vector<std::shared_ptr<POLYGINE::Lighting>> _lightVec;
	
	glm::vec3 _bgc;

	GS _state;

	void _initGame();
	void _looper();
	void _input();
	void _foreverInput();
	void _runningInput();
	void _update();
	void _draw();
	
};

#endif
