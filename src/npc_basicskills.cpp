/*
# NPC - Basic Subclass Skills #

### Description ###
------------------------------------------------------------------------------------------------------------------
- Adds NPCs that will teach all about basic Skills & Spells that are unavailable to the current Class.
- Part 2 of The SubClass Series Module.
- This module focus on Basic Skills (Fundamental Skills/Spells For Each Classes)
- Creating SubClasses like character(s).

### To-Do ###
------------------------------------------------------------------------------------------------------------------
- Add Intermediate Skills Proficiency NPC.
- Add Advanced Skills Proficiency NPC.
- Test & Tweak SubClasses Skills & Spells (Balancing).

### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: NPC
- Script: BasicSkills_NPC
- Config: Yes
- SQL: Yes
- NPC ID: 600002


### Updates ###
------------------------------------------------------------------------------------------------------------------
- Added Warnings/Restrictions when player do not meet the cost and level requirement.
- Added All of the Classes Basic Skills & Spells to the NPC.
- Added Exception For Players With The Learned Abilities/Skills.

*/

#include "Config.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

bool BasicSkillsAnnounceModule;
bool BasicSkillsEnableAI;

class BasicSkillsConfig : public WorldScript
{
public:
    BasicSkillsConfig() : WorldScript("BasicSkillsConfig_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            BasicSkillsAnnounceModule = sConfigMgr->GetOption<bool>("BasicSkillsNPC.Announce", 1);
            BasicSkillsEnableAI = sConfigMgr->GetOption<bool>("BasicSkillsNPC.EnableAI", 1);
        }
    }
};

class BasicSkillsAnnounce : public PlayerScript
{

public:

    BasicSkillsAnnounce() : PlayerScript("BasicSkillsAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (BasicSkillsAnnounceModule)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00BasicSkillsNPC |rmodule.");
        }
    }
};

class BasicSkills_NPC : public CreatureScript
{

public:

