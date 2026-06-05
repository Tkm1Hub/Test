#pragma once
#include <memory>

#include "HPBarUI.h"
#include "CharacterBase.h"
#include "UIContainer.h"

class UIFactory
{
public:
    static std::shared_ptr<HPBarUI>
        CreateHPBarUI(const std::shared_ptr<CharacterBase>& target);
};