modded class PlayerBase 
{
    int kills = 0;
    ref StatLogger statLogger;
    
    override void OnConnect(){
        super.OnConnect();

        ref SurvivorBase sbConnecting = SurvivorBase.Cast(this);
        sbConnecting.SetPlayerID(this.GetIdentity().GetPlainId());
        sbConnecting.SetPlayerFullName(this.GetIdentity().GetName());

        statLogger = new StatLogger;
        statLogger.OnConnectHandler(sbConnecting.GetPlayerID(), sbConnecting.GetPlayerFullName());
    }

    override void OnDisconnect(){
        super.OnDisconnect();
		ref SurvivorBase sbPlayer = SurvivorBase.Cast(this);
        int longestShot = StatGet("longest_survivor_hit");
        int zKilled = StatGet("infected_killed");
        int playTime = StatGet("playtime");
        int distTrav = StatGet("dist");
		statLogger.OnDisconnectHandler(sbPlayer.GetPlayerID(), longestShot, zKilled, playTime, distTrav);
    }

    override void EEKilled(Object killer) {
        ref SurvivorBase sbKilled = SurvivorBase.Cast(this);
		ref EntityAI castedKiller = EntityAI.Cast(killer);
		if (castedKiller.IsPlayer()) {
			ref SurvivorBase sbKiller = SurvivorBase.Cast(castedKiller);			
			if (sbKiller.GetPlayerID() != sbKilled.GetPlayerID()) {			
				statLogger.KillHandler(sbKilled.GetPlayerID(), sbKiller, castedKiller.GetPosition());	
			}	
		}
        statLogger.DeathHandler(sbKilled, castedKiller, sbKilled.GetPosition());

        super.EEKilled(killer);
    }
}