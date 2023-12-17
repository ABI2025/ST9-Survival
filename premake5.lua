workspace "st9"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "st9"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SFML"] = "vendor/SFML/SFML-2.6.0/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["spd_log"] = "vendor/spdlog/include"

-- Projects
group "Dependencies"
	include "vendor/imgui"
group ""

include "st9"
