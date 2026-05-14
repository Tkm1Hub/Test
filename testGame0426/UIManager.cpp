#include "UIManager.h"
#include "UIBase.h"

void UIManager::Add(std::shared_ptr<UIBase>ui)
{
	uiList.push_back(ui);
}

void UIManager::Update()
{
	for (auto& ui : uiList)
	{
		ui->Update();
	}
}

void UIManager::Draw()
{
	for (auto& ui : uiList)
	{
		ui->Draw();
	}
}