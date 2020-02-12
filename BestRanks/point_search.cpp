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
			(temp->arr).push_back(*it);
			++it; //iterate the counter 
		}
		std::sort((temp->arr).begin(), (temp->arr).end(), compare);
		return temp;
	}

	bool compare(Point A, Point B) {
		return (A.rank < B.rank);
	}
	__declspec(dllexport) int32_t  search(SearchContext* sc, const Rect rect, const int32_t count, Point* out_points)
	{
		int t = 0;
		for(auto it = (sc->arr).begin();it != (sc->arr).end();++it)
		{
			if (it->x >= rect.lx && it->x <= rect.hx && it->y >= rect.ly && it->y <= rect.hy) {
				out_points[t] = *it;
				++t;
				if (t == count) {
					break;
				}
			}

		}
		return t;
	}

	__declspec(dllexport) SearchContext*  destroy(SearchContext* sc)
	{

		(sc->arr).clear();
		delete sc;
		return nullptr;
	}