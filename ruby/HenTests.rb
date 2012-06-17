# Unit Tests

require 'test/unit'
require 'HendecagonUtils.rb'
include HendecagonUtils
require 'SymmetricalDistance.rb'
include SymmetricalDistance

class TestSym < Test::Unit::TestCase

  def test_distCounts
    dc = distCounts
    assert_equal(4, dc.length);
    assert_equal(32, dc[0]);
    assert_equal(30, dc[1]);
    assert_equal(1,  dc[2]);
    assert_equal(0,  dc[3]);
  end

  def test_flip
    assert_equal("00010", flip("00000", 3));
    assert_equal("11101", flip("11111", 3));
  end

  def test_togglesToSymmetric
    ts = togglesToSymmetric
    assert_equal(1,  ts[0]);
    assert_equal(10, ts[1]);
    assert_equal(10,  ts[2]);
    assert_equal(0,  ts[3]);
    assert_equal(15,  ts[4]);
    assert_equal(20,  ts[5]);
    assert_equal(5,  ts[6]);
    assert_equal(0,  ts[7]);
    assert_equal(0,  ts[8]);
    assert_equal(0,  ts[9]);
    assert_equal(0,  ts[10]);
    assert_equal(2,  ts[11]);
  end

end

class TestHenUtils < Test::Unit::TestCase

  def test_dec2bin
    assert_equal(dec2bin(0), "00000000000");
    assert_equal(dec2bin(7), "00000000111");
    assert_equal(dec2bin("7"), "00000000111");

    # Two-argument function
    assert_equal("0110", dec2bin_length(6,4));
    assert_equal("0000110", dec2bin_length(6,7));
  end

  def test_bin2dec
    assert_equal(0, bin2dec("00000000000"));
    assert_equal(7, bin2dec("00000000111"));
    assert_equal(1025, bin2dec("10000000001"));
  end

  def test_isCircleSym
    assert(isCircleSym("0110"));
    assert(isCircleSym("1010110001"));
    assert(isCircleSym("10"));
    assert(isCircleSym("1110"));
    assert(isCircleSym("11100000"));
    assert(!isCircleSym("011010"));
  end

  def test_canonical
    assert_equal("11100000000", canonical("00000000111", false));
    assert_equal("11010000000", canonical("00000001011", false));
    assert_equal("11010000000", canonical("00000001101", false));

    assert_equal("10000000000", canonical("00000000001", true));
    assert_equal("10000000000", canonical("11111111110", true));
    assert_equal("10000000000", canonical("00000000001", false));
    assert_equal("11111111110", canonical("11111111110", false));

  end

  def test_prettyName
    assert_equal("0",  prettyName("00000000000"));
    assert_equal("1",  prettyName("10000000000"));
    assert_equal("1",  prettyName("00000100000"));
    assert_equal("1",  prettyName("00000000001"));
    assert_equal("11", prettyName("11111111111"));
    assert_equal("3-2-1", prettyName("11101101000"));
  end

  def test_p3
    assert_equal("2-1", p3(11, false));
    assert_equal("2-1", p3(22, false));
  end

  def test_p2
    assert_equal("2-1", p2("00001101000", false));
  end

  def test_getUniqStates
    s1 = getUniqStates(false)
    assert_equal(0, s1["0"]);
    assert_equal(2047, s1["11"]);

    assert_equal(nil, s1["00000000000"]);
    assert_equal(nil, s1["12"]);
    assert_equal(nil, s1[11]);
    assert_equal(nil, s1[0]);

    assert_equal(126, s1.length);

    s2 = getUniqStates(true)
    assert_equal(0, s2["0"]);
    assert_equal(nil, s2["11"]);

    assert_equal(nil, s2["00000000000"]);
    assert_equal(nil, s2["12"]);
    assert_equal(nil, s2[11]);
    assert_equal(nil, s2[0]);

    assert_equal(63, s2.length);
  end

end

