#pragma once
class Object;
class StateBase
{
public:
	void SetOwner(Object* obj)
	{
		Owner = obj;
	}

	// ステートが始まるときに一度だけ呼ばれる関数
	virtual void OnStart() {}

	// ステートが更新されるときに呼ばれる関数
	virtual void OnUpdate() {}

	// ステートが終了する際に一度だけ呼ばれる関数
	virtual void OnExit() {}

	// ステートの名前を取得
	virtual const char* GetName() const = 0;

protected:
	Object* Owner = nullptr;
};