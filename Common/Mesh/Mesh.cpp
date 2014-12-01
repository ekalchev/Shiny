///////////////////////////////////////////////////////////////////////////////
//	File:    Mesh.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Mesh.h"
#include "Vertex.h"
#include "PlyLoader.h"


Mesh::Mesh()
{
	vertexList = NULL;
	indicesList = NULL;
}

Mesh::Mesh(Vertex** vList,int nVertices)
{
	numVertices = nVertices;
	vertexList = vList;
}


Mesh::~Mesh()
{
	if(vertexList != NULL)
	{
		for(int i = 0; i < numVertices; ++i)
		{
			delete vertexList[i];
		}
		delete[] vertexList;
	}

	if(indicesList != NULL)
	{
		delete[] indicesList;
	}
}

bool Mesh::LoadFromFile(string filename)
{
	if(FileFormat(filename,"ply") == true)
	{
		FILE *fp = fopen(filename.c_str(),"r");
		PlyLoader::Load(fp,vertexList,numVertices,indicesList,numIndices);
		fclose(fp);
	}
	return false;
}

bool Mesh::FileFormat(string filename,string fileExtension)
{
	fileExtension.insert(0,".");
	if(filename.rfind(fileExtension) == filename.length() - fileExtension.length())
	{
		return true;
	}
	return false;
}