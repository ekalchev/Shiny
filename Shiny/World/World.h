///////////////////////////////////////////////////////////////////////////////
//	File:    World.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "ShadeRec.h"
#include "RGBColor.h"
#include <KdTree.h>
#include <GeoObject.h>
#include <GeoObjectAdapter.h>

using namespace std;


class ViewPane;
class Camera;
class Tracer;
class Ray;
class AmbientLight;
class Light;
class Mesh;
class Material;


class World
{
private:
	vector<GeoObject*>	objects;
	vector<Material*> materials;
	Camera *pCurrentCamera;
	KdTree<GeoObject,GeoObjectAdapter,ShadeRec>* kdtree;
public:
	Tracer *pTracer;
	AmbientLight *pAmbientLight;
	vector<Light*>	lights;
public:
	World();
	~World();
	void build();
	void render(ViewPane& viewPane);
	void setCamera(Camera& camera);
	const vector<GeoObject*>& GetWorldObjects() const;
	ShadeRec HitObjects(const Ray& ray);
	void AddLight(Light* light);
	void DeleteLights();
	void DeleteObjects();
	void DeleteMaterials();
	void AddObject(Mesh* meshObject);
#ifdef _DEBUG
	ShadeRec HitObjectsNoKdTree(const Ray& ray);
#endif
};

#endif