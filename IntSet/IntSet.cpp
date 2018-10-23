// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet()
{
   //the private array of ints 'data' is initialized to size equal to 'IntSet::MAX_SIZE'.
   //used represents the number of relevant ints in the IntSet; this is set to 0

   data[IntSet::MAX_SIZE] = {0};
   used = 0;

}

int IntSet::size() const
{
   //basic access function. returns the value of private int 'used'

   return used; // used is the number of relevant int in the IntSet
}


bool IntSet::isEmpty() const
{
   //checks to see if used is 0. if yes return true.
   //else return false

   if(used == 0)
      return true;
   return false;
}

bool IntSet::contains(int anInt) const
{
   //a for loop is used to iterate through 'data',
   //checking at each position to see if 'data[i]' matches 'anInt'
   //return true if found. false if not.
   for(int i = 0; i < size(); i++)
   {
      if(data[i] == anInt)
         return true;
   }
   return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   //first we check to see if this 'IntSet' is empty because empty set
   //is subset of all sets by definition. if empty, return true.
   //then 'data' of this 'IntSet' is iterated through and checked to see
   //if it is NOT in 'otherIntSet'. if it is not false is returned.
   //if end of iteration if reached without false return, then all elements
   //are in 'otherIntSet' and true is returned.

   if( isEmpty() )
      return true;
   for(int i = 0; i < size(); i++)
   {
      if( !otherIntSet.contains(data[i]) )
         return false;
   }
   return true;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
         for (int i = 1; i < used; ++i)
      out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   //first 'assert' is used to make sure the union of this 'IntSet' and
   //'otherIntSet' does not excede MAX_SIZE (as per prof's instruction).
   //then 'otherIntSet' is copied to a temporary 'IntSet' and then every
   //element from this 'data' is attempted to be added to 'temp'
   //(add is implimented so that it will not re-add elements already in
   //the list). return the resulting 'IntSet', 'temp'.

   assert(size() + (otherIntSet.subtract(*this)).size() <= IntSet::MAX_SIZE);
   IntSet temp = otherIntSet;
   for(int i = 0; i < size(); i++)
      temp.add(data[i]);
   return temp;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   //first an empty 'IntSet' 'temp' is created. then 'data' is iterated
   //through, checking if each element matches an element in 'otherIntSet'.
   //if this is the case, the element is added to temp. after the entire
   //'data' has been searched, 'temp' is returned.

   IntSet temp;
   for(int i = 0; i < size(); i++)
   {
      if(otherIntSet.contains(data[i]))
         temp.add(data[i]);
   }
   return temp;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   //first temporary 'IntSet' 'temp' is created matching this 'IntSet'.
   //then this 'data' is iterated through to check if the elements in this
   //'IntSet' match 'otherIntSet', removing from 'temp' any matching
   //elements. after all common elements are removed from 'temp', it is
   //returned.

   IntSet temp = *this;
   for(int i = 0; i < temp.size(); i++)
   {
      if(otherIntSet.contains(temp.data[i]))
         temp.remove(temp.data[i--]);
   }
   return temp;
}

void IntSet::reset()
{
   //the number of relevant elements is set to zero. that is all.
   used = 0;
}

bool IntSet::add(int anInt)
{
   //first add checks to see that there is space in 'data' to add another
   //element. if not return false.
   //otherwize, at index position size() (first available position) the
   //value of the new element is copied, the number of relvant elements
   //is incremented, and true is returned.

   if(size() >= IntSet::MAX_SIZE || contains(anInt))
   {
      cout << "failed to add element to IntSet";
      return false;
   }
   data[size()] = anInt;
   used++;
   return true;
}

bool IntSet::remove(int anInt)
{
   /* THIS IS NOT USED IN MY VERSION, BUT IT IS A MORE EFFICENT (AND MORE LAZY)
   * 		WAY TO REMOVE AN ELEMENT
   * This version of remove will not attempt to maintain the relative order of elements
   if(contains(anInt))
   {
      for(int i = 0; i < size(); i++)
      {
         if(data[i] == anInt)
         {
            data[i] = data[size() -1];
            break;
         }
      }
      used--;
      return true;
   }
   */

   //This version of remove will maintain the relative order of elements
   //when an element is removed.
   //first a check is performed to ensure 'anInt' is in the IntSet.
   //then 'data' is searched until 'anInt' is located.
   //starting with the index position that matched 'anInt',
   //each subsequent position is copied into the previous position.
   //decrement the size by 1 and return true in indicate 'remove' was
   //successful.
   //return false if IntSet does not contain 'anInt'

   if(contains(anInt))
   {
      for(int i = 0; i < size() ; i++)
      {
         if(data[i] == anInt)
         {
            for(int j = i; j < size() -1 ; j++)
               data[j] = data[j+1];
            used--;
            return true;
         }
      }
   }
   return false;
}

bool equal(const IntSet& is1, const IntSet& is2)
{
   //if IntSet 'is1' and IntSet 'is2' are both empty, they are equal.
   //return true.
   //if IntSet 'is1' subtract IntSet 'is2' returns an empty set and
   //IntSet 'is2' subtract IntSet 'is1' returns an empty set then they are equal.

   if(is1.isEmpty() && is2.isEmpty())
      return true;
   if( is1.subtract(is2).isEmpty() && is2.subtract(is1).isEmpty() )
      return true;
   return false;
}
