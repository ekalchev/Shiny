///////////////////////////////////////////////////////////////////////////////
//	File:    World.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "World.h"
#include "ShinyMath.h"
#include "Ray.h"
#include "Sphere.h"
#include "ViewPane.h"
#include "PinholeCamera.h"
#include "RayCast.h"
#include "AmbientLight.h"
#include "Matte.h"
#include "Phong.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Plane.h"
#include "Reflective.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Vertex.h"
#include <kdtree.h>

#include <math.h>

float z = 100;
float x = 100;
float angle = 0;


World::World() : pAmbientLight(NULL)
{
	pCurrentCamera = NULL;
	kdtree = NULL;
}

World::~World()
{
	if(pCurrentCamera != NULL)
	{
		delete pCurrentCamera;
	}

	if(kdtree != NULL)
	{
		delete kdtree;
	}

	DeleteObjects();
	DeleteLights();
	DeleteMaterials();
}

void World::setCamera(Camera& camera)
{
	if(pCurrentCamera != NULL)
	{
		delete pCurrentCamera;
	}

	pCurrentCamera = &camera;
}

void World::build()
{ 
	pTracer = new RayCast(this);
	pCurrentCamera = new PinholeCamera();
	pAmbientLight = new AmbientLight();

	PointLight *light1 = new PointLight();
	light1->SetPosition(Point3D(10,10,-5));
	AddLight((Light*)light1);

	PointLight *light2 = new PointLight();
	light2->SetPosition(Point3D(100,100,-1500));
	AddLight((Light*)light2);

	pAmbientLight->ScaleRadiance(0.05f);
	pAmbientLight->SetColor(RGBColor(1.0f,1.0f,1.0f));

	Sphere *sp1 = new Sphere();
	Phong *mat1 = new Phong();
	mat1->SetKd(1.0f);
	mat1->SetCd(RGBColor(1.0f,1.0f,1.0f));
	mat1->SetKs(RGBColor(0.3f,0.3f,0.3f));
	mat1->SetExp(0.25f);
	sp1->SetCenter(Point3D(-100.0, 100.0, -100.0));
	sp1->SetRadius(100.0);
	sp1->SetMaterial(mat1);

	Sphere *sp2 = new Sphere();	
	Matte *mat2 = new Matte();
	mat2->SetKd(1.0f);
	mat2->SetCd(RGBColor(1.0f,0.0f,0.0f));
	sp2->SetCenter(Point3D(200.0, 200.0, -150.0));
	sp2->SetRadius(80.0);
	sp2->SetMaterial(mat2);

	Sphere *sp3 = new Sphere();
	Phong *mat3 = new Phong();
	mat3->SetKd(1.0f);
	mat3->SetCd(RGBColor(0.0f,0.0f,1.0f));
	mat3->SetKs(RGBColor(0.3f,0.3f,0.3f));
	mat3->SetExp(0.9f);
	sp3->SetCenter(Point3D(150.0, -100.0, -200.0));
	sp3->SetRadius(130.0);
	sp3->SetMaterial(mat3);

	Sphere *sp4 = new Sphere();
	Phong *mat4 = new Phong();
	mat4->SetKd(1.0f);
	mat4->SetCd(RGBColor(0.0f,1.0f,0.0f));
	mat4->SetKs(RGBColor(1.0f,1.0f,1.0f));
	mat4->SetExp(300.0f);
	sp4->SetCenter(Point3D(-200.0, -150.0, -100.0));
	sp4->SetRadius(130.0);
	sp4->SetMaterial(mat4);

	Sphere *sp5 = new Sphere();
	Reflective *mat5 = new Reflective();
	mat5->SetKd(1.0f);
	mat5->SetCd(RGBColor(0.0f,0.0f,0.0f));
	mat5->SetKs(RGBColor(1.0f,0.0f,0.0f));
	mat5->SetExp(1.0f);
	sp5->SetCenter(Point3D(-300.0, 150.0, 100.0));
	sp5->SetRadius(130.0);
	sp5->SetMaterial(mat5);

	Sphere *sp6 = new Sphere();
	Reflective *mat7 = new Reflective();
	mat7->SetKd(1.0f);
	mat7->SetCd(RGBColor(0.0f,1.0f,0.0f));
	mat7->SetKs(RGBColor(0.0f,0.1f,0.4f));
	mat7->SetExp(8.0f);
	sp6->SetCenter(Point3D(0.0, -150.0, 50.0));
	sp6->SetRadius(70.0);
	sp6->SetMaterial(mat7);

	Triangle *tr1 = new Triangle(Point3D(4000,-200,0),Point3D(-4500,-200,0),Point3D(0,-200,4000));
	Phong *mat8 = new Phong();
	mat8->SetKd(1.0f);
	mat8->SetCd(RGBColor(1.0f,1.0f,1.0f));
	mat8->SetKs(RGBColor(0.0f,0.1f,0.4f));
	mat8->SetExp(8.0f);
	tr1->SetMaterial(mat8);

	Mesh *mesh = new Mesh();
	//mesh->LoadFromFile("c:\\temp\\dragon.ply");
	//mesh->LoadFromFile("c:\\temp\\bunny.ply");
	mesh->LoadFromFile("c:\\temp\\hand.ply");
	//mesh->LoadFromFile("c:\\temp\\sphere.ply");

	//objects.push_back(sp1);
	//objects.push_back(sp2);
	//objects.push_back(sp3);
	//objects.push_back(sp4);
	//objects.push_back(sp5);
	//objects.push_back(sp6);
	//objects.push_back(tr1);
	AddObject(mesh);

	//materials
	materials.push_back(mat1);
	materials.push_back(mat2);
	materials.push_back(mat3);
	materials.push_back(mat4);
	materials.push_back(mat5);
	materials.push_back(mat7);
	materials.push_back(mat8);


	//build KD-Tree
	kdtree = new KdTree<GeoObject,GeoObjectAdapter,ShadeRec>(objects,KdTree<GeoObject,GeoObjectAdapter,ShadeRec>::MULTI_THREADED);
	kdtree->Build();
}

