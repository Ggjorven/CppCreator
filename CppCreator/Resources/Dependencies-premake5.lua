------------------------------------------------------------------------------
-- Bug fixes
------------------------------------------------------------------------------
CC_BEGIN_BUGFIX_LIST()
CC_START_BUGFIX("Bugfix for C++ Modules (same module file name per project)")
-- Visual Studio: Bugfix for C++ Modules (same module file name per project)
-- https://github.com/premake/premake-core/issues/2177
require("vstudio")
premake.override(premake.vstudio.vc2010.elements, "clCompile", function(base, prj)
	local m = premake.vstudio.vc2010
	local calls = base(prj)

	if premake.project.iscpp(prj) then
		table.insertafter(calls, premake.xmlDeclaration,  function()
			premake.w('<ModuleDependenciesFile>$(IntDir)\\%%(RelativeDir)</ModuleDependenciesFile>')
			premake.w('<ModuleOutputFile>$(IntDir)\\%%(RelativeDir)</ModuleOutputFile>')
			premake.w('<ObjectFileName>$(IntDir)\\%%(RelativeDir)</ObjectFileName>')
		end)
	end

	return calls
end)
CC_END_BUGFIX()
CC_END_BUGFIX_LIST()
------------------------------------------------------------------------------

------------------------------------------------------------------------------
-- Dependencies
------------------------------------------------------------------------------
Dependencies =
{
	CC_DEPENDENCY_MAPPING
}

-- TODO: Include dependencies
-- TODO: Link dependencies
------------------------------------------------------------------------------

------------------------------------------------------------------------------
-- Defines
------------------------------------------------------------------------------
MacOSVersion = "CC_MACOS_VERSION"
OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}"
------------------------------------------------------------------------------