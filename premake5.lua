workspace "GBox"                     --工作区
    architecture "x64"              --架构
    startproject "Sandbox"          --[[启动项目]]

    configurations
    {                               --配置
        "Debug",
        "Release",
        "Dist"
    }

    -- flags                           --设置编译器选项
	-- {
	-- 	"MultiProcessorCompile"     --多处理器并行编译
	-- }

-- [[起别名]]
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"                 --（方便输出和中间目录编写）
IncludeDir = {}                                                                 --创建一个名为IncludeDir的表
IncludeDir["GLFW"] = "GBox/vendor/GLFW/include"                                  --将表的"GLFW"键索引到此路径
IncludeDir["Glad"] = "GBox/vendor/Glad/include"                                  --将表的"Glad"键索引到此路径
IncludeDir["ImGui"] = "GBox/vendor/imgui"                                        --将表的"ImGui"键索引到此路径
-- IncludeDir["glm"] = "GBox/vendor/glm"                                            --将表的"ImGui"键索引到此路径
-- IncludeDir["stb_image"] = "GBox/vendor/stb_image"

---------------------------------------------------------------------------------------
-- 包含GBox/GBox/vendor/GLFW、GBox/GBox/vendor/Glad、GBox/GBox/vendor/imgui中的premake文件，将其作为依赖项，并合并到这里
-- group "Dependencies"
    include "GBox/vendor/GLFW"
    include "GBox/vendor/Glad"
    include "GBox/vendor/imgui"

-- group ""                                                                        --包含所有未分组的文件

--[[
    XXXX
]]
---------------------------------------------------------------------------------------

--[[项目GBox]]
project "GBox"                       --项目
    location "GBox"                  --项目文件的输出目录（填写解决方案GBox之下的路径 "GBox/GBox"）
    kind "SHAREDLib"                --类型（动态库）
    language "C++"                  --语言
    cppdialect "C++17"              --C++标准（编译时）
    staticruntime "off"              --是否将运行时库静态链接运行时库（dll属性的文件需要关闭）

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")                           --输出目录(.. XX ..中 ".."是字符串连接符)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")                          --中间目录

    pchheader "gboxpch.h"            --预编译头文件
    pchsource "GBox/src/gboxpch.cpp"

    files                           --将源代码文件包含到项目中
    {
       "%{prj.name}/include/**.h",
       "%{prj.name}/src/**.cpp"
    --    "%{prj.name}/vendor/stb_image/**.h",
    --    "%{prj.name}/vendor/stb_image/**.cpp",
    --    "%{prj.name}/vendor/glm/glm/**.hpp",
    --    "%{prj.name}/vendor/glm/glm/**.inl"
    }

    -- defines
    -- {
    --     "_CRT_SECURE_NO_WARNINGS"
    -- }

    includedirs                     --库文件（包含库目录）
    {
        "%{prj.name}/include",
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",                                                   --将IncludeDir表中GLFW键索引的值（地址）作为一个库文件路径
        "%{IncludeDir.Glad}",                                                   --将IncludeDir表中Glad键索引的值（地址）作为一个库文件路径
        "%{IncludeDir.ImGui}"                                                  --将IncludeDir表中ImGui键索引的值（地址）作为一个库文件路径
        -- "%{IncludeDir.glm}",                                                    --将IncludeDir表中glm键索引的值（地址）作为一个库文件路径
        -- "%{IncludeDir.stb_image}"
    }

    links                           --为GBox项目(.dll)链接文件
    {
        "GLFW",                                                                 --链接上方项目GLFW
        "opengl32.lib",
        "Glad",                                                                 --链接上方项目Glad
        "ImGui"                                                                --链接上方项目ImGui
    }

    filter "system:windows"         --过滤器(如果系统是windows)   >>> !!!  filter, not filters  !!!
        systemversion "latest"      --windows SDK 版本

        defines
        {                           --宏的声明
            "GBOX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        --  //////////////////////////////////////////////////////////////////////
        --  ////  NOW WE USE GBox AS A STATIC LIB, SO DON'T NEED THIS COMMAND  ////
        --  //////////////////////////////////////////////////////////////////////
        postbuildcommands           --构建项目完成后执行的指令
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
            --将当前项目的构建目标文件复制到 "../bin/" 下的一个名为 "Debug/Sandbox" 或 "Release/Sandbox" 的子目录中
        }

    filter "configurations:Debug"   -->>> !!!  configurations, not configuration  !!!
        defines "GBox_DEBUG"
        runtime "Debug"
        symbols "On"                --编译器是否生成带有调试符号的可执行文件

    filter "configurations:Release"
        defines "GBox_RELASE"
        runtime "Release"
        optimize "On"               --是否开启代码优化

    filter "configurations:Dist"
        defines "GBox_DIST"
        runtime "Release"
        optimize "On"

---------------------------------------------------------------------------------------------------------------

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files                          
    {
       "%{prj.name}/include/**.h",
       "%{prj.name}/src/**.cpp"
    }

    includedirs                      
    {
        "GBox/vendor/spdlog/include",
        "GBox/include",
        "GBox/src",
        "GBox/vendor"
        -- "%{IncludeDir.glm}"
    }

    links                           --链接
    {
        "GBox"
    }

    filter "system:windows"        
        systemversion "latest"

        defines
        {
            
        }

        filter "configurations:Debug"
            defines "GBox_DEBUG"
            runtime "Debug"
            symbols "On"            

        filter "configurations:Release"
            defines "GBox_RELASE"
            runtime "Release"
            optimize "On"           

        filter "configurations:Dist"
            defines "GBox_DIST"
            runtime "Release"
            optimize "On"