#include "ui.hh"
#include "../globals.hh"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

void ui::render() {
    if (!globals.active) return;

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin(window_title, &globals.active, window_flags);
    {
        ImGui::Checkbox("Enable", &clicker::C_toggle);
        ImGui::SliderInt("", &clicker::CPS, 1, 20, "%d CPS");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Checkbox("Only MC", &clicker::C_InMC);
    }
    ImGui::End();
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    // Cores modernas (preto e branco)
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Cores principais (preto e branco)
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f); // Fundo da janela (preto suave)
    colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Barra de título (preto suave)
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Barra de título ativa (preto mais claro)
    colors[ImGuiCol_Button] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Botões (preto suave)
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Botões ao passar o mouse (cinza escuro)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Botões pressionados (cinza mais claro)
    colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Fundo dos inputs (preto suave)
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Hover no fundo dos inputs
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f); // Ativo no fundo dos inputs
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f); // Deslizador (cinza claro)
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Deslizador ativo (branco suave)

    // Bordas arredondadas
    style.WindowRounding = 8.0f;   // Arredondamento das bordas da janela
    style.FrameRounding = 6.0f;    // Arredondamento dos botões e inputs
    style.GrabRounding = 6.0f;     // Arredondamento do controle de slider

    // Ajuste de espessura das bordas
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;

    // Ajustes no preenchimento dos elementos
    style.ItemSpacing = ImVec2(10, 5); // Distância entre os itens
    style.WindowPadding = ImVec2(10, 10); // Preenchimento da janela
    style.FramePadding = ImVec2(10, 5);  // Preenchimento do frame

    // Ajuste do layout de texto e centralização
    style.ItemInnerSpacing = ImVec2(10, 5);  // Distância entre texto e controles
    style.IndentSpacing = 10.0f; // Espaçamento para o indent do conteúdo

    // Resolução da tela e posição inicial da janela
    if (window_pos.x == 0) {
        RECT screen_rect{};
        GetWindowRect(GetDesktopWindow(), &screen_rect);
        screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
        window_pos = (screen_res - window_size) * 0.5f;

        // Inicia as imagens aqui
    }
}
