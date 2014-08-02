#pragma comment(lib, "Irrlicht.lib")
#include <irrlicht.h>

#include "OculusRenderer.h"

using namespace irr;

int Width = 1280;
int Height = 720;

int main()
{
    // Initialize Irrlicht
	const core::dimension2du videoDim(Width,Height);

	IrrlichtDevice *device = createDevice(video::EDT_DIRECT3D9, videoDim, 32, false );

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	// Initialize Oculus Rift Renderer
	OculusRenderer oculusRenderer(driver->getExposedVideoData().D3D9.HWnd, driver, smgr);


	// FPS camera with no vertical movement. Use Oculus Rift for that
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.5f, -1,
			0, 0, true,
			0.f, false,
			true);

	camera->setPosition(irr::core::vector3df(0, 200.0f, 0));

    // add stuff
	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
		"media/terrain.png",
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, -20.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);

	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0,
			driver->getTexture("media/terraintex.png"));



    int frames = 0;

    while(device->run())
    {
        driver->beginScene(true, true, irr::video::SColor(255, 150, 140, 255));

		camera->OnAnimate(device->getTimer()->getTime());
		camera->updateAbsolutePosition();
		oculusRenderer.drawAll(camera->getAbsolutePosition(), camera->getRotation().Y, irr::video::SColor(255, 150, 140, 255));
        
        driver->endScene();

		if(++frames == 100)
		{
			irr::core::stringw title = L"IrrOculusVR [FPS: ";
			title += driver->getFPS();
			title += "]";
			device->setWindowCaption(title.c_str());

			frames = 0;
		}
    }

    return 0;
}