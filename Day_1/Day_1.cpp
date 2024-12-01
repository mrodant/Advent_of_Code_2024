/***************************************************************************/
// ADVENT OF CODE 2024: DAY 1
/***************************************************************************/

#include <cmath>
#include <iostream>

using namespace std;

int main ()
{
   const int LIST_LENGTH = 1000;

   int list1[LIST_LENGTH]; // Left list
   int list2[LIST_LENGTH]; // Right list

   int distance = 0; // The total distance between the lists
   int score = 0;    // The similarity score between the lists

   // Inputs
   int id1, id2;

   for (int i = 0; i < LIST_LENGTH; i++) { // Both lists are filled

      cin >> id1;
      list1[i] = id1;

      cin >> id2;
      list2[i] = id2;
   }

   /************************************************************************/
   // Part One: Total Distance
   /************************************************************************/

   int minimum1, minimum2;
   int min_pos1, min_pos2;
   int swap;

   // By using selection sort on both lists at the same time, we make sure
   // before ending every loop cycle, the new minimum in each list is used
   // to add up to the total distance and then discarded at the beginning
   // of its list.

   for (int i = 0; i < LIST_LENGTH; i++) {
      
      minimum1 = list1[i];
      min_pos1 = i;
      
      minimum2 = list2[i];
      min_pos2 = i;

      // The minimum is found in each list
      for (int j = i + 1; j < LIST_LENGTH; j++) {

         if (list1[j] < minimum1) {
            minimum1 = list1[j];
            min_pos1 = j;
         }

         if (list2[j] < minimum2) {
            minimum2 = list2[j];
            min_pos2 = j;
         }
      }

      // Each minimum moves to the first unsorted position in each array
      swap = list1[i];
      list1[i] = list1[min_pos1];
      list1[min_pos1] = swap;

      swap = list2[i];
      list2[i] = list2[min_pos2];
      list2[min_pos2] = swap;

      distance += abs(list1[i] - list2[i]); // The total distance gets updated
   }

   /************************************************************************/
   // Part Two: Similarity Score
   /************************************************************************/

   int i = 0;
   int j = 0;

   int times_in_right_list;
   int times_in_left_list;

   // We now need to check:
   // 1. How many times a left list value appears in the right list.
   // 2. How many times that left list value appears in the left list.
   // Then, we multiply both counters by the actual value and add that up
   // to the similarity score.
   // Since the lists (arrays) are now sorted, we can do this with two
   // increasing indexes.

   while (i < LIST_LENGTH - 1) {

      times_in_right_list = 0;
      times_in_left_list  = 1;

      for (j; list2[j] <= list1[i]; j++) {

         if (list2[j] == list1[i])
            times_in_right_list ++;
      }

      if (times_in_right_list != 0) {

         for (i; list1[i] == list1[i + 1]; i++)
            times_in_left_list ++;

         // The similarity score gets updated
         score += list1[i] * times_in_left_list * times_in_right_list;
      }

      i ++;
   }

   // The last left list value is manually added, because of how the i index
   // is used in the while loop
   times_in_right_list = 0;

   for (j; list2[j] <= list1[i]; j++) {
      
      if (list2[j] <= list1[i])
         times_in_right_list ++;
   }

   score += list1[i] * times_in_right_list;

   // Outputs
   cout << "The total distance between the left list and the right list is "
        << distance << "!" << endl;
   cout << "The lists similarity score is " << score << "!" << endl;

   return 0;
}

/***************************************************************************/
/***************************************************************************/
