class Helper {
    static string GetCurrentTime() {
		int year, month, day, hour, minute, second;
        GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		string timeStamp = year.ToString()+":"+month.ToString()+":"+day.ToString()+":"+hour.ToString()+":"+minute.ToString()+":"+second.ToString();
        return timeStamp;	
    }
	
	static string GetWeaponInHands(SurvivorBase sb) {
		DayZPlayerInventory playerInv = sb.GetInventory();
        EntityAI handEntity = playerInv.GetEntityInHands();
		return handEntity.GetType();
	}
	
	static string ConvertVectorPosToString(vector pos) {
		return pos[0].ToString() +","+pos[1].ToString()+","+pos[2].ToString();
	}
}