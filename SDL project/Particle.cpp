#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Particle.h"
# define M_PI           3.14159265358979323846  /* pi */
using namespace std;
namespace CaveOfProgramming {


	Particle::Particle(){

		init();
	}

	void Particle::init() {
		m_x = 0;
		m_y = 0;
		m_direction = (2 * M_PI * rand()) / RAND_MAX;
		m_speed = 0.04 * rand() / RAND_MAX;

		m_speed *= m_speed; //this makes sure the explosion is not a round bulcky sphere

	}

	Particle::~Particle(){}

	void Particle::update(int interval) {
		/* multiplying speed with interval insures the speed of particles movement is propotional to the speed of the running computer, 
		   so that the explotion rate is similare on any computer, without dependency in the speed of the computer. 
		   slower the computer-> slower the main while loop that runs the programme, so this interval is common way of adjusting rate:
		   the slower the comp, the higher the interval, and the higher speed of particle movement.
		*/

		m_direction += interval * 0.0003; //direction curles
		m_x += m_speed * interval * cos(m_direction);
		m_y += m_speed * interval * sin(m_direction);
			
		if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
			init(); //particle that go off the edge of the screen reappear in the middle again
		}

		if (rand() < RAND_MAX / 100) { //1 in every 100
			init();
		}
	}
}

