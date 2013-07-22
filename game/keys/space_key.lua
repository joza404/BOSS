print('SPACE');

cm = ComponentManager.GetInstance();
boy = cm:GetAnimationComponent("boy");

if boy:GetState() == "boy_up" then
	boy:SetState("boy_down")
else
	boy:SetState("boy_up")
end
