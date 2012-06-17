# Given a ring of 11 lights (on or off), how many
# can you toggle to make it symmetrical?
#
# 0: 1  * (no toggle makes it symmetrical)
# 1: 10 **
# 2: 10 ***
# 3: 0
# 4: 15
# 5: 20
# 6: 5
# 7: 0
# 8: 0
# 9: 0
# 10: 0
# 11: 2 (any toggle makes it symmetrical)
#
# * 111-11-1--- (and its photo inverse, and rotations of these)
#
# ** They are: 107,219,163,119,27,51,339,165,93,45
#    All of these are already symmetrical.
#
# *** They are: 299,203,157,139,77,87,43,79,39,83
#    None of these are already symmetrical.
#

require 'HendecagonUtils.rb'
include HendecagonUtils

module SymmetricalDistance

def flip(str_orig, index)
  str = str_orig.dup
  if (str[index,1] == "0")
    str[index] = "1"
  else
    str[index] = "0"
  end
  return str
end

def togglesToSymmetric
  states = getUniqStates(true)
  toggDist = Hash.new

  for key in states.keys
    num = dec2bin(states[key])
    count = 0
    for i in 0..10
      count = count + 1 if isCircleSym(flip(num,i))
    end
    toggDist[key] = count
  end

  counts = [];
  for dist in 0..11
    count = 0
    for key in states.keys
      if (toggDist[key] == dist)
        count = count + 1
      end
    end
    counts[dist] = count
    puts("  #{dist} edits: #{count}")
  end
  counts
end

def distCounts

  states = getUniqStates(true)
  symDist = Hash.new

  # SymDist = 0
  for key in states.keys
    num = dec2bin(states[key])
    if (isCircleSym(num))
      symDist[key] = 0
    else
      symDist[key] = "?"
    end
  end

  # SymDist = 1,2,3
  for dist in 1..3
    for key in states.keys
      if symDist[key] == "?"
        num = dec2bin(states[key])
        for index in 0..10
          copy = num.dup
          if copy[index,1] == "0"
            copy[index] = "1"
          else
            copy[index] = "0"
          end
          key2 = p2(copy, true)
          if (symDist[key2] == dist-1)
            symDist[key] = dist
          end
        end
      end
    end
  end

  counts = [];
  for dist in 0..3
    count = 0
    for key in states.keys
      if (symDist[key] == dist)
        count = count + 1
      end
    end
    counts[dist] = count
  end
  counts
end

def explainItAll
  states = getUniqStates(true)
  puts "There are #{states.count} distinct game states, ignoring rotation, reversing and inverting."

  dCounts = distCounts();
  puts "  #{dCounts[0]} are already symmetrical.";
  puts "  #{dCounts[1]} are 1 edit away from symmetrical.";
  puts "  #{dCounts[2]} is 2 edits away from symmetrical.";
  puts "  #{dCounts[3]} are 3 or more edits away from symmetrical.";

  puts "Given a ring of 11 lights, how many of the 11 possible toggles would leave it symmetrical?";
  togglesToSymmetric

end
end

include SymmetricalDistance

explainItAll

# 126 configs total.
# 64 are symmetrical.
# 60 are 1 edit away
#  2 are 2 edits away

# These are the 'least symmetrical' configurations:
# 3-2-1
# 3-1--1 (negative of the other)

#=========================================
# Note that we count all-on and all-off as 2 distinct states.
#   so we're double-counting states
#
# If we count those as the same:
# 63 configs total
# 32 are symmetrical
# 30 are 1 edit away
#  1 is  2 edits away
