//Adarsh Kumar, Aayush Sarcar

#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Animation.h"

enum class Entity_Type
{
	Wall, Mushroom, Ground, Coin
};

class Level;

struct Entity
{
	Vector2 position{};
	Vector2 size{};
	Vector2 velocity{};
	Entity_Type type{};
	Color color = WHITE;

	bool dead = false;

	virtual void add_entity(Level* level) = 0;
	virtual void update(Level* level) = 0;
	virtual void render() = 0;

	virtual ~Entity() = default;
};

struct Enemy : public Entity
{
	Enemy(const Vector2 pos);
	 
	 void add_entity(Level* level) override;
	 void render() override;

	 void update(Level* level) override;
};

struct Wall : public Entity
{
	Wall(const Vector2 pos);
	void add_entity(Level* level) override;
	void render() override ;
	void update(Level* level) override;
};

struct Ground : public Entity
{
	Ground(const Vector2 pos);
	void add_entity(Level* level) override;
	void update(Level* level) override;
	void render() override;
};

struct Coin : public Entity
{
	Coin(const Vector2 coin_pos);

	void add_entity(Level* level) override;
	void update(Level* level) override;
	void render() override;
};

struct VictoryFlag // This is victory point object in the game.
{
	VictoryFlag();

	Vector2 pos;
	Vector2 size;
	Color color;
};


struct Parallax
{
	float BGScrollSpeed = 0.0f;
	float FGScrollSpeed = 0.0f;

	void ParallaxHandling();
};