///////////////////////////////////////////////////////////////////////////////
//	File:    PlyLoader.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "PlyLoader.h"
#include "ply.h"
#include "Vertex.h"
#include <string.h>

PlyLoader::PlyLoader()
{
}

bool PlyLoader::Load(FILE *fp,Vertex**& vList,unsigned int &numVertices,int*& indicesList,unsigned int &numIndices)
{
	PlyProperty vert_props[] = { /* list of property information for a vertex */
	{"x", Float32, Float64, offsetof(PlyVertex,x), 0, 0, 0, 0},
	{"y", Float32, Float64, offsetof(PlyVertex,y), 0, 0, 0, 0},
	{"z", Float32, Float64, offsetof(PlyVertex,z), 0, 0, 0, 0},
	{"nx", Float32, Float64, offsetof(PlyVertex,nx), 0, 0, 0, 0},
	{"ny", Float32, Float64, offsetof(PlyVertex,ny), 0, 0, 0, 0},
	{"nz", Float32, Float64, offsetof(PlyVertex,nz), 0, 0, 0, 0},
	};

	PlyProperty face_props[] = { /* list of property information for a face */
	{"vertex_indices", Int32, Int32, offsetof(PlyFace,verts),
    1, Uint8, Uint8, offsetof(PlyFace,nverts)},
	};
  ////////////////////
	PlyFile *ply = read_ply (fp);
	char *elem_name;
	int i,j;
	int elem_count;

	for (i = 0; i < ply->num_elem_types; i++) 
	{
		
		/* prepare to read the i'th list of elements */
		elem_name = setup_element_read_ply (ply, i, &elem_count);

		if (equal_strings ("vertex", elem_name)) 
		{
			/* create a vertex list to hold all the vertices */
			vList = new Vertex*[elem_count];
			numVertices = elem_count;
		

			/* set up for getting vertex elements */
			/* (we want x,y,z) */

			setup_property_ply (ply, &vert_props[0]);
			setup_property_ply (ply, &vert_props[1]);
			setup_property_ply (ply, &vert_props[2]);

			/* we also want normal information if it is there (nx,ny,nz) */

			for (j = 0; j < ply->elems[i]->nprops; j++) 
			{
				PlyProperty *prop;
				prop = ply->elems[i]->props[j];
				if (equal_strings ("nx", prop->name)) 
				{
					setup_property_ply (ply, &vert_props[3]);
				}
				if (equal_strings ("ny", prop->name)) 
				{
					setup_property_ply (ply, &vert_props[4]);
				}
				if (equal_strings ("nz", prop->name)) 
				{
					setup_property_ply (ply, &vert_props[5]);
				}
			}

			PlyOtherProp* otherProps = get_other_properties_ply (ply,offsetof(PlyVertex,other_props));

			for (j = 0; j < elem_count; j++) 
			{
				PlyVertex plyVertex;
				vList[j] = new Vertex();
				get_element_ply (ply, (void *) &plyVertex);
				memcpy(vList[j],&plyVertex,sizeof(Vertex));
			}
		}
		else if (equal_strings ("face", elem_name)) 
		{
			elem_count *= 3;
			/* create a list to hold all the face elements */
			indicesList = new int[elem_count];
			numIndices = elem_count;

			/* set up for getting face elements */
			/* (all we need are vertex indices) */

			setup_property_ply (ply, &face_props[0]);
			PlyOtherProp* otherProps = get_other_properties_ply (ply,offsetof(PlyFace,other_props));

			/* grab all the face elements and place them in our list */

			for (j = 0; j < elem_count; j+=3) 
			{
				PlyFace face;
				get_element_ply (ply, (void *) &face);

				//TODO: memcpy here
				indicesList[j] = face.verts[0];
				indicesList[j + 1] = face.verts[1];
				indicesList[j + 2] = face.verts[2];
			}
		}
		else  /* all non-vertex and non-face elements are grabbed here */
		{
			get_other_element_ply (ply);
		}
	}

	close_ply (ply);
	free_ply (ply);
	return true;
}