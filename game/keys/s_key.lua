gom = GameObjectManager.GetInstance();
player = gom:GetObject("Human1", "Player");

if key_pressed('a') == false and key_pressed('d') == false then
	player.movement:SetState("Walk_Down");
elseif key_pressed('a') == true then
	player.movement:SetState("Walk_Down_Left");
elseif key_pressed('d') == true then
	player.movement:SetState("Walk_Down_Right");
end
