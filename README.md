MeshHistogram
=============
This program can directly run "histogram/debug/MeshHistogram.exe"  
"LoadMesh": Load mesh by ".obj", ".off", ".ply" format.  
"AddNoise": Add random Gaussian noise to mesh vertices.  
"RemoveDV": Removes all duplicate vertices (or distance between two vertices within the close-up range).  
"Normalize": Normalize the model inside the unit cube.  
"MeshHistogram": Normalize the model first, then, randomly select 1000 pairs of vertices,compute a histogram of the distances between them and  print the histogram in the window.  
  
The code of implementing these function above is in MeshOperation.cpp
