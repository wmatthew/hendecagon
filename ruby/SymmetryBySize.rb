=begin

If you flip X coins and arrange them in a circle, what are
the odds the pattern will be symmetrical?

Size	Sym	Total	Percent Symmetrical
1	1	1	100.0%     <-- always symmetrical
2	2	2	100.0%
3	4	4	100.0%
4	8	8	100.0%
5	16	16	100.0%
6	26	32	81.25%
7	50	64	78.125%
8	80	128	62.5%
9	130	256	50.78125%    <-- almost evenly split
10	212	512	41.40625%
11	342	1024	33.3984375%
12	518	2048	25.29296875%
13	820	4096	20.01953125%
14	1276	8192	15.576171875%
15	1864	16384	11.376953125%
16	2960	32768	9.033203125%
17	4336	65536	6.6162109375%
18	6704	131072	5.11474609375%
19	9710	262144	3.70407104492188%
20	15068	524288	2.87399291992188%    <-- rarely symmetrical


For example:
6	26	32	81.25%
- If you flip 6 coins,
- It will be symmetrical 26 / 32 times.
- That's 81.25%.

=end

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

puts "If you flip X coins and arrange them in a circle, what are
the odds the pattern will be symmetrical?";

puts "Size\tSym\tTotal\tPercent Symmetrical"

for size in 1..20
  evaluateSize(size)
end
