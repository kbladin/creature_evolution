#include "Scene.h"

Scene* Scene::instance_ = NULL;

Scene* Scene::Instance() {
if (!instance_) {
    instance_ = new Scene();
  }
  return instance_;
}

Scene::~Scene() {
  // kill shit
}

void Scene::SetCamera(Camera cam) {
  cam_ = cam;
}

Camera* Scene::GetCamera() {
  return &cam_;
}

