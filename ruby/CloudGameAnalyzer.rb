# -*- coding: utf-8 -*-
require 'CloudUtils.rb'
include CloudUtils

def getDict
  states = getUniqStates(false)
  dict = Hash.new
  for key in states.keys
    name = key
    integer = states[key]
    dict[name] = integer
  end
  return dict
end

# Print a series of arrays of integers.
# Each array starts with an input configuration
# and ends with output configurations the computer should choose.
# every array has 6 values, padded with -1s as needed.
def printRobotGuide(expandSinglesFully, allowDoubleShrink)
  descend = getSuccessorHash(allowDoubleShrink, expandSinglesFully)
  outcomes = getOutcomeHash(descend)
  duration = getDurations(descend, outcomes)
  dict = getDict

    for key in duration.keys
      print "{ #{dict[key]}"
      count = 2
      for kid in descend[key]
        if (count > 0 &&
            outcomes[kid] != outcomes[key] &&
            duration[kid] == duration[key]-1)
          print ", #{dict[kid]}"
          count = count - 1
        end
      end
      for i in 1..count
        print ", #{-1}"
      end

      puts " },"
    end
end

def printOrderedGameMap(expandSinglesFully, allowDoubleShrink)

  puts "-------------------------"
  puts "Printing Ordered Game Map";
  puts " Rules:"
  puts "expandSinglesFully: #{expandSinglesFully ? "yes" : "no"}";
  puts "allowDoubleShrink:  #{allowDoubleShrink  ? "yes" : "no"}";
  
  descend = getSuccessorHash(allowDoubleShrink, expandSinglesFully)
  outcomes = getOutcomeHash(descend)
  duration = getDurations(descend, outcomes)

  dict = getDict

  biggest = duration.values.max
  biggest.downto(1) { | big |

    #next if (big%2)==1

    puts "‒‒‒‒#{big} moves left (#{big%2==1 ? "lose" : "win"} states)"
    for key in duration.keys
      if duration[key] == big
        puts key
         for kid in descend[key]
          if (outcomes[kid] != outcomes[key])
            puts "  suggested next move: #{kid} (#{duration[kid]} left)"
          end
         end

      end
    end
  }
  puts "==================="

end

def printAll4Maps
  printOrderedGameMap(true,false)
  printOrderedGameMap(true,true)
  printOrderedGameMap(false,true)
  printOrderedGameMap(false,false)
end

def printAllStates(expandSinglesFully, allowDoubleShrink)

  descend = getSuccessorHash(allowDoubleShrink, expandSinglesFully)
  outcomes = getOutcomeHash(descend)
  states = getUniqStates(false)
  dict = getDict

  arr = []
  for key in states.keys.sort
    if (outcomes[key] == "Win")
      kids = descend[key]
      goodKids = 0.0
      goodKids2 = 0
      allKids2 = 0
      for kid in kids
        puts "  #{kid} (#{outcomes[kid]})"
        if (outcomes[kid] == "Win")
          goodKids = goodKids + 1
        else
          kids2 = descend[kid]
          allKids2 = kids2.count
          for kid2 in kids2
            if (outcomes[kid2] == "Win")
              goodKids2 = goodKids2 + 1
            end
          end
        end
      end

      if goodKids/kids.count > 0.7
        #puts "%s: %.02f" % [key,  goodKids / kids.count]
        #puts "  kid: %d / %d" % [ goodKids2, allKids2]
      end
    end
  end
end

def decisionMatters(expandSinglesFully, allowDoubleShrink)

  puts "-------------------------"
  puts "Do your decisions matter?";
  puts " Rules:"
  puts " expandSinglesFully: #{expandSinglesFully ? "yes" : "no"}";
  puts " allowDoubleShrink:  #{allowDoubleShrink  ? "yes" : "no"}";
  

  matters = 0
  moot = 0

  descend = getSuccessorHash(allowDoubleShrink, expandSinglesFully)
  outcomes = getOutcomeHash(descend)
  states = getUniqStates(false)

  for key in states.keys.sort
    if (outcomes[key] == "Win")
      kids = descend[key]
      for kid in kids
        if (outcomes[kid] == "Win")
          matters = matters + 1
          break
        end
      end
      moot = moot + 1
    end
  end  

  puts "If you're winning, #{matters} of your decisions matter. #{moot} don't.";

end

printOrderedGameMap(false,false)
printRobotGuide(false,false)

decisionMatters(true, true);
decisionMatters(true, false);
decisionMatters(false, true);
decisionMatters(false, false);


