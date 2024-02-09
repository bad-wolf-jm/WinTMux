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

int main( int, char ** )
{
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

    int fontSize = 16.0f;
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

    ImVec4 clear_color = ImVec4( 0.0f, 0.0f, 0.0f, 1.00f );

    // Main loop
    while( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float headerHeight = 25.0f;
        float footerHeight = 25.0f;

        auto       &windowSize     = ImGui::GetIO().DisplaySize;
        static bool window_is_open = true;
        ImGui::PushStyleVar( ImGuiStyleVar_WindowMinSize, ImVec2( fontSize, fontSize ) );
        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );

        ImGui::SetNextWindowPos( ImVec2( 0.0f, 0.0f ) );
        ImGui::SetNextWindowSize( ImVec2( windowSize.x, headerHeight ) );
        ImGui::Begin( "##1", &window_is_open,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                          ImGuiWindowFlags_NoScrollbar );
        {
            float posX = 5.0;
            float posY = ( headerHeight - fontSize ) * 0.5f;
            ImGui::SetCursorPos( ImVec2{ posX, posY } );
            ImGui::Text( "THIS WILL BE THE TITLE" );
        }
        ImGui::End();

        ImGui::SetNextWindowPos( ImVec2( 0.0f, windowSize.y - footerHeight ) );
        ImGui::SetNextWindowSize( ImVec2( windowSize.x, footerHeight ) );
        ImGui::Begin( "##2", &window_is_open,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                          ImGuiWindowFlags_NoScrollbar );
        {
            float posX = 5.0;
            float posY = ( footerHeight - fontSize ) * 0.5f;
            ImGui::SetCursorPos( ImVec2{ posX, posY } );
            ImGui::Text( "THIS WILL BE THE COMMAND LINE" );
        }
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();

        // Rendering
        ImGui::Render();
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
