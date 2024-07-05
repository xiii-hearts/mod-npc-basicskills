# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

- Latest build status with azerothcore:
[![Build Status](https://github.com/xiii-hearts/mod-npc-basicskills/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/xiii-hearts/mod-npc-basicskills)



# NPC Subclass [Skills & Spells Proficiency]

## Description
Adds NPCs that will teach all about basic Skills & Spells that are unavailable to all Classes, thus making a "subclass" like characters.

Part 2 of The SubClass Series Module.
- e.g - Warrior will be able to use healing spells from Priest.

All of the Skills/Spells can be learned through purchasing the desired skills.

### Learnable Basic Skills/Spells (All Skills/Spells are Rank 1)

Warrior's Basics
- Shield Bash
- Charge 
- Battle Shout
- Heroic Strike
- Taunt
- Sunder Armor
- Hamstring
- Rend

Paladin's Basics
- Seal of Righteousness
- Devotion Aura
- Hammer of Justice
- Divine Protection
- Holy Light
- Blessing of Might
- Purify
- Hand of Protection
- Lay on Hands

Hunter's Basic
- Auto Shot
- Hunter's Mark
- Concussive Shot
- Aspect of the Hawk
-  Hooked Net
- Arcane Shot
- Aspect of Monkey
- Serpent Sting

Rogue's Basics
- Pick Lock
- Pick Pocket
- Stealth
- Sprint
- Evasion
- Sinister Strike
- Backstab
- Gouge
- Slice and Dice

Priest's Basics
- Lesser Heal
- Smite
- Power Word: Shield
- Fade
- Mind Blast
- Resurrection

Death Knight's Basics
- Death Grip
- Obliterate
- Raise Dead
- Forceful Deflection

Shaman's Basics
- Healing Wave
- Earth Shock
- Lightning Shield
- Flametongue Weapon
- Flame Shock
- Bloodlust
- Force of Nature

Mage's Basics
- Fireball
- Fire Shield
- Frostbolt
- Frost Armor
- Conjure Water
- Conjure Food
- Fire Blast
- Arcane Missiles
- Polymorph
- Frost Nova

Warlock's Basics
- Shadow Bolt
- Demon Skin
- Immolate
- Corruption
- Curse of Weakness
- Fear
- Curse of Agony
- Drain Soul
- Summon Voidwalker

Druid's Basics
- Wrath
- Healing Touch
- Mark of the Wild
- Moonfire
- Thorns
- Entangling Roots
- Bear Form
- Demoralizing Roar
- Maul
- Natures Grasp

## Installation
1) Unzip and place the module folder under the `modules` folder/directory of your AzerothCore source.
2) Rename `mod-npc-basicskills-master` folder to `mod-npc-basicskills`
3) Re-run cmake and launch a clean build of AzerothCore.
4) Put the SQL file to the world database.

## How To Use
- Add the npc to the world by using GM command `.npc add 600002` or `.npc add temp 600002`

## Updates
- Added Warnings/Restrictions when player do not meet the cost and level requirement.
- Added All of the Classes Basic Skills & Spells to the NPC.
- Added Exception For Players With The Learned Abilities/Skills.



