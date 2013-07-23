gom = GameObjectManager.GetInstance();
player = gom:GetObject("Human1", "Player");

if key_pressed('w') == false and key_pressed('s') == false then
	player.movement:SetState("Walk_Right");
end