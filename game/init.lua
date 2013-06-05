--register keys
--register_key('w', '..\\game\\keys\\w_key.lua');
--register_key('s', '..\\game\\keys\\s_key.lua');
--register_key('a', '..\\game\\keys\\a_key.lua');
--register_key('d', '..\\game\\keys\\d_key.lua');
--register_key(' ', '..\\game\\keys\\space_key.lua');

--load resources
Res = Resources.GetInstance()
resBoy1 = Res:LoadAnimation("..//game//images//standingboy.info", "boy_stay")
resBoy2 = Res:LoadAnimation("..//game//images//standingboy2.info", "boy_reversed_stay")
Res:LoadImage("..//game//images//bg.info", "space")
Res:LoadFont("..//game//fonts//font1.info", "font1")


Comp = Components.GetInstance()
boy1 = Comp:CreateAnimation("boy")
boy1:AddState("boy_stay", "boy_stay")
boy1:AddState("boy_reversed_stay", "boy_reversed_stay")
boy1:SetState("boy_stay")

posBoy1 = Comp:CreatePosition("boy_position")
boy1:SetPosition(posBoy1);
posBoy1:SetY(20);
posBoy1:SetX(200);

print("Initialization has completed.")
