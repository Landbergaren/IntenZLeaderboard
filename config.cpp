class CfgPatches
{
	class IntenzLeaderboard_scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class IntenzLeaderboard
	{
		
		dir = "IntenzLeaderboard";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Test Mod";
		credits = "0";
		author = "0";
		authorID = "0"; 
		version = ""; 
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{	
			class gameScriptModule
			{
				value = "";
				files[] = {"@IntenzLeaderboard/addons/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"@IntenzLeaderboard/addons/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"@IntenzLeaderboard/addons/Scripts/5_Mission"};
			};
		};
	};
};