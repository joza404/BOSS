print("Initialization begins.")

input = Input.GetInstance();
gom = GameObjectManager.GetInstance();
cm = ComponentManager.GetInstance();
rm = ResourceManager.GetInstance();

W_Key = {}
W_Key["Press"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if string.find(currentState, "Idle") ~= nil then
		player.movement:SetState("Walk_Up");
	elseif currentState == "Walk_Left" then
		player.movement:SetState("Walk_Up_Left");
	elseif currentState == "Walk_Right" then
		player.movement:SetState("Walk_Up_Right");
	elseif currentState == "Walk_Down" then
		player.movement:SetState("Walk_Up");
	end
end

W_Key["Repeat"] = function()
end

W_Key["Release"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState =  player.movement:GetState();
	if currentState == "Walk_Up" then
		player.movement:SetState("Idle_Up");
	elseif currentState == "Walk_Up_Right" then
		if input:KeyPressed('d') == true then
			player.movement:SetState("Walk_Right");
		else 
			player.movement:SetState("Idle_Up_Right");
		end
	elseif currentState == "Walk_Up_Left" then
		if input:KeyPressed('a') == true then
			player.movement:SetState("Walk_Left");
		else
			player.movement:SetState("Idle_Up_Left");
		end
	end
end

S_Key = {}
S_Key["Press"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if string.find(currentState, "Idle") ~= nil then
		player.movement:SetState("Walk_Down");
	elseif currentState == "Walk_Left" then
		player.movement:SetState("Walk_Down_Left");
	elseif currentState == "Walk_Right" then
		player.movement:SetState("Walk_Down_Right");
	elseif currentState == "Walk_Up" then
		player.movement:SetState("Walk_Down");
	end 
end

S_Key["Repeat"] = function()
end

S_Key["Release"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if currentState == "Walk_Down" then
		player.movement:SetState("Idle_Down");
	elseif currentState == "Walk_Down_Right" then
		if input:KeyPressed('d') == true then
			player.movement:SetState("Walk_Right");
		else
			player.movement:SetState("Idle_Down_Right");
		end
	elseif currentState == "Walk_Down_Left" then
		if input:KeyPressed('a') == true then
			player.movement:SetState("Walk_Left");
		else
			player.movement:SetState("Idle_Down_Left");
		end
	end
end

A_Key = {}
A_Key["Press"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if string.find(currentState, "Idle") ~= nil then
		player.movement:SetState("Walk_Left");
	elseif currentState == "Walk_Up" then
		player.movement:SetState("Walk_Up_Left");
	elseif currentState == "Walk_Down" then
		player.movement:SetState("Walk_Down_Left");
	elseif currentState == "Walk_Right" then
		player.movement:SetState("Walk_Left");
	end 
end

A_Key["Repeat"] = function()
end

A_Key["Release"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if currentState == "Walk_Left" then
		player.movement:SetState("Idle_Left");
	elseif currentState == "Walk_Up_Left" then
		if input:KeyPressed('w') == true then
			player.movement:SetState("Walk_Up");
		else
			player.movement:SetState("Idle_Up_Left");
		end
	elseif currentState == "Walk_Down_Left" then
		if input:KeyPressed('s') == true then
			player.movement:SetState("Walk_Down");
		else
			player.movement:SetState("Idle_Down_Left");
		end
	end
end

D_Key = {}
D_Key["Press"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if string.find(currentState, "Idle") ~= nil then
		player.movement:SetState("Walk_Right");
	elseif currentState == "Walk_Up" then
		player.movement:SetState("Walk_Up_Right");
	elseif currentState == "Walk_Down" then
		player.movement:SetState("Walk_Down_Right");
	elseif currentState == "Walk_Left" then
		player.movement:SetState("Walk_Right");
	end 
end

D_Key["Repeat"] = function()
end

D_Key["Release"] = function()
	player = gom:GetObject("Human1", "Player");
	currentState = player.movement:GetState();
	if currentState == "Walk_Right" then
		player.movement:SetState("Idle_Right");
	elseif currentState == "Walk_Up_Right" then
		if input:KeyPressed('w') == true then
			player.movement:SetState("Walk_Up");
		else
			player.movement:SetState("Idle_Up_Right");
		end
	elseif currentState == "Walk_Down_Right" then
		if input:KeyPressed('s') == true then
			player.movement:SetState("Walk_Down");
		else
			player.movement:SetState("Idle_Down_Right");
		end
	end
end

input:SetUpdateFrequency(3);
input:RegisterKey('w', W_Key, 10000);
input:RegisterKey('s', S_Key, 10000);
input:RegisterKey('a', A_Key, 10000);
input:RegisterKey('d', D_Key, 10000);
 
--the space image
rm:LoadImageResource("Resource_Space", "..\\game\\Space\\Space.info");

--load the human1 animation
rm:LoadAnimationResource("Resource_Human1_Idle_Up", "..\\game\\Human1\\Idle_Up.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Up_Left", "..\\game\\Human1\\Idle_Up_Left.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Up_Right", "..\\game\\Human1\\Idle_Up_Right.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Left", "..\\game\\Human1\\Idle_Left.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Right", "..\\game\\Human1\\Idle_Right.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Down_Left", "..\\game\\Human1\\Idle_Down_Left.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Down_Right", "..\\game\\Human1\\Idle_Down_Right.info");
rm:LoadAnimationResource("Resource_Human1_Idle_Down", "..\\game\\Human1\\Idle_Down.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Up", "..\\game\\Human1\\Walk_Up.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Up_Left", "..\\game\\Human1\\Walk_Up_Left.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Up_Right", "..\\game\\Human1\\Walk_Up_Right.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Left", "..\\game\\Human1\\Walk_Left.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Right", "..\\game\\Human1\\Walk_Right.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Down_Left", "..\\game\\Human1\\Walk_Down_Left.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Down_Right", "..\\game\\Human1\\Walk_Down_Right.info");
rm:LoadAnimationResource("Resource_Human1_Walk_Down", "..\\game\\Human1\\Walk_Down.info");

Human1 = {}
Human1["Initialize"] = function(go)
	go.position = cm:CreatePositionComponent("Position_" .. go.typeName .. go.objectName);
	go.position:SetX( math.random(10, 400) ); 
	go.position:SetY( math.random(10, 400) ); 

	go.animation = cm:CreateAnimationComponent("Animation_" .. go.typeName .. go.objectName);
	go.animation:SetPosition(go.position);
	go.animation:AddState("Walk_Up", "Resource_Human1_Walk_Up");
	go.animation:AddState("Walk_Up_Left", "Resource_Human1_Walk_Up_Left");
	go.animation:AddState("Walk_Up_Right", "Resource_Human1_Walk_Up_Right");
	go.animation:AddState("Walk_Left", "Resource_Human1_Walk_Left");
	go.animation:AddState("Walk_Right", "Resource_Human1_Walk_Right");
	go.animation:AddState("Walk_Down_Left", "Resource_Human1_Walk_Down_Left");
	go.animation:AddState("Walk_Down_Right", "Resource_Human1_Walk_Down_Right");
	go.animation:AddState("Walk_Down", "Resource_Human1_Walk_Down");
	go.animation:AddState("Idle_Up", "Resource_Human1_Idle_Up");
	go.animation:AddState("Idle_Up_Left", "Resource_Human1_Idle_Up_Left");
	go.animation:AddState("Idle_Up_Right", "Resource_Human1_Idle_Up_Right");
	go.animation:AddState("Idle_Left", "Resource_Human1_Idle_Left");
	go.animation:AddState("Idle_Right", "Resource_Human1_Idle_Right");
	go.animation:AddState("Idle_Down_Left", "Resource_Human1_Idle_Down_Left");
	go.animation:AddState("Idle_Down_Right", "Resource_Human1_Idle_Down_Right");
	go.animation:AddState("Idle_Down", "Resource_Human1_Idle_Down");
	go.animation:SetSpeed(6);

	go.movement = cm:CreateMovementComponent("Movement_" .. go.typeName .. go.objectName);
	go.movement:SetPosition(go.position);
	go.movement:SetAnimation(go.animation);
	go.movement:AddState("Walk_Up", 0, -1);
	go.movement:AddState("Walk_Up_Left", -1, -1);
	go.movement:AddState("Walk_Up_Right", 1, -1);
	go.movement:AddState("Walk_Left", -1, 0);
	go.movement:AddState("Walk_Right", 1, 0);
	go.movement:AddState("Walk_Down_Left", -1, 1);
	go.movement:AddState("Walk_Down_Right", 1, 1);
	go.movement:AddState("Walk_Down", 0, 1);
	go.movement:AddState("Idle_Up", 0, 0);
	go.movement:AddState("Idle_Up_Left", 0, 0);
	go.movement:AddState("Idle_Up_Right", 0, 0);
	go.movement:AddState("Idle_Left", 0, 0);
	go.movement:AddState("Idle_Right", 0, 0);
	go.movement:AddState("Idle_Down_Left", 0, 0);
	go.movement:AddState("Idle_Down_Right", 0, 0);
	go.movement:AddState("Idle_Down", 0, 0);
	go.movement:BindAnimationState("Walk_Up", "Walk_Up");
	go.movement:BindAnimationState("Walk_Up_Left", "Walk_Up_Left");
	go.movement:BindAnimationState("Walk_Up_Right", "Walk_Up_Right");
	go.movement:BindAnimationState("Walk_Left", "Walk_Left");
	go.movement:BindAnimationState("Walk_Right", "Walk_Right");
	go.movement:BindAnimationState("Walk_Down_Left", "Walk_Down_Left");
	go.movement:BindAnimationState("Walk_Down_Right", "Walk_Down_Right");
	go.movement:BindAnimationState("Walk_Down", "Walk_Down");
	go.movement:BindAnimationState("Idle_Up", "Idle_Up");
	go.movement:BindAnimationState("Idle_Up_Left", "Idle_Up_Left");
	go.movement:BindAnimationState("Idle_Up_Right", "Idle_Up_Right");
	go.movement:BindAnimationState("Idle_Left", "Idle_Left");
	go.movement:BindAnimationState("Idle_Right", "Idle_Right");
	go.movement:BindAnimationState("Idle_Down_Left", "Idle_Down_Left");
	go.movement:BindAnimationState("Idle_Down_Right", "Idle_Down_Right");
	go.movement:BindAnimationState("Idle_Down", "Idle_Down");
	go.movement:SetState("Idle_Down");
end

Human1["Release"] = function(go)
	cm:DestroyAnimationComponent(go.animation);
	cm:DestroyPositionComponent(go.position);
	cm:DestroyMovementComponent(go.movement);
end

gom:CreateObjectType("Human1", Human1);

--create the background
background = cm:CreateImageComponent("Background");
background:SetResource("Resource_Space");

gom:CreateObject("Human1", "Player");


print("Initialization has completed.")
