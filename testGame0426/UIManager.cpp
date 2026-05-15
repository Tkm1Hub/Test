#include "UIManager.h"
#include "UIBase.h"

void UIManager::Add(std::shared_ptr<UIBase>ui)
{
	pendingUiList.push_back(ui);
}

void UIManager::Update()
{
	for (auto& ui : uiList)
	{
		ui->Update();
	}

	// íœ
	uiList.erase(
		std::remove_if(
			uiList.begin(),
			uiList.end(),
			[](const std::shared_ptr<UIBase>& ui)
			{
				return ui->GetIsDestroy();
			}
		),
		uiList.end()
	);

	// ’Ç‰Á—\–ñ‚ğ”½‰f
	for (auto& ui : pendingUiList)
	{
		ui->Init();
		uiList.push_back(ui);
	}

	pendingUiList.clear();

}

void UIManager::Draw()
{
	for (auto& ui : uiList)
	{
		ui->Draw();
	}
}