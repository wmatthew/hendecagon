# Quick script to get 'interesting' 11-circle patterns.
# for ticker-tape level

require 'HendecagonUtils.rb'
include HendecagonUtils

s1 = getUniqStates(false)
complex = []


for key in s1.keys
  if (key.length > 5)
    sum = 0
    str = dec2bin(s1[key])
    for i in 0..str.size-1
      if str[i,1] == "1"
        sum = sum + 1
      end
    end
    if (sum == 6)
      if (!isCircleSym(dec2bin(s1[key])))
        complex.push(key)
      end
    end
  end
end

puts "Complex Configurations: run-length encoding"
for c in complex
  puts c
end

puts "Complex Configurations: binary integer encoding"
for c in complex
  puts s1[c]
end
