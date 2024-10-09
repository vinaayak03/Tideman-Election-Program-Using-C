This program implements the Tideman voting system, where voters rank candidates in order of preference. The program records each voter's rankings, adds pairwise comparisons between candidates, and sorts these pairs by strength of victory. 
It locks pairs into a graph structure without creating cycles and then determines the winner based on the final structure. This system ensures that the most preferred candidate,
according to the voters’ rankings, is selected as the winner. The program handles multiple candidates and outputs the winner of the election based on the locked pairs.
