--[[
	File:Dungeon.lua
	Author(s): Gabriel Islas and Ryan Turner
--]]

function main()
	io.write(" -- DUNGEONS AND/OR DRAGONS --\n");
	io.write("-Developed by: Mudball Games-\n");
	io.write("Programmers:Ryan Turner and Gabriel Islas\n\n");
	
	Intro(); 
	
	-- declare variables and seed RNG
	level = 1;
	playerExp = 0;
	playerClass = "";
	magLevel = 0;
	potions = 2;
	ethers = 2;
	enemy = {};
	magArray = {"Flame", "Freeze", "Bolt"};
	elfMagArray = {"Incinerate", "Embrace", "Summon"};
	harveyArray = {"Reject Reality", "True Statement"};
	math.randomseed(os.time());
	math.random();
	
	-- player chooses character class and receives stats
	io.write("Choose your class: WARRIOR, MAGE, ELVEN MAIDEN, FIGHTER or PIRATE. ");
	io.flush();
	selection = io.read("*l");
	while (selection ~= "OK") do
		if (selection == "WARRIOR") then
			playerHPMax = 50;
			playerMPMax = 10;
			playerAtk = 20;
			playerMag = 5;
			playerDef = 15;
			playerSkl = 10;
		end
		if (selection == "ELVEN MAIDEN") then 
			playerHPMax = 30;
			playerMPMax = 100;
			playerAtk = 5;
			playerMag = 25;
			playerDef = 10;
			playerSkl = 15;
			magLevel = 1;
		end 
		if (selection == "FIGHTER") then 
			playerHPMax = 50;
			playerMPMax = 10;
			playerAtk = 25;
			playerMag = 5;
			playerDef = 15;
			playerSkl = 15;
		end 
		if (selection == "MAGE") then
			playerHPMax = 50;
			playerMPMax = 50;
			playerAtk = 5;
			playerMag = 20;
			playerDef = 5;
			playerSkl = 5;
			magLevel = 1;
		end
		if (selection == "PIRATE") then
			playerHPMax = 30;
			playerMPMax = 0;
			playerAtk = 15;
			playerMag = 0;
			playerDef = 10;
			playerSkl = 20;
		end
		io.write("\nLevel 1 ", selection, " Stat spread:\nMax HP: ", playerHPMax, "\nMax MP: ", playerMPMax, "\nAttack: ", playerAtk, "\nMagic: ", playerMag, "\nDefense: ", playerDef, "\nSkill: ", playerSkl, '\n');
		io.write("To change classes, enter your new class. To keep this class, enter OK: ");
		io.flush();
		playerClass = selection;
		selection = io.read("*l");
	end
	playerHP = playerHPMax;
	playerMP = playerMPMax;
	playerNext = 100;
	player = {level, playerClass, playerHP, playerHPMax, playerMP, playerMPMax, playerAtk, playerMag, playerDef, playerSkl, playerExp, playerNext};
	io.write("\n");
	-- display player's stats and inventory
	DispStats();
	DispInv();
	
	-- while the player has health
	while (player[3] > 0) do
	
		-- generate enemy
		enemy = SelectEnemy();
		io.write(enemy[2], " attacks!\n\n");
		
		---- BATTLE ENEMY --
		while (enemy[3] > 0 and player[3] > 0) do
			-- HP Critical notification
			if (player[3] <= player[4]/4) then
				io.write("WARNING! HP LOW!\n");
			end
			
			-- ask player for action
			action = "";
			turn = true;
			while (action ~= "ATTACK" and action ~= "MAGIC" and action ~= "ITEMS" and turn == true) do
				io.write("ATTACK, MAGIC, or ITEMS? \n");
				io.write("(Type STATS for current stats)");
				io.flush();
				action = io.read("*l");
				if (action == "STATS") then
					DispStats(player);
				end
				if (action == "INV") then
					DispInv();
				end
				if (action == "ATTACK") or (action == "Attack") or (action == "attack") then
					io.write("You attack!\n");
					damage = PhysAttack(player,enemy);
					io.write("You inflict ", damage, " damage!\n\n");
					enemy[3] = enemy[3] - damage;
					turn = false;
					break;
				end
				if (action == "MAGIC") or (action == "Magic") or (action == "magic") then
					DispMag();
					action = "";
					while (action ~= "BACK") do
						if magLevel == 0 then
							break;
						end
						io.write("Use which spell? ");
						io.flush();
						action = io.read("*l");
						if action == "BACK" then
							break;
						end
						spell = Spell(action);
						if player[5] < spell[3] then
							io.write("Not enough MP.\n");
							break;
						else
							io.write("You cast ", spell[1], "!\n");
							damage = MagAttack(player,enemy,spell);
							io.write("You inflict ", damage, " damage!\n\n");
							enemy[3] = enemy[3] - damage;
							player[5] = player[5] - spell[3];
							-- player's magLevel increases
							magLevel = magLevel + .1;
							turn = false;
						end
						
						break;
					end
				end
				if (action == "ITEMS") or (action == "Items") or (action == "items") then
					DispInv();
					action = "";
					while (action ~= "BACK") do
						io.write("Use which item? ");
						io.flush();
						action = io.read("*l");
						-- use a Potion
						if (action == "POTION") or (action == "Potion") or (action == "potion") then
							if potions > 0 then
								UsePotion();
								action = "BACK";
							else
								io.write("You don't have any Potions...\n");
								action = "BACK";
							end
						end
						-- use an Ether
						if (action == "ETHER") or (action == "Ether") or (action == "ether") then
							if ethers > 0 then
								UseEther();
								action = "BACK";
							else
								io.write("You don't have any Ethers...\n");
								action = "BACK";
							end
						end
					end
					break;
				end
				
			end
			
			-- determine enemy action
			if (enemy[3] > 0) then
				if enemy[5] > 0 then
					action = math.random(3);
				else
					action = 1;
				end
				if action == 1 or action == 2 then
					io.write(enemy[2], " attacks!\n");
					damage = PhysAttack(enemy,player);
					io.write("You sustain ", damage, " damage!\n\n");
					player[3] = player[3] - damage;
				else
					while true do
						-- choose magic attack
						action = math.random(enemyMag);
						spell = Spell(action);
						if spell[3] <= enemy[5] then
							break;
						end
					end
					-- magic attack text
					io.write(enemy[2], " casts ", spell[1], "!\n");
					damage = MagAttack(enemy,player,spell);
					io.write("You sustain ", damage, " damage!\n\n");
					player[3] = player[3] - damage;
				end
			end
			
			
		end
		
		-- if enemy is defeated, add EXP and reward
		if (enemy[3] <= 0) then
			io.write(enemy[2], " defeated!\nYou obtain:\n")
			io.write(enemy[11], " EXP points\n");
			player[11] = player[11] + enemy[11];
			-- Level up if player has enough EXP
			if (player[11] >= player[12]) then
				player = LevelUp();
			end
			io.write("Total EXP: ", player[11], '/', player[12], '\n');
			-- award items
			io.write("Found items: \n");
			if (enemy[12] == 1) then
				io.write("1 Potion\n");
				potions = potions+1;
			end
			if (enemy[12] == 2) then
				io.write("1 Ether\n");
				ethers = ethers+1;
			end
			if (enemy[12] == 3) then
				io.write("1 Potion\n1 Ether\n");
				potions = potions+1;
				ethers = ethers+1;
			end
			if (enemy[12] == 4) then
				io.write("2 Potions\n")
				potions = potions+2;
			end
			if (enemy[12] == 5) then
				io.write("2 Potions\n1 Ether\n")
				potions = potions+2;
				ethers = ethers+1;
			end
			
			io.write('\n');
		end
		
	end
	io.write("== Game Over ==\n");
