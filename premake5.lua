workspace "WinTMux"
    configurations { "Debug", "Release" }
    -- location ""


IMGUI_DIR = "ThirdParty/ImGui"

project "WinTMux"
    kind "ConsoleApp"
    language "C++"
    location "Source"
    architecture "x86_64"
    targetdir "Build/Bin/%{cfg.buildcfg}"
    objdir "Build/Obj/%{cfg.buildcfg}"

    files {
        "Source/Main.cpp"
    }
    includedirs { 
        IMGUI_DIR,
        IMGUI_DIR .. "/" .. "misc".. "/" .. "cpp",
        IMGUI_DIR .. "/" .. "backends",
        "ThirdParty/GLFW/include"
    }

    libdirs {
        "ThirdParty/GLFW/lib-vc2022",
        "Build/Bin/%{cfg.buildcfg}",
    }

    links { "ImGui", "glfw3" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

    filter { "system:windows" }
		links { "OpenGL32" }

project "ImGui"
    kind "StaticLib"
    language "C++"
    architecture "x86_64"
    location "ThirdParty/ImGui"
    targetdir "Build/Bin/%{cfg.buildcfg}"
    objdir "Build/Obj/%{cfg.buildcfg}"

    includedirs { 
        IMGUI_DIR,
        IMGUI_DIR .. "/" .. "misc".. "/" .. "cpp",
        "ThirdParty/GLFW/include"
    }
    
    files{
        IMGUI_DIR .. "/" .. "imgui.cpp",
        IMGUI_DIR .. "/" .. "imgui_demo.cpp",
        IMGUI_DIR .. "/" .. "imgui_draw.cpp",
        IMGUI_DIR .. "/" .. "imgui_widgets.cpp",
        IMGUI_DIR .. "/" .. "imgui_tables.cpp",
        IMGUI_DIR .. "/" .. "misc" .. "/" .. "cpp" .. "/" .. "imgui_stdlib.cpp",
        IMGUI_DIR .. "/" .. "backends" .. "/" .. "imgui_impl_glfw.cpp",
        IMGUI_DIR .. "/" .. "backends" .. "/" .. "imgui_impl_opengl3.cpp"
    }

    libdirs "ThirdParty/GLFW/Lib"

	-- Our static lib should not link against GLFW
	filter "kind:not StaticLib"
		links "glfw3"

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"


    filter {}

