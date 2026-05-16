#include "UIContainer.h"
#include "UIBase.h"

void UIContainer::Add(std::shared_ptr<UIBase>ui)
{
	pendingUiList.push_back(ui);
}

void UIContainer::Update()
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

void UIContainer::Draw()
{
	for (auto& ui : uiList)
	{
		ui->Draw();
	}
}