require 'set'
require 'HendecagonUtils.rb'
include HendecagonUtils

module CloudUtils

  #=========================
  # Duration Ranges
  # How short/long could the game be, from each position?

  # Computer (loser) will try to make game long
  # Human (winner) will try to make game short
  def getDurations(descend, outcomes)
    duration = Hash.new
    for key in outcomes.keys
      if (descend[key].length == 0)
        duration[key] = 1
      else
        duration[key] = "?";
      end
    end

    for i in 1..100
      stillHaveUnknowns = false
      for key in duration.keys
        if duration[key] == "?"
          stillHaveUnknowns = true
          allKnown = true
          wantMin = outcomes[key] == "Win"
          cands = []
          for kid in descend[key]
            if (outcomes[kid] != outcomes[key])
              if (duration[kid] == "?")
                allKnown = false
                break
              else
                cands << duration[kid]
              end
            end
          end
          if (allKnown)
            duration[key] = 1 + (wantMin ? cands.min : cands.max)
          end
        end
      end
      if (!stillHaveUnknowns)
        #puts "Settled in #{i} rounds"
        break
      end
    end
    return duration
  end
  
  #=====================
  # Descendants Hash
  # Key: state key, eg 3-2-1
  # Value: set of children of that state
  def getSuccessorHash(allowDoubleShrink, expandSinglesFully)
    states = getUniqStates(false)
    descend = Hash.new
    for key in states.keys
      num = dec2bin(states[key])
      kids = getSuccessors(num, allowDoubleShrink, expandSinglesFully)
      descend[key] = kids
    end
    return descend
  end
  
  #=====================
  # Outcome Hash
  # Key: state key, eg 3-2-1
  # Value: "Win" or "Lose"
  def getOutcomeHash(descend)
    states = getUniqStates(false)
    outcomes = Hash.new
    for key in states.keys
      outcomes[key] = "?"
    end

    for i in 1..100
      stillHaveUnknowns = false
      for key in outcomes.keys
        if (outcomes[key] == "?")
          stillHaveUnknowns = true
          allWins = true
          for kid in descend[key]
            if (outcomes[kid] == "Lose")
              outcomes[key] = "Win"
              allWins = false
            elsif (outcomes[kid] == "?")
              allWins = false
            end
          end
          if (allWins)
            outcomes[key] = "Lose";
          end
        end
      end
      if (!stillHaveUnknowns)
        #puts "Settled in #{i} rounds."
        break
      end
    end
    return outcomes
  end

  def getSuccessors(string, allowDoubleShrink, expandSinglesFully)
    if string.length != 11
      puts "Error"
      return []
    end
    
    kids = Set.new
    
    # Special case
    if (string == "11111111111")
      kids.add("0")
      return kids
    end

    #==========================
    # Narrowing edges of big islands
    kids = kids + getSuccessors_shrinkOneEdge(string)
    if allowDoubleShrink
      kids = kids + getSuccessors_shrinkTwoEdges(string)
    end
    
    #==========================
    # Expand 1-islands
    if (expandSinglesFully)
      kids = kids + getSuccessors_expandSinglesFully(string)
    else
      kids = kids + getSuccessors_expandSinglesPartially(string)
    end
    
    return kids
  end
  
  def getSuccessors_shrinkOneEdge(string)
    kids = Set.new
    for index in 1..11
      if (string[0, 3] == "011")
        kids.add(p2("001".concat(string[3,8]), false))
      elsif (string[0, 3] == "110")
        kids.add(p2("100".concat(string[3,8]), false))
      end
      string = string[10,1].concat(string[0,10]) #rotate
    end
    return kids
  end

def getSuccessors_shrinkTwoEdges(string)
  kids = Set.new
  for index in 1..11
    string = string[10,1].concat(string[0,10]) #rotate
    if (string[0, 3] == "111" && string[10,1] == "0")
      copy = string.dup
      copy[0] = "0"
      for index2 in 2..9
        if copy[index2,2] == "10"
          copy[index2,2] = "00"
          kids.add(p2(copy, false))
         break
        end
      end
     end
  end
  return kids
end

def getSuccessors_expandSinglesPartially(string)
  kids = Set.new
  for index in 1..11
    string = string[10,1].concat(string[0,10]) #rotate
    if (string[4,3] == "010")
      copy = string.dup
      for jj in 6..10
        if (copy[jj,1] == "0" && copy[10-jj,1] == "0")
          copy[jj] = "1"
          copy[10-jj] = "1"
        else
          break
        end
      end
      kids.add(p2(copy, false))
    end
  end    
  return kids
end

def getSuccessors_expandSinglesFully(string)
  kids = Set.new
  for index in 1..11
    string = string[10,1].concat(string[0,10]) #rotate

    if (string[0, 3] == "010")
      copy = string.dup
      copy[0..2]="111"
      for jj in 3..10
        if (copy[jj,1] == "0")
          copy[jj,1] = "1";
        else
          break
        end
      end
      copy = copy.reverse
      for jj in 0..7
        if (copy[jj,1] == "0")
          copy[jj,1] = "1";
        else
          break
        end
      end
      kids.add(p2(copy, false))
    end
  end
  return kids
end

end
