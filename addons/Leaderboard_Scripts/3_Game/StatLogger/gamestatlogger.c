class GameStatLogger {
    static string baseFolderLocation = "$profile:Leaderboard\\Stats-";
    ref PlayerStatsModel statModel = new PlayerStatsModel;

    void onAnimalKilled(Man killer, EntityAI target) {
            string killerId = killer.GetIdentity().GetPlainId();            
            statModel = Load(killerId);
            string animalType = target.GetType();
            statModel.animalsKilled.Insert(animalType);
            Save(statModel, killerId);
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