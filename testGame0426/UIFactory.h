#pragma once
#include <memory>

#include "HPBarUI.h"
#include "DamageableObject.h"
#include "UIContainer.h"

class UIFactory
{
public:
    static std::shared_ptr<HPBarUI>
        CreateHPBarUI(const std::shared_ptr<DamageableObject>& target);
};