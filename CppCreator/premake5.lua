MacOSVersion = MacOSVersion or "14.5"

project "CppCreator"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	staticruntime "On"

	debugdir ("%{prj.location}")

	architecture "x86_64"

	warnings "Extra"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.inl",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
	}

	includedirs
	{
		"src",

		"%{wks.location}/CppCreator/src",
	}

	links
	{
		"CppCreator",
	}

	filter "system:windows"
		defines "CC_PLATFORM_DESKTOP"
		defines "CC_PLATFORM_WINDOWS"
		systemversion "latest"
		staticruntime "on"

        defines
        {
            "NOMINMAX"
        }

	filter "system:linux"
		defines "CC_PLATFORM_DESKTOP"
		defines "CC_PLATFORM_LINUX"
		defines "CC_PLATFORM_UNIX"
		systemversion "latest"
		staticruntime "on"

    filter "system:macosx"
		defines "CC_PLATFORM_DESKTOP"
		defines "CC_PLATFORM_MACOS"
		defines "CC_PLATFORM_UNIX"
		defines "CC_PLATFORM_APPLE"
		systemversion(MacOSVersion)
		staticruntime "on"

	filter "action:vs*"
    	buildoptions { "/Zc:preprocessor" }

	filter "action:xcode*"
		-- Note: If we don't add the header files to the externalincludedirs
		-- we can't use <angled> brackets to include files.
		externalincludedirs(includedirs())

	filter "configurations:Debug"
		defines "CC_CONFIG_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "CC_CONFIG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CC_CONFIG_DIST"
		runtime "Release"
		optimize "Full"
		linktimeoptimization "on"
