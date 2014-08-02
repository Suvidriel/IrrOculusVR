IrrOculusVR
===========

Oculus Rift SDK 0.4.0 support for Irrlicht 1.7.3 using DirectX 9. Should work with newer Irrlicht
as well with minor modifications. OpenGL-support requires some changes to the shader.

The Oculus Rift-support is still experimental and hasn't been yet tested with a development kit.

The implementation is made FPS cameras in mind. This means that the player's body cannot rotate
around other axes than Y. For cockpit-style cameras some modifications will be required.

The player's direction and head rotation aren't linked together.

main.cpp contains simple example of use.