void World::render(ViewPane& viewPane)
{
	pCurrentCamera->setEye(Point3D(0,50,500));
	
	if(angle >= 360) 
	{
		angle = 0;
	}
	double xx = 0;
	double zz = 1;
	double a = PI/180 * angle;
	x = (float)(cos(a) * xx - sin(a) * zz);
	z = (float)(sin(a) * xx + cos(a) * zz);
	pCurrentCamera->setEye(Point3D(x,1,z));
	pCurrentCamera->computeUVW();
	pCurrentCamera->render(*this,viewPane);
	angle += 1;
}

const vector<GeoObject*>& World::GetWorldObjects() const
{
	return objects;
}

//This function use brute force and try to collide with every
//GeoObject in the scene without using kd-tree

#ifdef _DEBUG
ShadeRec World::HitObjectsNoKdTree(const Ray& ray)
{
	ShadeRec sr(this);
	float  tmin = kHugeValue;
	float  t;
	Normal normal;
	Point3D hitPoint;

	vector<GeoObject*>::iterator iter;

	for(iter = objects.begin(); iter != objects.end(); ++iter)
	{
		if((*iter)->Collide(ray,t,sr) && t < tmin)
		{
			tmin = t;
			sr.fDistance = t;
			sr.bHitAnObject = true;
			sr.hitPoint = ray.o + t * ray.d;
			sr.pMaterial = (*iter)->GetMaterial();
			sr.ray = ray;
			normal = sr.normal;
			hitPoint = sr.hitPoint;
		}

		if(sr.bHitAnObject) 
		{
			sr.fDistance = tmin;
			sr.normal = normal;
			sr.hitPoint = hitPoint;
		}
	}

	return sr;
}
#endif
ShadeRec World::HitObjects(const Ray& ray)
{
	ShadeRec sr;
	kdtree->Intersect(ray,&sr);
	sr.pWorld = this;
	return sr;
}

void World::DeleteLights()
{
	if(pAmbientLight)
		delete pAmbientLight;

	vector<Light*>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); ++iter)
	{
		delete (*iter);
	}
	lights.clear();
}

void World::DeleteObjects()
{
	vector<GeoObject*>::iterator iter;
	for(iter = objects.begin(); iter != objects.end(); ++iter)
	{
		delete (*iter);
	}
	objects.clear();
}

void World::DeleteMaterials()
{
	vector<Material*>::iterator iter;
	for(iter = materials.begin(); iter != materials.end(); ++iter)
	{
		delete (*iter);
	}
	objects.clear();
}

void World::AddLight(Light* light)
{
	lights.push_back(light);
}

void World::AddObject(Mesh* meshObject)
{

			Phong *mat4 = new Phong();
			mat4->SetKd(2.0f);
			mat4->SetCd(RGBColor(1.0f,1.0f,0.0f));
			mat4->SetKs(RGBColor(1.0f,0.0f,0.0f));
			materials.push_back(mat4);
		

		//for(unsigned int i = 0; i < 50/*meshObject->numIndices/3*/; ++i)
		for(unsigned int i = 0; i < meshObject->numIndices/3; ++i)
		{
			int indexV0 = meshObject->indicesList[i*3];
			int indexV1 = meshObject->indicesList[i*3 + 1];
			int indexV2 = meshObject->indicesList[i*3 + 2];
			Point3D a(meshObject->vertexList[indexV0]->x,meshObject->vertexList[indexV0]->y,meshObject->vertexList[indexV0]->z);
			Point3D b(meshObject->vertexList[indexV1]->x,meshObject->vertexList[indexV1]->y,meshObject->vertexList[indexV1]->z);
			Point3D c(meshObject->vertexList[indexV2]->x,meshObject->vertexList[indexV2]->y,meshObject->vertexList[indexV2]->z);
			

			//a = a * (4.f);
			//b = b * (4.f);
			//c = c * (4.f);

			a = a * 0.1f;
			b = b * 0.1f;
			c = c * 0.1f;

			//a = a * 3000.f;
			//b = b * 3000.f;
			//c = c * 3000.f;

			Triangle *tr = new Triangle(a,b,c);
			tr->InvertNormal();
	//TODO: delete this from here
			tr->SetMaterial(mat4);


			objects.push_back(tr);
		}
}