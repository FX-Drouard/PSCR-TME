#pragma once
#include "Vec3D.h"
#include "Rayon.h"
#include "Scene.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <random>
namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple


class RayJob : public Job {


	/*int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		this_thread::sleep_for(1s);
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}*/
	int arg;
	int * ret;
	Scene sc;
	const Scene::screen_t & screen;
	int cx;
	int cy;
	public :
		RayJob(Scene scene,const Scene::screen_t & screen int x, int y): sc(scene),cx(x),cy(y){};
	void run () {
		// le point de l'ecran par lequel passe ce rayon
		auto & screenPoint = screen[cy][cx];
		// le rayon a inspecter
		Rayon  ray(sc.getCameraPos(), screenPoint);
		int targetSphere = findClosestInter(sc, ray);
		if (targetSphere == -1) {
				// keep background color
				continue ;
		} else {
			const Sphere & obj = *(sc.begin() + targetSphere);
			// pixel prend la couleur de l'objet
			Color finalcolor = computeColor(obj, ray, sc.getCameraPos(), lights);
			// le point de l'image (pixel) dont on vient de calculer la couleur
			Color & pixel = pixels[y*scene.getHeight() + x];
			// mettre a jour la couleur du pixel dans l'image finale.
			pixel = finalcolor;
	}
	~RayJob(){}
};


}
