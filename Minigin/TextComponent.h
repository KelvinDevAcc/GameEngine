#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
    class TextComponent final : public Component
    {
    public:
        void Update() override;
        void Render() const override;

        void SetText(const std::string& text);
        void SetPosition(float x, float y) override;

        TextComponent(std::string text, std::unique_ptr<Font> font);
        ~TextComponent() override = default;
        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;

        const char* GetComponentType() const override { return "Text"; }

    private:
        bool m_needsUpdate;
        std::string m_text;
        Transform m_transform{};
        std::unique_ptr<Font> m_font;
        std::unique_ptr<Texture2D> m_textTexture;
    };
}