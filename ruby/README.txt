** CONTAINS PUZZLE SPOILERS **
--------------------------------------------------------------------------------
Hendecagon Analysis Ruby Scripts
Matthew Webber 2012

The Hendecagon is a puzzle game. It is a physical device about the size of a pie,
with 11 buttons that light up 11 pie-sliced wedges. You can read more
(and see pictures) here: http://m.atthe.ws/portfolio/hendecagon/

This is a set of scripts to analyze feasibilty and design puzzles for that game.

For example, imagine a player vs. computer game where the puzzle starts with all
lights on. On a turn, the player or computer must turn off one light, which will
turn off neighboring lights if they are on.

If the computer plays perfectly, which starting configurations give the human
a shot at winning? What strategy should the computer follow? How long will
the game be?

Questions like this are answered by the scripts here. Below is a description
of what each file does and how to use it.

--------------------------------------------------------------------------------
Technical Notes
Note that these scripts are meant to quickly give the accurate answers to game
design questions. At times, performance and space have been sacrificed in
favor of simplicity.

Everything should work out of the box; there are no external libraries or
environment modifications needed. All scripts were tested with this version
of Ruby:
> ruby -v
ruby 1.8.7 (2011-12-28 patchlevel 357) [universal-darwin11.0]
>

--------------------------------------------------------------------------------
HendecagonUtils.rb
  A module of utility functions handles configurations of lights. For instance,
if 3 of 11 lights are on, there are several ways to represent this:
  1. 00000000111  (binary string, where 1=light on)
  2. 7		  (binary integer)
  3. 3		  (run length encoding http://en.wikipedia.org/wiki/Run-length_encoding)

  The functions here convert between these formats. They let the user get a
  sequence's canonical value (which will be the same if the puzzle is rotated
  or flipped). Where needed, functions let the caller specify if, for the
  purposes of the task at hand, inverses are equal (eg 00000000111 vs 11111111000)

-------------------------
Usage And Expected Output
  none; should be included from other files.

--------------------------------------------------------------------------------
HenTests.rb
  Unit tests for each of the functions in HendecagonUtils.rb

-------------------------
Usage And Expected Output

> ruby HenTests.rb 
Loaded suite HenTests
Started
...........
Finished in 1.385471 seconds.

11 tests, 63 assertions, 0 failures, 0 errors
--------------------------------------------------------------------------------
CloudUtils.rb

The Cloud game is a 2-player game, meant to be played human player vs. computer
as a puzzle. Although it's possible for the human to win each game, it can be
hard and require strategy.

These are the rules of the Cloud Game:
1. The game starts with some of the lights on. Human goes first.
2. On a turn, a player taps a light.
3a. If the light is part of a run of 1 light, the run expands outward until it
reaches a light that is on. For instance:
        01100100011 (starting state)
             *      (user presses middle light)
        01101110011 (run expands out)
        01111111011 (run expands again, and stops because it hits another run)
                    (turn over)
3b. If that light is the edge of a run of lights, it turns off.
3c. If that light is the middle of a run of lights, one of the run edges turns off.
3d. If the pressed light is off or all lights are on, the player loses immediately.
4. Turns alternate between players until one loses.

This module provides a set of utility functions for analyzing this game.
The functions include:
- given a state, what are the valid next states (successors)
- given a state, what will the eventual outcome be, if both players play optimally?
- given a state, how long will the game last if both players play optimally?

The module also provides support for two game variants, 'expandSinglesFully'
and 'allowDoubleShrink'.

-------------------------
Usage And Expected Output
  none; should be included from other files.

--------------------------------------------------------------------------------
CloudTests.rb
  Unit tests for each of the functions in CloudUtils.rb

-------------------------
Usage And Expected Output
> ruby CloudTests.rb 
Loaded suite CloudTests
Started
..
Finished in 2.721772 seconds.

2 tests, 37 assertions, 0 failures, 0 errors

--------------------------------------------------------------------------------
CloudGameAnalyzer.rb

For the Cloud game described above, this script prints two descriptions of
the game:
1. A human-readable move list showing game states, whether they are winning or
losing (assuming optimal play), and suggested next moves.
2. The same information encoded in a list of int arrays, limiting suggestions
to two per scenario.

It also prints a summary of how often your decisions matter when playing the
game under 4 variations of the rules.

Reading these last results, I became aware that in a typical game, most of the
choices a human player makes are not meaningful- losing humans always lose,
and most of the time, winning humans keep winning. 

Practically speaking, this means it's very likely a player will win his/her
first game before learning the rules.

Based on the output here I decided to exclude the Cloud game from the final
version of the Hendecagon puzzle.

