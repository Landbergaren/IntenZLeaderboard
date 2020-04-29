class StatLogger
{
    static const string basePath = "$profile:Leaderboard\\Stats-";
    ref PlayerStatsModel statModelConnect = new PlayerStatsModel;
    ref PlayerStatsModel statModelDisconnect = new PlayerStatsModel;
    ref PlayerStatsModel statModelDied = new PlayerStatsModel;
    ref PlayerStatsModel statModelKill = new PlayerStatsModel;
    ref PlayerStatsModel statModelSave = new PlayerStatsModel;
    ref PlayerStatsModel statModelLoad = new PlayerStatsModel;
    ref StatLogger statLogger;
    void OnConnectHandler(string id, string name) {
        statModelConnect = Load(id);		
        statModelConnect.name = name;
        Save(statModelConnect, id);
    }
	
	void OnDisconnectHandler(SurvivorBase sbPlayer) {
		statModelDisconnect = Load(sbPlayer.GetPlayerID());
		statModelDisconnect.longestShot = sbPlayer.StatGet("longest_survivor_hit");
        statModelDisconnect.zKilled = sbPlayer.StatGet("infected_killed");
        statModelDisconnect.timeSurvived = sbPlayer.StatGet("playtime");
        statModelDisconnect.distTrav = sbPlayer.StatGet("dist");
		Save(statModelDisconnect, sbPlayer.GetPlayerID());
    }

    void DeathHandler(PlayerBase pbKilled, Object source) {
        statModelDied = Load(pbKilled.GetPlayerID());
		DeathStatsModel death = new DeathStatsModel;
		death.posDeath = Helper.ConvertVectorPosToString(pbKilled.GetPosition());
        death.timeStamp = Helper.GetCurrentTime();
		death.longestShot = pbKilled.StatGet("longest_survivor_hit");
		death.zKillCount = pbKilled.StatGet("infected_killed");
		death.timeSurvived = pbKilled.StatGet("playtime");
		death.distTrav = pbKilled.StatGet("dist");
        // Add playerkill to current death list
        death.kills.InsertAll(statModelDied.kills);
        statModelDied.kills.Clear();
        // Add killed animals to current deaths list
        death.animalsKilled.InsertAll(statModelDied.animalsKilled);
        statModelDied.animalsKilled.Clear();
        // Probably suicide
		if (pbKilled == source) {
			ref PlayerBase pbKiller = PlayerBase.Cast(source);
			death.killer = pbKiller.GetPlayerID();

			if ( pbKilled.GetPlayerID() == pbKiller.GetPlayerID())  {
                EntityAI weapon = Helper.GetWeaponInHands(pbKiller);
                if (weapon.IsWeapon() || weapon.IsMeleeWeapon()) {
                    statModelDied.suicideCount++;
                    death.killer = "suicide";
                    death.weapon = weapon.GetType();
                }
                else {
                    statModelDied.deathsToNaturalCauseCount++;
                    death.killer = "natural cause";
                }
            }
        }
        // Killed by another player
        else if (source.IsWeapon() || source.IsMeleeWeapon()) {
            statModelDied.deathsToPlayerCount++;
            string weaponType = source.GetType();
            death.weapon = weaponType;
            PlayerBase killerWithWeapon = PlayerBase.Cast(EntityAI.Cast(source).GetHierarchyParent());
            death.killer = killerWithWeapon.GetPlayerID();
            statLogger = new StatLogger;
            statLogger.KillHandler(killerWithWeapon, pbKilled, weaponType);
        }
        // Killed by fists
        else if (source.IsInherited(SurvivorBase) && source != pbKilled) {
            statModelDied.deathsToPlayerCount++;
            PlayerBase pbMeleeSource = PlayerBase.Cast(source);
            death.killer = pbMeleeSource.GetPlayerID();
            death.weapon = "fists";
            statLogger = new StatLogger;
            statLogger.KillHandler(pbMeleeSource, pbKilled, "fists");
        }
        // Killed by Z or animal
        else if (source.IsEntityAI()) {
			EntityAI eaiKiller = EntityAI.Cast(source);			
			if (eaiKiller.IsZombie()) {
				statModelDied.deathsToZCount++;
				death.killer = "zombie";
			}
			else if (eaiKiller.IsAnimal()) {
				statModelDied.deathsToAnimalCount++;
				death.killer = "animal";
			}
		}
        statModelDied.deaths.Insert(death);
        Save(statModelDied, pbKilled.GetPlayerID());
    }

    
    void KillHandler(PlayerBase killer, PlayerBase target, string weapon) {
        string killerId = killer.GetPlayerID();
        statModelKill = Load(killerId);
		
		KillStatsModel kill = new KillStatsModel;
        kill.posKill = Helper.ConvertVectorPosToString(killer.GetPosition());
        kill.timeStamp = Helper.GetCurrentTime();
        kill.victim.id = target.GetPlayerID();
        kill.victim.timeSurvived = target.StatGet("playtime");
		kill.weapon = weapon;
        kill.distance = vector.Distance(killer.GetPosition(), target.GetPosition());
        statModelKill.kills.Insert(kill);
        statModelKill.timeSurvived = killer.StatGet("playtime");
		
		Save(statModelKill, killerId);
    }	   

    PlayerStatsModel Load(string steamID) {
        PlayerStatsModel statModelLoad = new PlayerStatsModel;
        string FileLocation = basePath + steamID + ".json";

        if (FileExist(FileLocation)) {
            JsonFileLoader<PlayerStatsModel>.JsonLoadFile(FileLocation, statModelLoad);
        }
        else {
            JsonFileLoader<PlayerStatsModel>.JsonSaveFile(FileLocation, statModelLoad);
        }
        return statModelLoad;
    }

    void Save(PlayerStatsModel statModelSave, string steamID) {
        string FileLocation = basePath + steamID + ".json";
        JsonFileLoader<PlayerStatsModel>.JsonSaveFile(FileLocation, statModelSave);
    }
}