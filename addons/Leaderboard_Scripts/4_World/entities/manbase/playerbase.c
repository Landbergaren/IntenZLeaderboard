modded class PlayerBase 
{
    ref StatLogger statLogger;
    private string PlayerID = "empty";
    private string PlayerFullName = "empty";

    string GetPlayerID()
    {
        return PlayerID;
    }

    void SetPlayerID(string IdentityID)
    {
        PlayerID = IdentityID;
    }

    string GetPlayerFullName() 
    {    
        return PlayerFullName;
    }
         
    void SetPlayerFullName(string name) 
    {
        PlayerFullName = name;
    }
    
    override void OnConnect() {
        super.OnConnect();

        this.SetPlayerID(this.GetIdentity().GetPlainId());
        this.SetPlayerFullName(this.GetIdentity().GetName());

        statLogger = new StatLogger;
        statLogger.OnConnectHandler(this.GetPlayerID(), this.GetPlayerFullName());
    }

    override void OnDisconnect() {
        super.OnDisconnect();
		ref SurvivorBase sbPlayer = SurvivorBase.Cast(this);
		statLogger.OnDisconnectHandler(sbPlayer);
    }

    override void EEKilled(Object killer) {
        super.EEKilled(killer);

        if (GetGame().IsServer()) {
            statLogger.DeathHandler(this, killer);
        }
        // ref SurvivorBase sbKilled = SurvivorBase.Cast(this);
		// ref EntityAI castedKiller = EntityAI.Cast(killer);
        // statLogger.DeathHandler(sbKilled, castedKiller);
    }
}