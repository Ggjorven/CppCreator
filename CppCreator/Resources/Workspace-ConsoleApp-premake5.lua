------------------------------------------------------------------------------
-- Workspace
------------------------------------------------------------------------------
workspace "CC_WORKSPACE_NAME"
	architecture "x86_64"
	startproject "CC"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

group "Dependencies"
	CC_DEPENDENCY_INCLUDE_GROUP
group ""

include "CC_APPLICATION_NAME"
------------------------------------------------------------------------------