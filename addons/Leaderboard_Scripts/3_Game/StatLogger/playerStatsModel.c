class PlayerStatsModel {

    void PlayerStatsModel() {
        deaths = new array<DeathStatsModel>;
        kills = new array<KillStatsModel>;
		animalsKilled = new array<string>;
    }

	ref array<DeathStatsModel> deaths;
	ref array<KillStatsModel> kills;
	ref array<string> animalsKilled;
	string name;
	int deathsToZCount;
	int deathsToNaturalCauseCount;
	int deathsToPlayerCount;
	int deathsToAnimalCount;
	int suicideCount;
	int longestShot;
	int zKilled;
	int timeSurvived;
	int distTrav;
}

class DeathStatsModel {	

	void DeathStatsModel() {
		animalsKilled = new array<string>;
		kills = new array<KillStatsModel>;
	}
	ref array<string> animalsKilled;
	ref array<KillStatsModel> kills;
	int longestShot;
	int timeSurvived;
	int zKillCount;
	int distTrav;
	string timeStamp;
	string posDeath;
    string killer;
	string weapon;
}

class KillStatsModel {

	void KillStatsModel() {
		victim = new Victim;
	}
    ref Victim victim;
	string timeStamp;
	string posKill;
	string weapon;
	float distance;
}

class Victim {
	string id;
	int timeSurvived;
}