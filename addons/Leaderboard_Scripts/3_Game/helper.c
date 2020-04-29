class Helper {
    static string GetCurrentTime() {
		int year, month, day, hour, minute, second;
        GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		string timeStamp = year.ToString()+"-"+month.ToString()+"-"+day.ToString()+" "+hour.ToString()+":"+minute.ToString()+":"+second.ToString();
        return timeStamp;	
    }
	
	static EntityAI GetWeaponInHands(Man sb) {
        HumanInventory inventory = HumanInventory.Cast(sb.GetInventory());
		EntityAI weapon = inventory.GetEntityInHands();
		return weapon;
	}
	
	static string ConvertVectorPosToString(vector pos) {
		return pos[0].ToString() +","+pos[1].ToString()+","+pos[2].ToString();
	}
}