#pragma once
#include "afxwin.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include <ANN/ANN.h>
#include <fstream>
#include <iostream>
using namespace std;

#undef min
#undef max
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Mesh/Status.hh>
#include <OpenMesh/Core/IO/exporter/ExporterT.hh>
//#include <wrap/io_trimesh/export_vrml.h>
//#include <IO/Export/vtkVRMLExporter.h>
//#include <IO/Export/vtkExporter.h>

struct MyTraits : public OpenMesh::DefaultTraits
{
	VertexAttributes(OpenMesh::Attributes::Status);
	FaceAttributes(OpenMesh::Attributes::Status);
	EdgeAttributes(OpenMesh::Attributes::Status);
};

//template<class SaveMeshType>
//class vcg::tri::io::ExporterWRL<SaveMeshType>{
//
//	static int Save(MESH_TYPE &mesh, const char *filename, CallBackPos *cb=0)
//	static int Save(MESH_TYPE &mesh, const char *filename, int & savemask, CallBackPos *cb =0)
//	static const char *ErrorMsg(int error)
//	static int GetExportMaskCapability()
//
//};

//using namespace vcg;
//typedef vtkVRMLExporter::Superclass vtkExporter;
using namespace std;

typedef OpenMesh::PolyMesh_ArrayKernelT<>  MyMesh;

void AddNoise(double noise_standard_deviation,MyMesh &mesh);
void RemoveSameVertices2(MyMesh &mesh,MyMesh &new_mesh);
void RemoveSameVertices(MyMesh &mesh);
void Normalizer(MyMesh &mesh);
void GenMeshHistogram(MyMesh &mesh, double *mesh_histogram);
void VRML2Writer(MyMesh &mesh,string FileName);

