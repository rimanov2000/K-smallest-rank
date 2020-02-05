#include "pch.h"
#include <stdint.h>
#include <iostream> // For testing
/* include vector lib for the use of vectors*/
#include <vector>  
/*include the header file for function and structure declerations*/
#include "point_search.h"
/* inlcude algorithm for sorting*/
#include <algorithm>

/* For min heap algorihtm, I have used https://johnderinger.wordpress.com/2012/12/28/heapify/ and https://www.geeksforgeeks.org/binary-heap/ as a reference */
	

/* Store all the values unsorted into the vector in O(n), where n is total number of elements in the input*/
__declspec(dllexport) SearchContext*  create(const Point* points_begin, const Point* points_end){
		SearchContext* temp = new SearchContext;
		temp->count = 0;
		auto it = points_begin; //create a temp variable for going through the container(as an iterator)
		while (it != points_end) {
			(temp->count)++;
			++it; //iterate the counter 
		}
		temp->arr = (Point*)malloc(sizeof(Point)*(temp->count));
		it = points_begin;
		int count = 0;
		while (it != points_end) {
			(temp->arr)[count] = *it;
			++it; //iterate the pointer 
			++count; //iterate the counter
		}
		return temp;
	}

	int check(Point* arr,Point temp,int size) {
		int big = arr[0].rank; int big_in = 0; int changed = 0;
		for (int i = 0; i < size; ++i) {
			if (arr[i].rank > temp.rank && big < arr[i].rank) {
				big = arr[i].rank;
				big_in = i;
				changed = 1;
			}
		}
		if (changed == 1 || arr[0].rank > temp.rank)
			return big_in;
		else
			return -1;
	}
	bool compare(Point A, Point B) {
		return (A.rank < B.rank);
	}
	__declspec(dllexport) int32_t  search(SearchContext* sc, const Rect rect, const int32_t count, Point* out_points)
	{

		/* 1st -  Search through the sc -> arr to determine all the points which are within the rect range in O(n) */
		
		Point* temp_arr = (Point*)malloc(sizeof(Point)*count);
		int ct = 1;
		Point* it = sc->arr;
		int index; int t = 0;
		while (ct <= (sc->count))
		{
			if (it->x >= rect.lx && it->x <= rect.hx && it->y >= rect.ly && it->y <= rect.hy) {
				if (t != count) {
					temp_arr[t++] = *it;
				}
				else {
					index = check(temp_arr,*it,count);
					if (index != -1)
						temp_arr[index] = *it;
				}
				
			}
			++ct;
		}
		std::sort(temp_arr, temp_arr + count,compare);
		
		/*std::cout << "\nMIN POINT #0: " << hp->test(0) << std::endl;
		std::cout << "MIN POINT #1: " << hp->test(1) << std::endl;
		std::cout << "MIN POINT #2: " << hp->test(2) << std::endl;
		std::cout << "MIN POINT #3: " << hp->test(3) << std::endl;
		std::cout << "MIN POINT #4: " << hp->test(4) << std::endl;
		std::cout << "MIN POINT #5: " << hp->test(5) << std::endl;
		std::cout << "MIN POINT #6: " << hp->test(6) << std::endl;
		std::cout << "MIN POINT #7: " << hp->test(7) << std::endl;*/
		int i;
		for (i = 0; i < count; ++i) {
			out_points[i] = temp_arr[i];
			free(temp_arr + i);
		}
		/*hp->create();
		/* 3rd -  extract "count" numbers from the heap in O(N) 
		Point* ex; // extracted point
		int32_t j = 0; // counter for number of points extracted
		for (int i = 1; i <= count; ++i) {
			ex = hp->extract_min();
			if (ex != NULL) {
				out_points[j] = *ex;
				++j;
				delete ex;
			}
		}
	*/
		
		return i;
	}

	__declspec(dllexport) SearchContext*  destroy(SearchContext* sc)
	{
		auto temp = sc->arr;
		for(int i = 1; i <= sc->count; ++i){
			free(temp++);
		}
		delete sc;
		if (sc == NULL) {
			return nullptr;
		}
		else
			return sc;
	}