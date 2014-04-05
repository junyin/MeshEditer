MeshHistogram
=============
Compile and run "MeshHistogram/histogram/OpenGLTestOnMFC.sln".   
"LoadMesh": Load mesh by ".obj", ".off", ".ply" .etc  
"AddNoise": Add random Gaussian noise to mesh vertices.  
"RemoveDV": Removes all duplicate vertices (or distance between two vertices within the close-up range).  
"Normalize": Normalize the model inside the unit cube.  
"MeshHistogram": Normalize the model first, then, randomly select 1000 pairs of vertices,compute a histogram of the distances between them and  print the histogram in the window.  
  
The relevant functions can be found in MeshOperation.cpp.