    BasicSkills_NPC() : CreatureScript("BasicSkills_NPC") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_warrior:40:40:-18|t Warrior's Basics [15 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_paladin:40:40:-18|t Paladin's Basics [15 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_hunter:40:40:-18|t Hunter's Basics [15 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_rogue:-18|t Rogue's Basics [15 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_priest:40:40:-18|t Priest's Basics [20 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\spell_deathknight_classicon:40:40:-18|t Death Knight's Basics [10 Golds]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_shaman:40:40:-18|t Shaman's Basics [20 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_mage:40:40:-18|t Mage's Basics [20 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_warlock:40:40:-18|t Warlock's Basics [20 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
        AddGossipItemFor(player, 10, "|TInterface\\icons\\classicon_druid:40:40:-18|t Druid's Basic [20 Silvers]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);

        SendGossipMenuFor(player, 600002, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /* creature */, uint32 sender, uint32 uiAction) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
            {
                if (player->HasSpell(78))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else if (player->HasSpell(11972))
                {   
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }                
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(1500))
                        {
                            // Learn Spells
                            player->learnSpell(11972);   // Shield Bash

                            player->learnSpell(51756);   // Charge 

                            player->learnSpell(32064);   // Battle Shout

                            player->learnSpell(25710);   // Heroic Strike

                            player->learnSpell(37548);   // Taunt

                            player->learnSpell(58567);   // Sunder Armor

                            player->learnSpell(38262);   // Hamstring

                            player->learnSpell(43246);   // Rend

                            // Cost
                            player->ModifyMoney(-1500);   // 15 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Warrior's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 2:
            {
                if (player->HasSpell(21084))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(1500))
                        {
                            // Learn Spells
                            player->learnSpell(21084);   // Seal of Righteousness

                            player->learnSpell(8258);   // Devotion Aura

                            player->learnSpell(853);   // Hammer of Justice

                            player->learnSpell(498);   // Divine Protection

                            player->learnSpell(635);   // Holy Light

                            player->learnSpell(19740);   // Blessing of Might

                            player->learnSpell(1152);   // Purify

                            player->learnSpell(1022);   // Hand of Protection

                            player->learnSpell(633);   // Lay on Hands

                            // Cost
                            player->ModifyMoney(-1500);   // 15 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Paladin's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 3:
            {
                if (player->HasSpell(75))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }           
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(1500))
                        {
                            // Learn Spells
                            player->learnSpell(75);   // Auto Shot

                            player->learnSpell(1130);   // Hunter's Mark

                            player->learnSpell(5116);   // Concussive Shot

                            player->learnSpell(13165);   // Aspect of the Hawk

                            player->learnSpell(38912);   // Hooked Net

                            player->learnSpell(3044);   // Arcane Shot

                            player->learnSpell(13163);   // Aspect of Monkey

                            player->learnSpell(1978);   // Serpent Sting

                            // Cost
                            player->ModifyMoney(-1500);   // 15 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Hunter's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 4:
            {
                if (player->HasSpell(1752))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else if (player->HasSpell(1804))
                {   
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }                
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(1500))
                        {
                            // Set Skills
                            player->SetSkill(633, 0, 1, 1);   // Lockpicking

                            // Learn Spells                        
                            player->learnSpell(1804);   // Pick Lock

                            player->learnSpell(921);   // Pick Pocket

                            player->learnSpell(1784);   // Stealth

                            player->learnSpell(2983);   // Sprint

                            player->learnSpell(5277);   // Evasion

                            player->learnSpell(1757);   // Sinister Strike

                            player->learnSpell(53);   // Backstab

                            player->learnSpell(1776);   // Gouge

                            player->learnSpell(30470);   // Slice and Dice

                            // Cost
                            player->ModifyMoney(-1500);   // 15 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Rogue's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 5:
            {
                if (player->HasSpell(2050))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }   
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(2000))
                        {
                            // Learn Spells
                            player->learnSpell(2050);   // Lesser Heal

                            player->learnSpell(585);   // Smite

                            player->learnSpell(17);   // Power Word: Shield

                            player->learnSpell(586);   // Fade

                            player->learnSpell(8092);   // Mind Blast

                            player->learnSpell(2006);   // Resurrection

                            // Cost
                            player->ModifyMoney(-2000);   // 20 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Priest's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;
        
        case GOSSIP_ACTION_INFO_DEF + 6:
            {
                if (player->HasSpell(49576))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(100000))
                        {
                            // Learn Spells
                            player->learnSpell(49576);   // Death Grip

                            player->learnSpell(66198);   // Obliterate

                            player->learnSpell(46584);   // Raise Dead

                            player->learnSpell(49410);   // Forceful Deflection

                            // Cost
                            player->ModifyMoney(-100000);   // 10 Golds

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Death Knight's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 7:
            {
                if (player->HasSpell(331))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }                
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(2000))
                        {
                            // Learn Spells
                            player->learnSpell(331);   // Healing Wave

                            player->learnSpell(8042);   // Earth Shock

                            player->learnSpell(324);   // Lightning Shield

                            player->learnSpell(8024);   // Flametongue Weapon

                            player->learnSpell(8050);   // Flame Shock

                            player->learnSpell(2825);   // Bloodlust

                            player->learnSpell(65861);  // Force of Nature

                            // Cost
                            player->ModifyMoney(-2000);   // 20 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Shaman's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 8:
            {
                if (player->HasSpell(133))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(2000))
                        {
                            // Learn Spells
                            player->learnSpell(133);   // Fireball

                            player->learnSpell(134);   // Fire Shield

                            player->learnSpell(116);   // Frostbolt

                            player->learnSpell(168);   // Frost Armor

                            player->learnSpell(5504);   // Conjure Water

                            player->learnSpell(587);   // Conjure Food

                            player->learnSpell(2136);   // Fire Blast

                            player->learnSpell(5143);   // Arcane Missiles

                            player->learnSpell(118);   // Polymorph

                            player->learnSpell(122);   // Frost Nova

                            // Cost
                            player->ModifyMoney(-2000);   // 20 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Mage's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 9:
            {
                if (player->HasSpell(686))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }            
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(2000))
                        {
                            // Learn Spells
                            player->learnSpell(686);   // Shadow Bolt

                            player->learnSpell(687);   // Demon Skin

                            player->learnSpell(348);   // Immolate

                            player->learnSpell(172);   // Corruption

                            player->learnSpell(702);   // Curse of Weakness

                            player->learnSpell(5782);   // Fear

                            player->learnSpell(980);   // Curse of Agony

                            player->learnSpell(1120);   // Drain Soul

                            player->learnSpell(697);   // Summon Voidwalker

                            // Cost
                            player->ModifyMoney(-2000);   // 20 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Warlock's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        case GOSSIP_ACTION_INFO_DEF + 10:
            {
                if (player->HasSpell(5176))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                    player->PlayerTalkClass->SendCloseGossip();
                }  
                else
                {
                    if (player->GetLevel() < 10)
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("Please come back when you have leveled up a bit more [Level 10]");
                        player->PlayerTalkClass->SendCloseGossip();
                    }
                    else if (player->GetLevel() >= 10)        
                    {            
                        if (player->HasEnoughMoney(2000))
                        {
                            // Learn Spells
                            player->learnSpell(5176);   // Wrath

                            player->learnSpell(5185);   // Healing Touch

                            player->learnSpell(1126);   // Mark of the Wild

                            player->learnSpell(8921);   // Moonfire

                            player->learnSpell(467);   // Thorns

                            player->learnSpell(339);   // Entangling Roots

                            player->learnSpell(5487);   // Bear Form

                            player->learnSpell(99);   // Demoralizing Roar

                            player->learnSpell(6807);   // Maul

                            player->learnSpell(16689);   // Natures Grasp

                            // Cost
                            player->ModifyMoney(-2000);   // 20 Silvers

                            // Chat Indicator
                            ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now Proficient with Druid's Basics");

                            // Goodbye
                            player->PlayerTalkClass->SendCloseGossip();
                        }
                    }  
                } 
            }
            break;

        
        }

        return true;
    }


    // Passive Emotes
    struct NPC_PassiveAI : public ScriptedAI
    {
        NPC_PassiveAI(Creature * creature) : ScriptedAI(creature) { }

        uint32 Choice;
        uint32 MessageTimer;

        // Called once when client is loaded
        void Reset()
        {
            MessageTimer = urand(60000, 180000); // 1-3 minutes
        }

        // Called at World update tick
        void UpdateAI(const uint32 diff)
        {
            if (BasicSkillsEnableAI)
            {
                if (MessageTimer <= diff)
                {
                    // Make a random message choice
                    Choice = urand(1, 3);

                    switch (Choice)
                    {
                    case 1:
                    {
                        me->Say("I can teach you about basic skills to subclassing!", LANG_UNIVERSAL);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        MessageTimer = urand(60000, 180000);
                        break;
                    }
                    case 2:
                    {
                        me->Say("You should try to learn different skills and spells!!", LANG_UNIVERSAL);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        MessageTimer = urand(60000, 180000);
                        break;
                    }
                    }
                }
                else { MessageTimer -= diff; }
            }
        };
    };

    // CREATURE AI
    CreatureAI * GetAI(Creature * creature) const override
    {
        return new NPC_PassiveAI(creature);
    }
};

void AddBasicSkillsNPCScripts()
{
    new BasicSkillsConfig();
    new BasicSkillsAnnounce();
    new BasicSkills_NPC();
}
