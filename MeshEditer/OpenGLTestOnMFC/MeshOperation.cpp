#include "stdafx.h"
#include "OpenGLControl.h"
#include ".\openglcontrol.h"
#include "MeshOperation.h"

#include <math.h>
#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <ANN/ANN.h>
#include <random>


using namespace std; // make std:: accessible

//kd tree
// Global variables
//
int k = 2;			// number of nearest neighbors
int dim = 3;			// dimension
double eps = 0;			// error bound
istream* dataIn = NULL;		// input for data points
istream* queryIn = NULL;	// input for query points

/*Add random Gaussian Noise to verteices*/
void AddNoise(double noise_standard_deviation,MyMesh &mesh)
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0,noise_standard_deviation); //Gaussian distribution: mean value = 0.0

	for (auto it = mesh.vertices_begin(); it != mesh.vertices_end(); ++it)
	{
		double Pt[3] = {};
		for (int d=0;d<dim;d++)
		{
			Pt[d]=*(mesh.point(it).data()+d);
			double randn = distribution(generator);
			if ((randn>=-1.0)&&(randn<=1.0))//Gaussian distribution range [-1.0,1.0]							        
			{
				Pt[d]= Pt[d]*(1.0+randn);
				*(mesh.point(it).data()+d)=float(Pt[d]);
			}
		}
	}
	NOISE_CONTROL = false;
}

/*removes all duplicate vertices (such that the model stays the same)*/
//void RemoveSameVertices(MyMesh &mesh)
//{
//	/*ANN kd-tree find nearest point*/
//	ANNpointArray	meshArray;		
//	ANNpoint		Pt;			// ANN point
//	ANNpoint		queryPt;		// query point
//	ANNidxArray		nnIdx;			// near neighbor indices
//	ANNdistArray		dists;			// near neighbor distances
//	ANNkd_tree*		kdTree;	
//
//	nnIdx = new ANNidx[k];			// allocate near neigh indices
//	dists = new ANNdist[k];			// allocate near neigh distance
//
//	int max_Pts = mesh.n_vertices();
//	meshArray = annAllocPts(max_Pts, dim);
//	queryPt = annAllocPt(dim);
//	Pt = annAllocPt(dim);
//
//	//align mesh vertices to ANNArray for building kd-tree
//	for (MyMesh::VertexIter v_it=mesh.vertices_begin();v_it!=mesh.vertices_end();++v_it)
//	{
//		int index = v_it->idx();
//		//Pt get the space of data array
//		Pt = meshArray[index];
//		double getPt[3] = {};
//
//		for(int d = 0;d < dim; d++)
//		{
//			getPt[d] = *(mesh.point(v_it).data()+d);
//			Pt[d] = getPt[d];
//		}
//		//assign Pt coordinates to data array
//		meshArray[index] = Pt;
//	}
//
//	//build kd-tree
//	kdTree = new ANNkd_tree(// build search structure
//		meshArray,	// the data points
//		max_Pts,	// number of points
//		dim);
//
//	double threshold = 0.00001;
//
//	MyMesh::VertexIter v_it = mesh.vertices_begin();
//	MyMesh::VertexHandle vh_it =  v_it.handle();
//
//	/*Test*/
//	if (!mesh.has_vertex_status())
//		mesh.request_vertex_status();
//	if(!mesh.has_face_status()) 
//		mesh.request_face_status();
//	if(!mesh.has_edge_status())
//		mesh.request_edge_status();
//
//	mesh.delete_vertex(vh_it,false);
//
//	//for (MyMesh::VertexIter v_it=mesh.vertices_begin();v_it!=mesh.vertices_end();v_it++)
//	//{
//	//	int indx = v_it->idx();
//	//	queryPt=meshArray[indx];
//
//	//	kdTree->annkSearch(		// search
//	//		queryPt,		// query point
//	//		k,			// number of near neighbors
//	//		nnIdx,			// nearest neighbors (returned)
//	//		dists,			// distance (returned)
//	//		eps);			// error bound
//
//	//	if(*dists <= threshold)
//	//	{
//	//		MyMesh::VertexHandle vh_it =  mesh.vertex_handle(*nnIdx);
//	//		//mesh.delete_vertex(vh_it, false);
//	//		//true if element handle is marked as deleted
//	//		mesh.status(vh_it).deleted();
//	//		mesh.delete_vertex(vh_it, false);
//	//	}
//	//}
//
//	// Delete all elements that are marked as deleted from memory.
//	mesh.garbage_collection();
//
//	if (mesh.has_vertex_status())
//		mesh.release_vertex_status();
//	if(mesh.has_face_status())
//		mesh.release_face_status();
//	if(mesh.has_edge_status())
//		mesh.release_edge_status();
//	// clean kd-tree
//	delete [] nnIdx; 
//	delete [] dists;
//	delete kdTree;
//	annClose(); 
//}

