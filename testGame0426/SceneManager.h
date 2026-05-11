#pragma once
#include "Scene.h"

/// @brief シーンマネージャー
/// @remark このクラスで管理するシーンは Scene を継承する必要があります。
class SceneManager
{
public:

    SceneManager();

    /// @brief メンバ変数の後始末をします。
    ~SceneManager();

    /// @brief アクティブなシーンを更新します。
    /// @remark アクティブなシーンが無ければ何もしません。
    void Update() const;

    /// @brief アクティブなシーンを描画します。
    /// @remark アクティブなシーンが無ければ何もしません。
    void Draw() const;

    /// @brief 管理するシーンを追加します。
    /// @tparam SceneType 管理するシーンの型
    /// @param name シーン名
    /// @note テンプレート関数はインライン定義する必要があります。
    /// @warning SceneType はどんな型でも許容してしまうので、コンセプトや SFINAE で制約を付ける必要があります。
    template <class SceneType>
    void Add(const std::string_view name)
    {
        // [HACK] 重複非許容にする必要があります。
        m_scenes[name] = new SceneType{ *this };

        // 最初に追加されたシーンがデフォルトのシーンです。
        if (m_nowScene == nullptr)
        {
            m_nowScene = m_scenes[name];
            m_nowScene->Init();
        }
    }

    /// @brief アクティブなシーンを切り替えます。
    /// @param name 切り替え先のシーン名
    void ChangeScene(std::string_view name);

private:

    /// @brief シーンコンテナ
    std::unordered_map<std::string_view, Scene*> m_scenes;

    /// @brief アクティブなシーン
    Scene* m_nowScene;
};
