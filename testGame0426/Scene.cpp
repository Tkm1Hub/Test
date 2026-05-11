#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(SceneManager& manager)
    : m_manager{ manager } {
}

void Scene::Init()
{
    // –³ˆ—
}

void Scene::Update()
{
    // –³ˆ—
}

void Scene::Draw() const
{
    // –³ˆ—
}

void Scene::ChangeScene(const std::string_view name)
{
    m_manager.ChangeScene(name);
}