end

-- display player's stats
function DispStats()
	io.write("Level ", player[1], " ", player[2], '\n');
	io.write("HP: ", player[3], "/", player[4], "\nMP: ", player[5], "/", player[6], "\nAttack: ", player[7], "\nMagic: ", player[8], "\nDefense: ", player[9], "\nSkill: ", player[10], "\n");
	io.write("EXP: ", player[11], "/", player[12], "\n\n");
end

-- display player's inventory
function DispInv()
	io.write("ITEMS:\n");
	io.write("Potions: ", potions, '\n');
	io.write("Ethers: ", ethers, "\n\n");
end

-- display player's known spells
function DispMag()
	if magLevel == 0 then
		io.write("You don't know any magic.\n");
	elseif playerClass == "MAGE" then 
		io.write("KNOWN SPELLS\n");
		for i = 1, math.floor(magLevel), 1 do
			spell = Spell(i);
			io.write(magArray[i], " -", spell[2], "MP\n");
			
		end
	else 
		io.write("KNOWN SPELLS\n"); 
		for i = 1, math.floor(magLevel), 1 do 
			spell = Spell(i);
			io.write(elfMagArray[i], " -", spell[2], "MP\n");
		end 
	end 
	io.write('\n');
end

-- generate enemy depending on player's level
function SelectEnemy()
	level = player[1];
	enemyMag = 0;
	if (level <= 3) then
		class = math.random(5)
		if (class == 1) then
			class = "WOLF"
			HP = 20;
			MP = 0;
			Atk = 15;
			Mag = 0;
			Def = 5;
			Skl = 3;
			Exp = 20;
			Rwrd = 1;
		end
		if (class == 2) then
			class = "SNAKE";
			HP = 15;
			MP = 0;
			Atk= 20;
			Mag = 0;
			Def = 10;
			Skl = 5;
			Exp = 30;
			Rwrd = 1;
		end
		if (class == 3) then
			class = "REVENANT"
			HP = 25;
			MP = 0;
			Atk = 22;
			Mag = 0;
			Def = 8;
			Skl = 5;
			Exp = 25;
			Rwrd = 1;
		end
		if (class == 4) then
			class = "MIST"
			HP = 15;
			MP = 35;
			Atk = 10;
			Mag = 15;
			Def = 10;
			Skl = 5;
			Exp = 30;
			Rwrd = 2;
			enemyMag = 2;
		end
		if (class == 5) then
			class = "LESSER DRAKE"
			HP = 30;
			MP = 20;
			Atk = 25;
			Mag = 12;
			Def = 10;
			Skl = 10;
			Exp = 50;
			Rwrd = 3;
			enemyMag = 1;
		end
	end
	if  (level > 3 and level <= 6) then
		class = math.random(6,10)
		if (class == 6) then
			class = "ANTLION";
			HP = 40;
			MP = 0;
			Atk = 26;
			Mag = 0;
			Def = 12;
			Skl = 26;
			Exp = 55;
			Rwrd = 1;
		end
		if (class == 7) then
			class = "COBRA";
			HP = 35;
			MP = 0;
			Atk = 28;
			Mag = 0;
			Def = 14;
			Skl = 30;
			Exp = 60;
			Rwrd = 3;
		end
		if (class == 8) then
			class = "CHIMERA";
			HP = 40;
			MP = 20;
			Atk = 25;
			Mag = 15;
			Def = 17;
			Skl = 15;
			Exp = 35;
			Rwrd = 4;
			enemyMag = 1;
		end
		if (class == 9) then
			class = "WRAITH";
			HP = 35;
			MP = 60;
			Atk = 20;
			Mag = 35;
			Def = 16;
			Skl = 16;
			Exp = 40;
			Rwrd = 5;
			enemyMag = 3;
		end
		if (class == 10) then
			class = "GREATER DRAKE";
			HP = 50;
			MP = 50;
			Atk = 30;
			Mag = 15;
			Def = 20;
			Skl = 30;
			Exp = 50;
			Rwrd = 5;
			enemyMag = 3;
		end
	end
	if (level > 10) then
		class = 11;
		if (class == 11) then 
			class = "HARVEY";
			HP = 1000;
			MP = 300;
			Atk = 50
			Mag = 20; 
			Def = 25;
			Skl = 35;
			Exp = 200;
			Rwrd = 5;
			bossMag = 2;
		end
	end 
	MaxHP = HP;
	MaxMP = MP;
	return {level, class, HP, MaxHP, MP, MaxMP, Atk, Mag, Def, Skl, Exp, Rwrd};
