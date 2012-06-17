# Hendecagon Utilities
# Tested in HenTests.rb
module HendecagonUtils

  ## Convert an integer str/num to binary str
  # Input: 7
  # Output: 00000000111
  def dec2bin(number)
    dec2bin_length(number, 11);
  end

  def bin2dec(str)
    sum = 0
    while (str != "")
      sum = sum * 2
      sum = sum + 1 if (str[0,1] == "1")
      str = str[1,str.length-1]
    end
    return sum
  end

  ## Convert an integer str/num to binary str
  # Can specify length
  # Input: 7, 11
  # Output: 00000000111
  def dec2bin_length(number, length)
    return "%0#{length}b" % Integer(number);
  end

  ## Returns true if any rotation of a string
  # is symmetrical; false otherwise
  def isCircleSym(string)
    for i in (0..string.length-1)
      if string == string.reverse
        return true
      elsif string.length % 2 == 0
        if string.chop == string.chop.reverse
          return true
        end
      end
      string = "#{string[1,string.length-1]}#{string[0,1]}"
    end
    return false
  end
  
  ## Rotate a string. Return the largest value.
  # Input:  00000000111
  # Output: 11100000000
  def canonical(string, inversesAreEqual)
    if string.length != 11
      puts "Error- malformed input to biggestRotation"
      return 'XXXXXXXXXXX'
    end

    candidates = []
    for index in 1..44
      candidates << string.dup
      string = string[10,1].concat(string[0,10])
      if (index == 11 || index == 33)
        string = string.reverse
      end
      if (index == 22 && inversesAreEqual)
        # invert
        string.gsub!("0", "X")
        string.gsub!("1", "0")
        string.gsub!("X", "1")
      end

    end    
    return candidates.min.reverse
  end

  ## Return a human-readable version of the string
  # Input: 11001101110
  # Output: 2--2-3
  def prettyName(string)
    if string.length != 11
      puts "Error- malformed input to prettyName"
      return 'XXXXXXXXXXX'
    end
  
    result = ""
    count = 0
    zerobuf = ""
    for index in 0..10
      if string[index,1] == "0"
        if (count > 0)
          result = result.concat(count.to_s)
          count = 0
        end
       if (result != "")
          zerobuf = zerobuf.concat("-")
        end
      else
        result = result.concat(zerobuf)
        zerobuf = ""
        count = count+1
      end
    end
  
    if (result == "" && count == 0)
      return "0"
    elsif (count > 0)
      return result.concat(count.to_s)
    else
      return result
    end
  end
  
  # Pretty-fy a number
  # Input:  44
  # Output: 2-1
  def p3(num, inversesAreEqual)
    return prettyName(canonical(dec2bin(num), inversesAreEqual));
  end
  
  # Pretty-fy a 11-digit string
  # Input:  00000011010
  # Output: 2-1
  def p2(num, inversesAreEqual)
    return prettyName(canonical(num, inversesAreEqual));
  end

  # Get an array of all unique states
  # Keys: pretty names
  # Values: 11-digit-strings
  def getUniqStates(inversesAreEqual)
    states = Hash.new
    for num in 0..2047
      key = p3(num, inversesAreEqual)
      if (states[key] == nil)
        states[key] = num
      end
    end
    return states
  end

end
