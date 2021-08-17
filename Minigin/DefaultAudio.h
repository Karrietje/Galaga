#pragma once
#include "Audio.h"

namespace dae
{
    class DefaultAudio : public Audio
    {
    public:
		DefaultAudio() = default;
		virtual ~DefaultAudio() = default;
		virtual void AddMusic(bool, int, const std::string&) override {};
		virtual void AddSoundEffect(int, const std::string&) override {};

		virtual void PlaySound(int) override {};
		virtual void StopAll() override {};
    };
}