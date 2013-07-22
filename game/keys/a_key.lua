if key_pressed('w') == true then
do
	print('A+W');
end elseif key_pressed('s') == true then
do
	print('A+S');
end else
	print('A');
end

cm = ComponentManager.GetInstance();
boy_pos = cm:GetPositionComponent("boy_pos");
boy_pos:SetX(boy_pos:GetX() - 2);