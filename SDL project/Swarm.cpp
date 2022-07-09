#include "Swarm.h"
namespace CaveOfProgramming {

	Swarm::Swarm():m_lasTime(0){

		m_pParticales = new Particle[NPARTICLES];
	}


	Swarm::~Swarm() {
		delete[] m_pParticales;
	}

	void Swarm::update(int elapsed) {

		int interval = elapsed - m_lasTime;

		for (int i = 0; i < Swarm::NPARTICLES; ++i) {
			m_pParticales[i].update(interval);
		}

		m_lasTime = elapsed;
	}
}