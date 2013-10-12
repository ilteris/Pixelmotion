/*
 *  ParticleSystem.cpp
 *  getEdgeVideo4
 *
 *  Created by ilteris kaplan on 11/14/06.
 *  Copyright 2006 ilteris kaplan. All rights reserved.
 *
 */

#include "ParticleSystem.h"
#include <list>
#include <iostream>

ParticleSystem::ParticleSystem(long x_, long y_, int num_) {
	//num = num_;
	
	// particles.reserve(num);
	
	/*
	for (std::list<MyLine>::size_type i = 0; i != particles.size(); ++i) {
//		particles.push_front(MyLine::Myline());
		//	particles.push_back(MyLine::MyLine();
	}
	 */
}
/*
void ParticleSystem::run() {
	for (std::list<MyLine>::size_type i = particles.size()-1; i >= 0; i--) {
		particles[i].run();
		if(particles[i].dead()) {
			particles.pop_last;
		}
		
	}	


						 
}
*/
/*
 ParticleSystem(int num, Vector3D v) {
	 particles = new ArrayList();              // Initialize the arraylist
	 origin = v.copy();                        // Store the origin point
	 for (int i = 0; i < num; i++) {
		 particles.add(new Particle(origin));    // Add "num" amount of particles to the arraylist
	 }
 }
 
 void run() {
	 // Cycle through the ArrayList backwards b/c we are deleting
	 for (int i = particles.size()-1; i >= 0; i--) {
		 Particle p = (Particle) particles.get(i);
		 p.run();
		 if (p.dead()) {
			 particles.remove(i);
		 }
	 }
 }
 
 void addParticle() {
	 particles.add(new Particle(origin));
 }
 
 void addParticle(Particle p) {
	 particles.add(p);
 }
 
 // A method to test if the particle system still has particles
 boolean dead() {
	 if (particles.isEmpty()) {
		 return true;
	 } else {
		 return false;
	 }
 }
 
 
 */