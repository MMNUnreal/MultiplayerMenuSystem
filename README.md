# MultiplayerMenuSystem
A multiplayer menu system using unreal online subsystem. <br/>
It relies on the source in the menusystem folder, with calls such as hosting, joining, loading menu, loading ingame menu called through the game instance to the menu interface (if necessary).
<br/>
<br/>
There are a couple of test gameplay objects in the game map (third person player map); Platform trigger and Platform cube. When the player overlaps the trigger, it activates its corresponding cube (set in BP). When total number of triggers are activated, the cubes will move.
