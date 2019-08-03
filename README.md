# Mountains
## Real-Time Procedural Terrain Generation using OpenGL Compute Shaders.
Terrain is generated by populating a 3-dimensional array with "density" values using a signed distance function (see https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch01.html). This grid is then polygonized using the Marching Cubes algorithm (see http://paulbourke.net/geometry/polygonise/). This offers the advantage of being able to render any 3D shape for which an SDF can be created, something that isn't possible with a heightmap approach.

The terrain is split into chunks using an Octree with greater depth nearer the camera, such that closer chunks are generated with finer detail. The significant speedup obtained by parallelising the scalar field generation and Marching Cubes algorithm using compute shaders allows this octree to be updated and new terrain at the correct level of detail to be generated each time the camera moves.

## Note
This code requires a modern GPU with a recent version of OpenGL, as well as the following libraries:
* GLFW
* GLEW
* GLM
