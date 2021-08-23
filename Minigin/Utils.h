#pragma once
enum class ComponentType
{
	TextComponent, TextureComponent, FPSComponent, SubjectComponent, HealthComponent, PointComponent, SpriteSheetComponent, GalagaManagerComponent, SpaceShipComponent, TriggerComponent, MissileComponent, EnemyComponent, AIComponent, BeginScreenComponent, EndScreenComponent
};

enum class Event
{
	Kill, ZakoKill, ZakoDivingKill, GoeiKill, GoeiDivingKill, BossKill, BossDivingKill, Shot, Hit
};

enum class MovementDirection
{
	Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft
};

enum class Tag
{
	Spaceship, Missile, EnemyMissile, Enemy, TractorBeam, Back, Front, TractorBeamFront
};

enum class EnemyType
{
	Zako, Goei, Boss
};