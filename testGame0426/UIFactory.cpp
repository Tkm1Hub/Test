#include "UIFactory.h"
#include "stdafx.h"

std::shared_ptr<HPBarUI>
UIFactory::CreateHPBarUI(const std::shared_ptr<CharacterBase>& target)
{
	auto ui = std::make_shared<HPBarUI>();
	ui->SetTarget(target);
	return ui;
}