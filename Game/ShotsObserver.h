#pragma once
#include <Observer.h>

namespace dae
{
    class ShotsObserver final : public Observer
    {
    public:
        ShotsObserver() = default;

        virtual void Notify(Event event) override;

        static int GetShotsFired();
        static int GetShotsHit();
    private:
        static int m_ShotsFired;
        static int m_ShotsHit;
    };
}