#pragma once

#include "Component.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "../imgui-plot-master/include/imgui_plot.h"
#include "GameObjectBenchmark.h"

namespace dae
{
    class imguiExerciseComponent : public Component
    {
    public:
        imguiExerciseComponent();
        ~imguiExerciseComponent() override;

        void Update() override;

        void Render() const override;

        std::type_info const& GetComponentType() const override { return typeid(imguiExerciseComponent); }


    private:
        static constexpr int buffer_size = 1 << 26; // Define buffer_size as a constant
        static constexpr int inputValueDefault = 10; // Define default value for inputValue

        void RenderExercise1Window() const;
        void RenderExercise2Window() const;

        // Member variables
        mutable int inputValue = inputValueDefault; // Mutable to allow modification in const methods
        mutable std::vector<float> timingsIntBuffer;
        mutable std::vector<float> timingsGameObject3D;
        mutable std::vector<float> timingsGameObject3DAlt;
    };
}