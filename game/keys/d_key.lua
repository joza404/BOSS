if key_pressed('w') == true then
do
	print('D+W');
end elseif key_pressed('s') == true then
do
	print('D+S');
end else
	print('D');
end

cm = ComponentManager.GetInstance();
boy_pos = cm:GetPositionComponent("boy_pos");
boy_pos:SetX(boy_pos:GetX() + 2);