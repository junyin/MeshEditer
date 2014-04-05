#pragma once
#include "afxwin.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include <ANN/ANN.h>

#undef min
#undef max
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Mesh/Status.hh>
//#include <wrap/io_trimesh/export_vrml.h>
//#include <IO/Export/vtkVRMLExporter.h>
//#include <IO/Export/vtkExporter.h>
//#include "Rendering/Core/vtkRenderer.h"
//#include "Common/DataModel/vtkDataSet.h"

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

using namespace std;


typedef OpenMesh::PolyMesh_ArrayKernelT<>  MyMesh;

//typedef vtkVRMLExporter::Superclass vtkExporter;

//void MeshAlign(MyMesh &target_mesh, MyMesh &source_mesh);
//void getsampledAnnArray(size_t sample_Pts,int sample_ratio,MyMesh &mesh,ANNpointArray &dataArray);
//void RotateMesh(double rotate_theta,MyMesh &mesh);
void AddNoise(double noise_standard_deviation,MyMesh &mesh);
double FindMaxDistance(MyMesh &mesh);
//void RemoveSameVertices(MyMesh &mesh);
void RemoveSameVertices2(MyMesh &mesh,MyMesh &new_mesh);
void Normalizer(MyMesh &mesh);
void GenMeshHistogram(MyMesh &mesh, double *mesh_histogram);
void VRMLTranslator(MyMesh &mesh);

