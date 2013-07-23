print("Initialization begins.")

register_key('w', '..\\game\\keys\\w_key.lua');
register_key('s', '..\\game\\keys\\s_key.lua');
register_key('a', '..\\game\\keys\\a_key.lua');
register_key('d', '..\\game\\keys\\d_key.lua');
--register_key('z', '..\\game\\keys\\z_key.lua');
--register_key('x', '..\\game\\keys\\x_key.lua');
--register_key('c', '..\\game\\keys\\c_key.lua');
--register_key('v', '..\\game\\keys\\v_key.lua');
--register_key(' ', '..\\game\\keys\\space_key.lua');

gom = GameObjectManager.GetInstance();
cm = ComponentManager.GetInstance();
rm = ResourceManager.GetInstance();

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
