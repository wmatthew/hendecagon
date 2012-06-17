require 'set'
require 'HendecagonUtils.rb'
include HendecagonUtils

module BlackHole

  def allStates
    return 0..63
  end

  def kids(state)
    sstr = dec2bin_length(state, 6)
    result = []
    for i in 0..5
      if sstr[i,1] == "1"
        copy = sstr.dup
        copy[i] = "0"
        if (i < 5)
            copy[i+1] = "1"
        end
        result << bin2dec(copy)
      end
    end
    return result;
  end

  def outcomes
    outs = Hash.new
    for state in allStates
      outs[state] = "?";
    end

    for i in 1..20
      for state in allStates
        if outs[state] == "?"
          allWins = true
          for kid in kids(state)
            if outs[kid] == "Lose"
              outs[state] = "Win"
              allWins = false
            elsif outs[kid] == "?"
              allWins = false
            end
          end
          if (allWins)
            outs[state] = "Lose"
          end
        end
      end
    end
    outs
  end

  def printWinStates
    o = outcomes()

    puts "Outcomes:"
    for key in 0..63
      bin = dec2bin_length(key,6)
      out = o[key]
      puts " #{bin}: #{out} state"
    end
  end

  def printWinStatesShort
    o = outcomes()

    puts "Outcomes (short):"
    for key in 0..63
      bin = dec2bin_length(key,6)
      out = o[key]

      if out == "Lose"
        print "#{key} "
      end
    end
    puts
  end

end

include BlackHole
printWinStates
printWinStatesShort
