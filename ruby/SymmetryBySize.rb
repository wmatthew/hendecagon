# Symmetry by size
# This script tries to answer the question:
# if you write a random sequence of 0s and 1s along the edge of a circle,
# what is the chance that it will be symmetrical?
# for example, if you write 5 digits, it will always be symmetrical (100% of the time).
# so:
# 1-5 digits: 100% symmetrical
# 6 digits: 81.25% symmetrical
# 9 digits: ~50.7% symmetrical
# 20 digits: ~2.87% symmetrical

require 'HendecagonUtils.rb'
include HendecagonUtils

def evaluateSize(size)
  max = 2 ** (size-1)
  sym = 0
  for i in (0..max-1)
    cand = dec2bin_length(i, size)
    if (isCircleSym(cand))
      sym = sym + 1
    end
  end
  puts "#{size}\t#{sym}\t#{max}\t#{100.0*sym/max}%"
end

puts "If you write a random sequence of 0s and 1s along the edge of
a circle, what is the chance it will be symmetrical?";

puts "Size\tSym\tTotal\tPercent Symmetrical"

for size in 1..13
  evaluateSize(size)
end
