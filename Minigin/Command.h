#pragma once
#include <iostream>

#include "Audio.h"
#include "SubjectComponent.h"
#include "AudioLocator.h"

using namespace dae;
class Command
{
public:
	virtual ~Command() = default; 
	virtual void Execute() = 0; 
};

class JumpCommand final : public Command 
{	
public:
	virtual void Execute() override { std::cout << "You jumped!\n"; }
};

class SmileCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You smiled!\n"; }
};

class FireCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You fired!\n"; }
};

class RunCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You ran!\n"; }
};

class LeftHandpCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You attacked with your left hand!\n"; }
};

class RightHandCommand final : public Command
{
public:
	virtual void Execute() override { std::cout << "You attacked with your right hand!\n"; }
};

class KillCommand final : public Command
{
public:
	KillCommand(SubjectComponent* pSubject)
		:m_pSubject{pSubject}
	{}

	virtual void Execute() override 
	{
		if (m_pSubject)
		{
			m_pSubject->Notify(Event::Kill);
			AudioLocator::GetAudioSystem()->PlaySound(0);
		} 
	}

private:
	SubjectComponent* m_pSubject;
};

class ColorChangeCommand final : public Command
{
public:
	ColorChangeCommand(SubjectComponent* pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (m_pSubject)
		{
			m_pSubject->Notify(Event::ColorChange);
		}
	}

private:
	SubjectComponent* m_pSubject;
};

class KillByFlyingDiscCommand final : public Command
{
public:
	KillByFlyingDiscCommand(SubjectComponent* pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (m_pSubject)
		{
			m_pSubject->Notify(Event::KillByFlyingDisc);
		}
	}

private:
	SubjectComponent* m_pSubject;
};

class RemainingDiscCommand final : public Command
{
public:
	RemainingDiscCommand(SubjectComponent* pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (m_pSubject)
		{
			m_pSubject->Notify(Event::RemainingDisc);
		}
	}

private:
	SubjectComponent* m_pSubject;
};

class CatchingCommand final : public Command
{
public:

	CatchingCommand(SubjectComponent* pSubject)
		:m_pSubject{ pSubject }
	{}

	virtual void Execute() override
	{
		if (m_pSubject)
		{
			m_pSubject->Notify(Event::CatchingSlickSam);
		}
	}

private:
	SubjectComponent* m_pSubject;
};

