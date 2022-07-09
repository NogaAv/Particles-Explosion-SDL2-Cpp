#pragma once
#include "Particle.h"

namespace CaveOfProgramming {
	class Swarm
	{
	public:
		 static const int NPARTICLES = 5000;

	private:
		Particle* m_pParticales;
		int m_lasTime;
	public:
		Swarm();
		virtual ~Swarm();

		const Particle* const getParticles() { return this->m_pParticales; }
		void update(int elapsed);

	};

}

