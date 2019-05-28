class PlayerStatsModel {

    void PlayerStatsModel() {
        deaths = new array<DeathStatsModel>;
        kills = new array<KillStatsModel>;
    }

	ref array<DeathStatsModel> deaths;
	ref array<KillStatsModel> kills;
	string name;
	int deathsToZCount;
	int deathsToPlayerCount;
	int deathsToAnimalCount;
	int suicideCount;
	int longestShot;
	int zKilled;
	int playTime;
	int distTrav;
}

class DeathStatsModel {
	string timeStamp;
	string posDeath;
    string killer;
	string weapon;
}

class KillStatsModel {
	string timeStamp;
	string posKill;
    string victim;
	string weapon;
}