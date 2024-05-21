workspace "st9"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "st9"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SFML"] = "Vendor/SFML/SFML-2.6.0/include"
IncludeDir["ImGui"] = "Vendor/imgui"
IncludeDir["glm"] = "Vendor/glm"
IncludeDir["spd_log"] = "Vendor/spdlog/include"

-- Projects
group "Dependencies"
	include "Vendor/imgui"
group ""

include "st9"
