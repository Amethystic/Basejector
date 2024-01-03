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

static const char* status[]{ "Game 1", "Game 2" };
static int selected_cheat = 0;

class initWindow {
public:
    const char* window_title = "YourCheatDomain.gg";
    ImVec2 window_size{ 400, 205 };
    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
} iw;

void load_styles()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    {
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.45f, 0.87f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.07f, 0.32f, 0.71f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.79f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImColor(21, 21, 21, 255);
        colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
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
                        ImGui::Text("Status:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("?");

                        ImGui::Text("Update Ver:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("0.0.0.0");
                    }
                    else if (selected_cheat == 1) // Game 2
                    {
                        ImGui::Text("Status:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("?");

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
                    if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() - 16, 23)))
                    {
                        inject(L"YourGameName.Exe", L"YourCheatName.dll");
                        /*exit(0);*/ // if u want u can ctrl + k + c that exit func or delete it if u want to
                    }
                }
                else if (selected_cheat == 1) // Game 2
                {
                    //if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() - 16, 23)))
                    //{
                    //    inject(L"YourGameName.Exe", L"YourCheatName.dll");
                    //    /*exit(0);*/ // if u want u can ctrl + k + c that exit func or delete it if u want to
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