/*removes all duplicate vertices (such that the model stays the same)*/
void RemoveSameVertices2(MyMesh &mesh,MyMesh &new_mesh)
{
	/*ANN kd-tree find nearest point*/
	ANNpointArray	meshArray;		
	ANNpoint		Pt;		// ANN point
	ANNpoint		queryPt;	// query point
	ANNidxArray		nnIdx;		// near neighbor indices
	ANNdistArray		dists;		// near neighbor distances
	ANNkd_tree*		kdTree;	

	nnIdx = new ANNidx[k];			// allocate near neigh indices
	dists = new ANNdist[k];			// allocate near neigh distance

	int max_Pts = mesh.n_vertices();
	meshArray = annAllocPts(max_Pts, dim);
	queryPt = annAllocPt(dim);
	Pt = annAllocPt(dim);

	/*Test by adding same vertex
	int size = mesh.n_vertices();
	MyMesh::VertexHandle _vh_it = mesh.vertex_handle(size);
	double _dista = mesh.point(mesh.vertices_begin()).data()[0];
	MyMesh::Point temp = mesh.point(mesh.vertices_begin());

	_vh_it = mesh.add_vertex(temp);
	int nsize = mesh.n_vertices();
	MyMesh::VertexHandle _bv_it=mesh.vertices_begin();

	double _dist = mesh.point(_bv_it).data()[0];
	double _distb = mesh.point(_vh_it).data()[0];
	double _dist2 = mesh.point(_bv_it).data()[1];
	double _dist2b = mesh.point(_vh_it).data()[1];
	double _dist3 = mesh.point(_bv_it).data()[2];
	double _dist3b = mesh.point(_vh_it).data()[2];

	double _dis = sqrt(pow(_dist-_distb,2)+pow(_dist2-_dist2b,2)+pow(_dist3-_dist3b,2));
	*/

	//align mesh vertices to ANNArray for building kd-tree
	for (MyMesh::VertexIter v_it=mesh.vertices_begin();v_it!=mesh.vertices_end();++v_it)
	{
		int index = v_it->idx();
		//Pt get the space of data array
		Pt = meshArray[index];
		double getPt[3] = {};

		for(int d = 0;d < dim; d++)
		{
			getPt[d] = *(mesh.point(v_it).data()+d);
			Pt[d] = getPt[d];
		}
		//assign Pt coordinates to data array
		meshArray[index] = Pt;
	}

	//build kd-tree
	kdTree = new ANNkd_tree(// build search structure
		meshArray,			// the data points
		max_Pts,			// number of points
		dim);

	double threshold = 0.0001;
	int counter = 0;

	for(MyMesh::VertexIter v_it = mesh.vertices_begin();v_it!=mesh.vertices_end();++v_it)
	{
		int indx = v_it->idx();
		queryPt=meshArray[indx];

		kdTree->annkSearch(		// search
			queryPt,		// query point
			k,			// number of near neighbors
			nnIdx,			// nearest neighbors (returned)
			dists,			// distance (returned)
			eps);


		if(*(dists+1)>=threshold)
		{
			MyMesh::VertexHandle nvh_it = mesh.vertex_handle(counter);
			MyMesh::Point temp = mesh.point(v_it);
			nvh_it = new_mesh.add_vertex(temp);
			counter += 1;
		}
	}
	// clean kd-tree
	delete [] nnIdx; 
	delete [] dists;
	delete kdTree;
	annClose(); 
	REMOVE_CONTROL=false;
}

/*find the max distance of the model*/
double FindMaxDistance(MyMesh &mesh)
{
	//initial 
	MyMesh::VertexIter v_it1 = mesh.vertices_begin();
	double x_max = mesh.point(v_it1).data()[0];
	double y_max = mesh.point(v_it1).data()[1];
	double z_max = mesh.point(v_it1).data()[2];
	double x_min = mesh.point(v_it1).data()[0];
	double y_min = mesh.point(v_it1).data()[1];
	double z_min = mesh.point(v_it1).data()[2];

	for (MyMesh::VertexIter v_it = mesh.vertices_begin();v_it!=mesh.vertices_end(); ++v_it)
	{
		//max
		if(mesh.point(v_it).data()[0]>x_max) x_max = mesh.point(v_it).data()[0];
		if(mesh.point(v_it).data()[1]>y_max) y_max = mesh.point(v_it).data()[1];
		if(mesh.point(v_it).data()[2]>z_max) z_max = mesh.point(v_it).data()[2];

		//min
		if(mesh.point(v_it).data()[0]<x_min) x_min = mesh.point(v_it).data()[0];
		if(mesh.point(v_it).data()[1]<y_min) y_min = mesh.point(v_it).data()[1];
		if(mesh.point(v_it).data()[2]<z_min) z_min = mesh.point(v_it).data()[2];
	}

	double distance_x = x_max - x_min;
	double distance_y = y_max - y_min;
	double distance_z = z_max - z_min;
	double max_distance = distance_x;

	if (distance_y > max_distance) max_distance = distance_y;
	if (distance_z > max_distance) max_distance = distance_z;

	return max_distance;
}

