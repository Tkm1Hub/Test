#pragma once

class SceneManager;

/// @brief シーンの基底クラス
/// @remark SceneManager で管理するシーンはこのクラスを継承する必要があります。
class Scene
{
public:

    /// @brief SceneManager への参照を受け取ります。
    /// @param manager SceneManager への参照
    Scene(SceneManager& manager);

    /// @brief シーンを初期化します。
    /// @remark デフォルトでは何もしません。
    virtual void Init();

    /// @brief シーンを更新します。
    /// @remark デフォルトでは何もしません。
    virtual void Update();

    /// @brief シーンを描画します。
    /// @remark デフォルトでは何もしません。
    virtual void Draw() const;

protected:

    /// @brief アクティブなシーンを切り替えます。
    /// @param name 切り替え先のシーン名
    void ChangeScene(std::string_view name);

private:

    /// @brief SceneManager への参照
    /// @note ポインタを使うより安全です。
    SceneManager& m_manager;
};
