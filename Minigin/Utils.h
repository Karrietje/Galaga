#pragma once
enum class ComponentType
{
	TextComponent, TextureComponent, FPSComponent, SubjectComponent, HealthComponent, PointComponent, SpriteSheetComponent, GalagaComponent, SpaceShipComponent, TriggerComponent, MissileComponent, ZakoComponent, AIComponent
};

enum class Event
{
	Kill, ColorChange, KillByFlyingDisc, RemainingDisc, CatchingSlickSam
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