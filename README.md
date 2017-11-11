# CQuest

My work for a game jam - intended to be made into a small rpg engine in c supporting dynamic content and mods. Game jam completed - engine continuing in production.

## Compilation

    cd source
    make

## Running

    usage: ./cquest <mode>
    modes: battle, graphics, filereader, attacks, prompt

## Goals

1. Make redraw actually redraw the current screen. Have a way of keeping track of and drawing the current screen configuration.
1. Make an attack tree that works in prep for combos.
1. Colors load from file format.
1. Test limits of colors.
1. Make a battle simulation.
1. Stats and attack combination read from file.
1. Basic conversation / game choice interface.
1. Perhaps some small scripting language insertion? Either an assembly format or a basic lisp-like.
