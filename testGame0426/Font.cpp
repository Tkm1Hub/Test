#include "Font.h"
#include "stdafx.h"

int Font::DamageFont = -1;

void Font::Init()
{
	DamageFont =
		CreateFontToHandle(
			"Œ¹óƒ‰ƒeƒS v2",
			48,
			3,
			DX_FONTTYPE_ANTIALIASING_EDGE_4X4
		);
}