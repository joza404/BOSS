if key_pressed('a') == false and key_pressed('d') == false then
	print('W');
end

cm = ComponentManager.GetInstance();
boy_pos = cm:GetPositionComponent("boy_pos");
boy_pos:SetY(boy_pos:GetY() - 2);