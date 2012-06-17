# Unit Tests
require 'set'
require 'test/unit'
require 'HendecagonUtils.rb'
include HendecagonUtils
require 'CloudUtils.rb'
include CloudUtils

class TestCloud < Test::Unit::TestCase

  def countVal(hash, value)
    count = 0
    for k in hash.keys
      if hash[k] == value
        count = count + 1
      end
    end
    return count
  end

  def test_getHashes
    outcomes = getOutcomeHash(getSuccessorHash(true, true))
    assert_equal(91, countVal(outcomes, "Win"))
    assert_equal(35, countVal(outcomes, "Lose"))
    assert_equal("Lose", outcomes["0"]);
    assert_equal("Win", outcomes["11"]);

    outcomes = getOutcomeHash(getSuccessorHash(true, false))
    assert_equal(84, countVal(outcomes, "Win"))
    assert_equal(42, countVal(outcomes, "Lose"))
    assert_equal("Lose", outcomes["0"]);
    assert_equal("Win", outcomes["11"]);

    outcomes = getOutcomeHash(getSuccessorHash(false, true))
    assert_equal(78, countVal(outcomes, "Win"))
    assert_equal(48, countVal(outcomes, "Lose"))
    assert_equal("Lose", outcomes["0"]);
    assert_equal("Win", outcomes["11"]);

    outcomes = getOutcomeHash(getSuccessorHash(false, false))
    assert_equal(77, countVal(outcomes, "Win"))
    assert_equal(49, countVal(outcomes, "Lose"))
    assert_equal("Lose", outcomes["0"]);
    assert_equal("Win", outcomes["11"]);
  end

  def test_getSuccessors
    seed = "11110000010";
    assert_equal(Set[
               "3-1", # 1 edge
               "3--1", # 1 edge
              ],
           getSuccessors_shrinkOneEdge(seed));

    assert_equal(Set[
               "2--1", # 2 edges
              ],
           getSuccessors_shrinkTwoEdges(seed));

    assert_equal(Set[
               "11", # fully
              ],
           getSuccessors_expandSinglesFully(seed));

    assert_equal(Set[
               "7", # partially
              ],
           getSuccessors_expandSinglesPartially(seed));

    assert_equal(Set[
               "3-1", # 1 edge
               "3--1", # 1 edge
               "2--1", # 2 edges
               "11", # fully
              ],
           getSuccessors(seed, true, true));

    assert_equal(Set[
               "3-1", # 1 edge
               "3--1", # 1 edge
               "2--1", # 2 edges
               "7", # partially
              ],
           getSuccessors(seed, true, false));

    assert_equal(Set[
               "3-1", # 1 edge
               "3--1", # 1 edge
               "11", # fully
              ],
           getSuccessors(seed, false, true));

    assert_equal(Set[
               "3-1", # 1 edge
               "3--1", # 1 edge
               "7", # partially
              ],
           getSuccessors(seed, false, false));

    # Invariants- these are true no matter what the rule booleans
    # are set to.
    for i in 0..3
      assert_equal(Set[
                ],
             getSuccessors("00000000000", i%2==0, i<2));

      assert_equal(Set[
                 "0"
                ],
             getSuccessors("11111111111", i%2==0, i<2));

      assert_equal(Set[
                 "11"
                ],
             getSuccessors("10000000000", i%2==0, i<2));

    end

    # 2-1-1-1 bug
    assert_equal(Set[
                     "1-1-1-1",
                     "1-1-1--1",
                     "6-1",
                     "5-2",
                     "4-1-2"
                    ],
                 getSuccessors("11010101000", false, false));

  end

end
