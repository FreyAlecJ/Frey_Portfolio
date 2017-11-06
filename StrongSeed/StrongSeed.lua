--[[
	Main file for Strong Seed wow addon
]]--
local _, core = ...;

SLASH_RELOADUI1 = "/rl"; -- new slash command for reloading UI
SlashCmdList.RELOADUI = ReloadUI;

function core:DisplayMessage(event, name)
	local name, _, _, _, _, duration, expiration, _, _, _ = UnitAura("player", "Nightfall");
	local MsgFrame = CreateFrame("MessageFrame", nil, UIParent);
	local remaining = math.floor(expiration - GetTime());
	if (remaining == 10) then MsgFrame:clear(); end;
	MsgFrame:SetPoint("CENTER",UIParent,"CENTER",0,150);
	MsgFrame:SetSize(1000,70);
	MsgFrame:SetFontObject("GameFontNormalLarge");
	MsgFrame:SetTimeVisible(1);
	MsgFrame:SetFadeDuration(0);
	MsgFrame:AddMessage("The seed is strong friend!", 0.53, 0.21, 0.60, 1);
	MsgFrame:Show();
end

-- Register the event
local events = CreateFrame("Frame");
events:RegisterEvent("UNIT_AURA");
events:SetScript("OnEvent", core.DisplayMessage);