/*normalize the model inside the unit cube*/
void Normalizer(MyMesh &mesh)
{
	double max_distance = FindMaxDistance(mesh);

	for (MyMesh::VertexIter v_it = mesh.vertices_begin();v_it!=mesh.vertices_end(); ++v_it)
	{
		for (int d = 0; d < 3; d++)
		{
			*(mesh.point(v_it).data()+d) /= max_distance;
		}
	}
	NORMALIZE_CONTROL = FALSE;
}

/*Normalize the model and compute a histogram of the distances between them*/
void GenMeshHistogram(MyMesh &mesh,double *mesh_histogram)
{
	Normalizer(mesh);

	std::default_random_engine generator1;
	std::default_random_engine generator2;
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	int vertices_num = 1000;

	//assign to the new mesh with random vertices
	MyMesh new_mesh1;
	MyMesh new_mesh2;
	for(unsigned int i = 0; i<vertices_num;i++)
	{
		unsigned int random_vit1 ;
		while(true){
			random_vit1 =  int(distribution(generator1)*vertices_num);
			if(random_vit1<mesh.n_vertices()) break;
		}
		MyMesh::VertexHandle v_it1 = mesh.vertex_handle(random_vit1);
		new_mesh1.add_vertex(mesh.point(v_it1));

		unsigned int random_vit2;
		while(true){
			random_vit2 =  int(distribution(generator2)*vertices_num);
			if(random_vit2<mesh.n_vertices()) break;
		}
		MyMesh::VertexHandle v_it2 = mesh.vertex_handle(random_vit2);
		new_mesh2.add_vertex(mesh.point(v_it2));
	}

	//calculate the distances between them
	for(MyMesh::VertexIter v_it1 = new_mesh1.vertices_begin();v_it1 != new_mesh1.vertices_end();++v_it1)
	{
		for(MyMesh::VertexIter v_it2 = new_mesh2.vertices_begin();v_it2 != new_mesh2.vertices_end();++v_it2)
		{
			double distance;

			distance = sqrt(pow(new_mesh1.point(v_it1).data()[0]-new_mesh2.point(v_it2).data()[0],2)
				+pow(new_mesh1.point(v_it1).data()[1]-new_mesh2.point(v_it2).data()[1],2)
				+pow(new_mesh1.point(v_it1).data()[2]-new_mesh2.point(v_it2).data()[2],2));

			*(mesh_histogram+int(distance*1000)) += 1.0;
		}
	}

	//Normalize the histogram
	double max_hist = mesh_histogram[0];
	for (int i = 0; i <1733; i++)
	{
		if(max_hist < *(mesh_histogram+i))
			max_hist = *(mesh_histogram+i);
	}
	for (int i = 0; i <1733; i++)
	{
		*(mesh_histogram+i)/=max_hist;
	}

	HISTOGRAM_CONTROL = FALSE;
}

/*writes the resulting file in the VRML V2.0 format*/
void VRML2Writer(MyMesh &mesh,string filname)
{
	//delete ".off"
	filname.erase(filname.end()-4,filname.end());

	// open file
	ofstream myfile;
	myfile.open (filname+".wrl");
	//write file header
	if (myfile.is_open())
	{
		myfile << "#VRML V2.0 utf8\n";
		myfile << "#Three IndexedFaceSets\n";
		myfile << "Shape {\n";
		myfile << "  geometry IndexedFaceSet {\n";
		myfile << "    coord Coordinate {\n";
		myfile << "      point [\n";
		//write vertices
		for(MyMesh::VertexIter v_it=mesh.vertices_begin();v_it!=mesh.vertices_end();++v_it)
		{
			myfile << "        "<< mesh.point(v_it).data()[0] << " " << mesh.point(v_it).data()[1] << " " <<mesh.point(v_it).data()[2]<< ",\n";
		}
		myfile << "      ]\n";
		myfile << "    }\n";
		myfile << "    coordIndex [\n";
		//write faces
		for(MyMesh::FaceIter f_it=mesh.faces_begin();f_it!=mesh.faces_end();++f_it)
		{
			
			MyMesh::FaceVertexIter fv_it;
			myfile << "      ";
			for (fv_it = mesh.fv_iter(f_it);fv_it;++fv_it)
			{
				MyMesh::VertexHandle vh_it = fv_it.handle();				
				myfile << vh_it.idx()<< " ";
			}
			myfile << ",\n";
		}
		myfile << "    ]\n";
		myfile << "  }\n";
		myfile << "}\n";
		myfile.close();
	}
}
