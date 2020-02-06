# K-smallest-rank
Finding the "count" number smallest ranks points from the given 2D graph of points.
1. Solution repo holds the algorithm which searches the array for "count" number of smallest elements and then sorts it to get correct positions for each element:
   * It takes O(N) to store all points into dynamic array
   * It takes O(c*K) to go through the array and find "count"= c smallest ranked points from the given points, where K is the total number of Points inside the Rect given
   * It takes O(clogc) time to sort the unsorted array for correct poisitons of each point
   ### To sum up: O(N+cK+clogc) = O(N) 
2. linear repo holds the algorithm that uses min heap logic to extract the minimum element from the heap for "count" times
   * It takes O(N) to store all points into dynamic array
   * It takes O(N) to go through array and checks each time whether the current point rank is smaller than any point from the heap, so in total O(N+cK), where c is count, and K is the total number of Points inside the Rect given.
   * It takes O(c) to create heap, and O(clogc) to extract the min for c times
   ### To sum up: O(N + N + cK + c + clogc) = O(N)
   
