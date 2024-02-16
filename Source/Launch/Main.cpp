#include "Core/String.h"
#include "MainWindow/MainWindow.h"
//#include "MainWindow/CommandLine.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback( int error, const char *description )
{
    fprintf( stderr, "GLFW Error %d: %s\n", error, description );
}

static string_t _currentCommand;
static int      cursorPosition   = 0;
static bool     commandInputMode = false;

void OnKeyPressed( GLFWwindow *window, int keycode, int scancode, int action, int mods )
{
    if( action != GLFW_PRESS && action != GLFW_REPEAT )
        return;

    if( keycode >= 340 && keycode <= 348 )
        return;

    std::cout << "KEY"
              << " " << keycode << " " << scancode << " " << action << std::endl;

    if( !commandInputMode )
    {
        // build key sequence for processing.
    }
    else
    {
        // if key is alphanumeric of space, append to the current command

        if( keycode >= GLFW_KEY_A && keycode <= GLFW_KEY_Z )
        {
            _currentCommand += keycode + ( ( mods == GLFW_MOD_SHIFT ) ? 0 : 32 );
        }
        else
        {
            switch( keycode )
            {
            case GLFW_KEY_APOSTROPHE:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '"' : '\'';
                break; /* ' */
            case GLFW_KEY_COMMA:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '<' : ',';
                break; /* , */
            case GLFW_KEY_MINUS:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '+' : '-';
                break; /* - */
            case GLFW_KEY_PERIOD:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '>' : '.';
                break; /* . */
            case GLFW_KEY_SLASH:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '?' : '/';
                break; /* / */
            case GLFW_KEY_0:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? ')' : '0';
                break;
            case GLFW_KEY_1:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '!' : '1';
                break;
            case GLFW_KEY_2:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '@' : '2';
                break;
            case GLFW_KEY_3:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '#' : '3';
                break;
            case GLFW_KEY_4:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '$' : '4';
                break;
            case GLFW_KEY_5:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '%' : '5';
                break;
            case GLFW_KEY_6:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '^' : '6';
                break;
            case GLFW_KEY_7:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '&' : '7';
                break;
            case GLFW_KEY_8:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '*' : '8';
                break;
            case GLFW_KEY_9:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '(' : '9';
                break;
            case GLFW_KEY_SEMICOLON:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? ':' : ';';
                break; /* ; */
            case GLFW_KEY_EQUAL:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '+' : '=';
                break; /* = */
            case GLFW_KEY_LEFT_BRACKET:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '{' : '[';
                break; /* [ */
            case GLFW_KEY_BACKSLASH:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '|' : '\\';
                break; /* \ */
            case GLFW_KEY_RIGHT_BRACKET:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '}' : ']';
                break; /* ] */
            case GLFW_KEY_GRAVE_ACCENT:
                _currentCommand += ( mods == GLFW_MOD_SHIFT ) ? '~' : '`';
                break; /* ` */
            }
        }
    }

    if( ( keycode == GLFW_KEY_SEMICOLON ) && ( mods & GLFW_MOD_SHIFT ) && !commandInputMode )
    {
        commandInputMode = true;
        cursorPosition   = 0;

        _currentCommand = ":";
    }

    if( keycode == GLFW_KEY_ENTER && commandInputMode )
    {
        commandInputMode = false;
        cursorPosition   = 0;

        _currentCommand.resize( 0 );
    }

    std::cout << _currentCommand << std::endl;
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
    GLFWwindow *window = glfwCreateWindow( 1920, 1080, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr );
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

    int fontSize = 18.0f;
    io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFontMono-Regular.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-ExtraBold.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-ExtraBoldItalic.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-ExtraLight.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-ExtraLightItalic.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-Italic.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-Light.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-LightItalic.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-MediumItalic.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-Bold.ttf", fontSize );
    // io.Fonts->AddFontFromFileTTF( "C:\\GitLab\\WinTMux\\Resources\\Fonts\\JetBrainsMonoNLNerdFont-BoldItalic.ttf", fontSize );

    ImVec4     clear_color = ImVec4( 0.0f, 0.0f, 0.0f, 1.00f );
    MainWindow mainWindow{};
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
