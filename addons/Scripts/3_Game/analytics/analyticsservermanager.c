modded class AnalyticsManagerServer {
    ref GameStatLogger statLogger = new GameStatLogger;
    
    override void OnEntityKilled( Object killer, EntityAI target ) {
		EntityAI killer_entity = EntityAI.Cast( killer );
		if ( killer_entity )
		{
			Man killer_survivor = killer_entity.GetHierarchyRootPlayer();
			if ( killer_survivor )
			{
				if ( target.IsPlayer() )
				{
					OnPlayerKilled( killer_survivor, target );
				}
				else if ( target.IsZombie() )
				{
					OnInfectedKilled( killer_survivor, target );
				}
                else if ( target.IsAnimal() && GetGame().IsServer())
                {
                    statLogger.onAnimalKilled(killer_survivor, target);
                }
			}
		}
    }
}