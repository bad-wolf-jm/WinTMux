#ifndef APIENTRY
#    undef APIENTRY
#endif

#include <Windows.h>

#include "Core/ControlSequences.h"
#include "Core/String.h"
#include "MainWindow/MainWindow.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback( int error, const char *description )
{
    fprintf( stderr, "GLFW Error %d: %s\n", error, description );
}

static KeyboardHandler  keyboardHandler;
static ControlSequences controlSequences;
static string_t         _currentCommand;
static int              cursorPosition   = 0;
static bool             commandInputMode = false;

MainWindow mainWindow{};

void OnKeyPressed( GLFWwindow *window, int keycode, int scancode, int action, int mods )
{
    if( action != GLFW_PRESS && action != GLFW_REPEAT )
        return;

    if( keycode >= 340 && keycode <= 348 )
        return;

    auto const &keyCode = keyboardHandler.GetKeyCode( keycode );
    mainWindow.OnKeyPress( keyCode, keyboardHandler.GetModifierState( mods ) );
}

ImFont *LoadFont( path_t fontName, uint32_t fontSize )
{
    // clang-format off
    static ImWchar charRanges[] = { 
        0x0020, 0x00FF, // Basic Latin and Latin Supplement
        0x2070, 0x209F, // Superscripts and subscripts
        0x2100, 0x214F, // Letter-like symbols
        0x2200, 0x2300, // Mathematical operators
        0x2500, 0x257F, // Box drawing
        0x2A00, 0x2AFF, // Supplemental
        0x0370, 0x03ff, // Greek characters
        0x23FB, 0x23FE, // IEC Power Symbol
        0x2655, 0x2655, // Octicons
        0x26A1, 0x26A1, // Octicons
        0xF400, 0xF532, // Octicons
        0x2B58, 0x2B58, // IEC Power Symbols
        0xE000, 0xE00A, // Pomicons
        0xE0A0, 0xE0A2, // Powerline
        0xE0B0, 0xE0B3, // Powerline
        0xE0A3, 0xE0A3, // Powerline Extra
        0xE0B4, 0xE0C8, // Powerline Extra
        0xE0CA, 0xE0CA, // Powerline Extra
        0xE0CC, 0xE0D4, // Powerline Extra
        0xE300, 0xE3E3, // Weather Icons
        0xE5FA, 0xE6B1, // Seti-UI + Custom
        0xE600, 0xE700, // Devicons
        0xEa60, 0xEBEB, // Codicons
        0xF000, 0xF2E0, // Font Awesome
        0xE000, 0xE200, // Font Awesome Extension
        0xF300, 0xF372, // Font Logos
        0 
    };
    // clang-format on

    ImGuiIO &io   = ImGui::GetIO();
    ImFont  *font = io.Fonts->AddFontFromFileTTF( fontName.string().c_str(), fontSize, nullptr, charRanges );

    return font;
}

int main( int, char ** )
{
    _currentCommand.reserve( 2048 );
    glfwSetErrorCallback( glfw_error_callback );
    if( !glfwInit() )
        return 1;

    // Decide GL+GLSL versions
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow( 2450, 1300, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr );
    if( window == nullptr )
        return 1;

    glfwMakeContextCurrent( window );
    glfwSwapInterval( 1 ); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( glsl_version );
    glfwSetKeyCallback( window, OnKeyPressed );

    int     fontSize       = 18;
    ImFont *normalFont     = LoadFont( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFontMono-Regular.ttf", fontSize );
    ImFont *italicFont     = LoadFont( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-Italic.ttf", fontSize );
    ImFont *boldFont       = LoadFont( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-Bold.ttf", fontSize );
    ImFont *boldItalicFont = LoadFont( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-BoldItalic.ttf", fontSize );

    ImVec4 clear_color = ImVec4( 0.0f, 0.0f, 0.0f, 1.00f );
    // Main loop
    while( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        mainWindow.Render();

        int display_w, display_h;
        glfwGetFramebufferSize( window, &display_w, &display_h );
        glViewport( 0, 0, display_w, display_h );
        glClearColor( clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w );
        glClear( GL_COLOR_BUFFER_BIT );
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        glfwSwapBuffers( window );
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
