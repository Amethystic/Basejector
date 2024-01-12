#include "ImGui/ImGui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "menu.h"
#include "globals.h"

#include "Injector.h"

#include <iostream>
#include <windows.h>

bool doOnce = true;

ImVec4 firstChildBorder = ImColor(42, 42, 42, 255);
ImVec4 firstChildColor = ImColor(17, 17, 17, 255);

ImVec4 seconedChildBorder = ImColor(42, 42, 42, 255);
ImVec4 seconedChildColor = ImColor(21, 21, 21, 255);

static const char* status[]{ "S.A.R.S", "Lethal Company", "CS:GO"};
static int selected_cheat = 0;

class initWindow {
public:
    const char* window_title = "Catnip.lol";
    ImVec2 window_size{ 400, 205 };
    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
} iw;

void load_styles()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    {
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.62f, 0.26f, 0.98f, 0.67f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.12f, 0.29f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.75f, 0.44f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.11f, 0.45f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.57f, 0.22f, 0.85f, 1.00f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.76f, 0.46f, 1.00f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_DockingPreview] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.66f, 0.26f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    ImGuiStyle* style = &ImGui::GetStyle();
    {
        style->WindowTitleAlign = ImVec2(.5, .5);
        style->FramePadding = ImVec2(8, 7);
        style->ItemSpacing = ImVec2(20, 5);
        style->FrameBorderSize = 1;
        style->FrameRounding = 9;
        style->ChildRounding = 9;
        style->WindowRounding = 9;
        style->PopupRounding = 9;
        style->TabRounding = 9;
    }
}

void menu::render()
{
    if (doOnce)
    {
        load_styles();
        doOnce = false;
    }

    if (globals.active)
    {
        ImGui::SetNextWindowSize(iw.window_size);
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::Begin(iw.window_title, &globals.active, iw.window_flags);
        {
            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);

            ImGui::BeginChild("##firstChild", ImVec2(ImGui::GetWindowWidth() - 16, ImGui::GetWindowHeight() - 45), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            {
                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);

                ImGui::BeginChild("##CheatSelection", ImVec2(ImGui::GetWindowWidth() - 16, 55), true);
                {
                    ImGui::TextDisabled("Cheats");

                    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 16);
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
                    {
                        ImGui::Combo("##Cheats", &selected_cheat, status, IM_ARRAYSIZE(status));
                    }
                    ImGui::PopStyleVar();
                }
                ImGui::EndChild();

                ImGui::PopStyleColor(2);
                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);

                ImGui::BeginChild("##InfoSection", ImVec2(ImGui::GetWindowWidth() - 16, 60), true);
                {
                    ImGui::TextDisabled("Cheat Info");
                    if (selected_cheat == 0) // Game 1
                    {
                        ImGui::Text("Status: ");
                        ImGui::SameLine();
                        ImGui::TextDisabled("Detected | W.I.P");

                        ImGui::Text("Update Ver:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("0.0.0.0");
                    }
                    else if (selected_cheat == 1) // Game 2
                    {
                        ImGui::Text("Status: ");
                        ImGui::SameLine();
                        ImGui::TextDisabled("W.I.P");

                        ImGui::Text("Update Ver:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("0.0.0.0");
                    }
                    else if (selected_cheat == 2) // Game 3
                    {
                        ImGui::Text("Status: ");
                        ImGui::SameLine();
                        ImGui::TextDisabled("Detected | W.I.P");

                        ImGui::Text("Update Ver:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("0.0.0.0");
                    }
                }
                ImGui::EndChild();

                ImGui::PopStyleColor(2);
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 6));

                if (selected_cheat == 0) // Game 1
                {
                    //if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() - 16, 23)))
                    //{
                    //    inject(L"Super Animal Royale.exe", L"test.dll");
                    //    exit(0); // if u want u can ctrl + k + c that exit func or delete it if u want to
                    //}
                }
                if (selected_cheat == 1) // Game 1
                {
                    //if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() - 16, 23)))
                    //{
                    //    inject(L"Lethal Company.exe", L"test.dll");
                    //    exit(0); // if u want u can ctrl + k + c that exit func or delete it if u want to
                    //}
                }
                if (selected_cheat == 2) // Game 1
                {
                    //if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() - 16, 23)))
                    //{
                    //    inject(L"csgo.exe", L"test.dll");
                    //    exit(0); // if u want u can ctrl + k + c that exit func or delete it if u want to
                    //}
                }
                ImGui::PopStyleVar();
            }
            ImGui::EndChild();
            ImGui::PopStyleColor(2);
        }
        ImGui::End();
    }
    else
    {
        exit(0);
    }
}