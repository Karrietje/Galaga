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