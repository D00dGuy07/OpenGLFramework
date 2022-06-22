# OpenGLFramework
This is my OpenGL rendering framework. It has a few demos for testing included. Whenever I implement a new big feature, I usually create a new test demo as well. Particles is the latest one. Here is a list:

* Particles
	* A very simple 2d particle emitter that uses a post process blur effect.
* InstancedCube
	* A 3D scene where you can fly around in an area with over one million colored cubes.
* ComputeVertices
	* A plane with variable resolution and every frame, a compute shader moves around the vertices with a simplex noise function.
* ComputeTexture
	* A quad with a texture generated in a compute shader.
* PostProcessQuad
	* A quad with multiple colors which is rendered to a framebuffer and then sort of pixelized in a post process pass.

Most of these demos misuse features and are way too complex than they need to be, they are just a proof of concept that I use to test the framework as I develop it.