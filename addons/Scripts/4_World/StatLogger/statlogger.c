static string baseFolderLocation = "$profile:Stats-";

class StatLogger
{
    ref PlayerStatsModel statModel = new PlayerStatsModel;

    void OnConnectHandler(string id, string name) {
        statModel = Load(id);
		
        statModel.name = name;

        Save(statModel, id);
    }
	
	void OnDisconnectHandler(string id, int longestShot, int zKilled, int playTime, int distTrav) {
		statModel = Load(id);
		statModel.longestShot = longestShot;
		statModel.zKilled = zKilled;
		statModel.playTime = playTime;
		statModel.distTrav = distTrav;
		Save(statModel, id);
}

    void DeathHandler(string victimId, EntityAI killer, vector pos) {
        statModel = Load(victimId);
		DeathStatsModel death = new DeathStatsModel;
		death.posDeath = Helper.ConvertVectorPosToString(pos);
        death.timeStamp = Helper.GetCurrentTime();
		if (killer.IsPlayer()) {
			ref SurvivorBase sbKiller = SurvivorBase.Cast(killer);
			death.killer = sbKiller.GetPlayerID();
			death.weapon = Helper.GetWeaponInHands(sbKiller);
			if (victimId == sbKiller.GetPlayerID()) {
				statModel.suicideCount++;
			}
			else {
				statModel.deathsToPlayerCount++;
			}			
		}
		else if (killer.IsZombie()) {
			statModel.deathsToZCount++;
			death.killer = "zombie";
		}
		else if (killer.IsAnimal()) {
			statModel.deathsToAnimalCount++;
			death.killer = "animal";
		}
        statModel.deaths.Insert(death);
        Save(statModel, victimId);
    }
    
    void KillHandler(string victimId, SurvivorBase sbKiller, vector pos) {
        statModel = Load(victimId);
		
		KillStatsModel kill = new KillStatsModel;
        kill.posKill = Helper.ConvertVectorPosToString(pos);
        kill.timeStamp = Helper.GetCurrentTime();
        kill.victim = victimId;
		kill.weapon = Helper.GetWeaponInHands(sbKiller);
        statModel.kills.Insert(kill);
		
		Save(statModel, sbKiller.GetPlayerID());
    }
	

    PlayerStatsModel Load(string steamID) {
        PlayerStatsModel statModel = new PlayerStatsModel;
        string FileLocation = baseFolderLocation + steamID + ".json";

        if (FileExist(FileLocation)) {
            JsonFileLoader<PlayerStatsModel>.JsonLoadFile(FileLocation, statModel);
        }
        else {
            JsonFileLoader<PlayerStatsModel>.JsonSaveFile(FileLocation, statModel);
        }
        return statModel;
    }

    void Save(PlayerStatsModel statModel, string steamID) {
        string FileLocation = baseFolderLocation + steamID + ".json";
        JsonFileLoader<PlayerStatsModel>.JsonSaveFile(FileLocation, statModel);
    }
}