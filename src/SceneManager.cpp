#include <SceneManager.h>
#include <btBulletDynamicsCommon.h>

SceneManager::SceneManager(btDiscreteDynamicsWorld* dynamics_world) {
	physics_world_ = dynamics_world;
	UpdateSceneNodes();
}

void SceneManager::UpdateSceneNodes() {
	/* 
		TODO:
		Loop through the physics world to update asscociated Nodes
	*/

}

void SceneManager::SetCamera(Camera cam) {
	cam_ = cam;
}