-------------------------
Usage And Expected Output
> ruby CloudGameAnalyzer.rb > CloudGameAnalyzer.rb.output
output: see CloudGameAnalyzer.rb.output

--------------------------------------------------------------------------------
BlackHoleAnalyzer.rb

The black hole game is a 2-player human vs computer game like the cloud game
described above. The rules are:

1. six lights start on. the left one is the black hole.
2. on a turn, a player must press a light that is on. 
3. when pressed, the light moves one step toward the black hole.
4. if on the black hole, the light turns off.
5. if there are no lights left, the player loses.

(note: the display is slightly different than described here for aesthetic
reasons, but this ruleset is tactically identical)

This script prints out all states for this game in order, and lists
for each one if it is losing or winning.

It then prints just the lose states again, in abbreviated form. The AI
strategy for this challenging game is simply to avoid these 21 losing states:
0 2 5 8 10 15 17 20 22 25 29 32 34 37 40 42 47 51 59 60 62

-------------------------
Usage And Expected Output
> ruby BlackHoleAnalyzer.rb > BlackHoleAnalyzer.rb.output
output: see BlackHoleAnalyzer.rb.output
>

--------------------------------------------------------------------------------
SymmetricalDistance.rb

Functions that help evaluate how many light configurations are symmetrical, and
how many toggles it takes to make any given configuration symmetrical.

The surprising conclusion I reached is that any configuration can be made
symmetrical with a single toggle, except for one configuration:
  3-2-1 (end-run encoding)
  11101101000 (binary string encoding)

-------------------------
Usage And Expected Output
> ruby SymmetricalDistance.rb 
There are 63 distinct game states, ignoring rotation, reversing and inverting.
  32 are already symmetrical.
  30 are 1 edit away from symmetrical.
  1 is 2 edits away from symmetrical.
  0 are 3 or more edits away from symmetrical.
Given a ring of 11 lights, how many of the 11 possible toggles would leave it symmetrical?
  0 edits: 1
  1 edits: 10
  2 edits: 10
  3 edits: 0
  4 edits: 15
  5 edits: 20
  6 edits: 5
  7 edits: 0
  8 edits: 0
  9 edits: 0
  10 edits: 0
  11 edits: 2
>

--------------------------------------------------------------------------------
SymmetryBySize.rb

When designing the Hendecagon, before I knew how many sides I wanted it to have,
I thought that symmetry was a good measure of complexity. I wanted a circular
field that was big enough that a random light configuration wouldn't be
symmetrical.

This script tries to answer the question: If you write a random sequence of 0s
and 1s along the edge of a circle, what is the chance that it will be
symmetrical?

For example, if you write 5 digits, it will always be symmetrical (100% of
the time).
# so:
# 1-5 digits: 100% symmetrical
# 6 digits: 81.25% symmetrical
# 9 digits: ~50.7% symmetrical

-------------------------
Usage And Expected Output
> ruby SymmetryBySize.rb 
If you write a random sequence of 0s and 1s along the edge of
a circle, what is the chance it will be symmetrical?
Size	  Sym  Total  Percent Symmetrical
1	  1    1      100.0%
2	  2    2      100.0%
3	  4    4      100.0%
4	  8    8      100.0%
5	  16   16     100.0%
6	  26   32     81.25%
7	  50   64     78.125%
8	  80   128    62.5%
9	  130  256    50.78125%
10	  212  512    41.40625%
11	  342  1024   33.3984375%
12	  518  2048   25.29296875%
13	  820  4096   20.01953125%
>

--------------------------------------------------------------------------------
TickerTape.rb

For one of the sub-puzzles, I wanted to make a list of the "most complicated"
light configurations- ones that were can't be easily described after looking
at them for a moment. For example:

SIMPLE
11000000000  "group of 2 lights" ---> too simple
11110111100  "2 groups of 4 lights" ---> too simple

COMPLICATED
11100110100  "3 lights on, then a gap of 2, then 2 lights, then a gap, then..." ---> good, complicated.

The complicated ones generated are all those that fit these criteria:
 - run-length encoding string is at least 6 long
 - the lights are half on and half off (5/6 split)
 - the pattern is not symmetrical

(redundent patterns, such as inverses, rotations and reverses have been removed)

-------------------------
Usage And Expected Output
> ruby TickerTape.rb 
Complex Configurations: run-length encoding
3-2--1
3--2-1
2-2-1-1
4-1--1
2--3-1
1-3-1-1
3-1-1-1
2-1-2-1
Complex Configurations: binary integer encoding
311
359
347
303
371
349
343
363
>

--------------------------------------------------------------------------------