end

-- calculate physical damage
function PhysAttack(attacker,defender)
	attack = attacker[7];
	defend = defender[9];
	atkSkl = attacker[10];
	defSkl = defender[10];
	-- normal damage calculation
	damage = (attack - defend) + math.random(-2,2);
	-- calculate Critical Points (half attacker's skill minus defender's skill = 1 CP)
	CP = (math.floor(atkSkl/2)) - defSkl;
	if (CP < 0) then
		CP = 0;
	end
	io.write("Critical roll: ", CP, "d6\n");
	-- roll 1d6 per CP
	crit = 0;
	for i = 1, CP, 1 do
		crit = crit + math.random(6);
	end
	-- if <CP>d6 roll exceeds double defender's skill, critical is scored
	if (crit > 2*defSkl) then
		dmgMult = 0;
		io.write("CRITICAL HIT!\n");
		io.write("Critical modifier: ");
		-- for every 10 points above crit sum, damage is increased
		for i = 2*defSkl-9, crit, 10 do
			dmgMult = dmgMult + 1;
		end
		io.write(dmgMult, "x\n");
		damage = damage * dmgMult;
	end
	-- prevent negative damage
	if (damage < 0) then
		damage = 0;
	end
	return damage;
end

-- return spell name, damage, and MP cost
function Spell(spell)
	if spell == "FLAME" or spell == 1 then
		name = "FLAME";
		damage = 10;
		cost = 10;
	end
	if spell == "FREEZE" or spell == 2 then
		name = "FREEZE";
		damage = 25;
		cost = 25;
	end
	if spell == "BOLT" or spell == 3 then
		name = "BOLT";
		damage = 40;
		cost = 40;
	end
	
	return {name, damage, cost};
