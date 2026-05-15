#pragma once
#include "DamageableObject.h"

class CharacterBase :
    public DamageableObject
{
public:
	//ƒJƒvƒZƒ‹
	VECTOR GetCapsuleBottom() const;
	VECTOR GetCapsuleTop() const;
	VECTOR GetCapsuleCenter() const;
	float GetBodyRadius() const { return bodyRadius; }
	float GetBodyHeight() const { return bodyHeight; }

protected:
    float bodyRadius;	// “–‚½‚è”»’è”¼Œa
    float bodyHeight;	// “–‚½‚è”»’è‚‚³
};