end

-- calculate magical damage
function MagAttack(attacker,defender,spell)
	magAtk = attacker[8];
	magDef = defender[8];
	-- calculate damage
	damage = (spell[2] + magAtk) - magDef;
	
	return damage;
end

-- use Potion
function UsePotion()
	recover = 50;
	if ((player[3] + recover) > player[4]) then
		recover = player[4] - player[3];
	end
	player[3] = player[3] + recover;
	potions = potions - 1;
	io.write("You used a Potion and recovered ", recover, " HP!\n\n");
end

-- use Ether
function UseEther()
	recover = 50;
	if ((player[5] + recover) > player[6]) then
		recover = player[6] - player[5];
	end
	player[5] = player[5] + recover;
	ethers = ethers - 1;
	io.write("You used an Ether and recovered ", recover, " MP!\n\n");
end

-- Level Up
function LevelUp()
	-- declare data
	level = player[1];
	class = player[2];
	HP = player[3];
	MaxHP = player[4];
	MP = player[5];
	MaxMP = player[6];
	atk = player[7];
	mag = player[8];
	def = player[9];
	skl = player[10];
	Exp = player[11];
	Next = player[12];
	gain = 0;
	
	-- if EXP exceeds amount needed for next level, modify stats
	level = level + 1;
	io.write("LEVEL UP!\n");
	io.write("Level: ", level, '\n');
	HP = HP + 10;
	MaxHP = MaxHP + 10;
	io.write("HP: +10\n");
	MP = MP + 5;
	MaxMP = MaxMP + 5;
	io.write("MP: +5\n");
	gain = math.random(3);
	atk = atk + gain;
	io.write("Attack: +", gain, '\n');
	gain = math.random(3);
	mag = mag + gain;
	io.write("Magic: +", gain, '\n');
	gain = math.random(3);
	def = def + gain;
	io.write("Defense: +", gain, '\n');
	gain = math.random(3);
	skl = skl + gain;
	io.write("Skill: +", gain, '\n');
	
	-- calculate new Next value
	Next = Next + 100 + 20*player[1];
	
	-- return new array
	return {level, class, HP, MaxHP, MP, MaxMP, atk, mag, def, skl, Exp, Next};
end

--Other functions (Added by Gabriel Islas) 
function Intro() 
	--Initialize a local variable
	local add = 0; 

	while true do	
		add = add + 1; 
		if add > 400 then 
			break;
		end 
	end 
	
	if add > 100 then 
		io.write( "You awake in shackles..."); 
		io.write( "\n");
	end 
	
	if add > 200 then 
		io.write( "You are in Harvey's infamous dungeon... \n");
		io.write( "In the distance, you hear a helpless victim screaming. \n"); 
		io.write("\n"); 
	end 
	
	if add > 300 then 
		io.write( "You break free, and find your weapon of choice...\n");
		io.write( "What is it....? \n"); 
		io.write( "\n"); 
	end 
	
end 