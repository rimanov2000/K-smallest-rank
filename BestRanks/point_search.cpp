#include "pch.h"
#include <stdint.h>
#include <iostream> // For testing
/* include vector lib for the use of vectors*/
#include <vector>  
/*include the header file for function and structure declerations*/
#include "point_search.h"

/* For min heap algorihtm, I have used https://johnderinger.wordpress.com/2012/12/28/heapify/ and https://www.geeksforgeeks.org/binary-heap/ as a reference */


/*Store all the values unsorted into the vector in O(n), where n is total number of elements in the input*/
__declspec(dllexport) SearchContext*  create(const Point* points_begin, const Point* points_end){
		SearchContext* temp = new SearchContext;
		temp->count = 1;
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
	Point* Minim_Heap::extract_min() {
		if (heap.size() > 0) {
			Point* extracted = new Point;
			*extracted = heap[0];
			heap[0] = heap[heap.size() - 1];
			heap.pop_back();
			min_heapify(0, heap.size() - 1);
			return extracted;
		}
		else
			return NULL;
	}
	void Minim_Heap::create() {
		// last non-leaf node index
		int end = heap.size() - 1;
		int index = (end / 2) - 1;

		// heapify from the first non-leaf node to the root to create the heap
		for (int i = index; i >= 0; --i) {
			min_heapify(i, end);
		}
	}
	void Minim_Heap::insert(Point temp) { heap.push_back(temp);  }
	void Minim_Heap::swap(Point* X, Point* Y) {
		Point temp = *X;
		*Y = *X;
		*X = temp;
	}
	void Minim_Heap::min_heapify(int id, int end) {
		int beg = id;
		int child_id = 2 * beg + 1;
		while (child_id <= end) {
			if (child_id + 1 <= end && heap[child_id].rank < heap[child_id + 1].rank) {
				++child_id;
			}

			if (heap[beg].rank < heap[child_id].rank) {
				swap(&(heap[beg]), &(heap[child_id]));
				beg = child_id;
				child_id = 2 * beg + 1;
			}
			else {
				return;
			}
		}

	}
	int32_t Minim_Heap::test(int index){
		return (heap[index]).rank;
	}
	Minim_Heap::Minim_Heap(int size) {
		heap.reserve(size); //the alternative could be reserving memory after determining the # of points in Rect, but it would cost us another O(N)
	}
	void Minim_Heap::clean() {
		heap.clear();
	}
	int Minim_Heap::sizeof_heap() {
		return heap.size();
	}
	bool Minim_Heap::isFull() {
		if (heap.size() == capacity) {
			return true;
		}
		else
			return false;
	}
	void Minim_Heap::set_capacity() {

	}
	int check(Point* temp) {

	}

	__declspec(dllexport) int32_t  search(SearchContext* sc, const Rect rect, const int32_t count, Point* out_points)
	{

		/* 1st -  Search through the sc -> arr to determine all the points which are within the rect range in O(n) */

		//Minim_Heap* hp = new Minim_Heap(count); // create the heap size of "count" numbers
		Point* temp_arr = (Point*)malloc(sizeof(Point)*count);
		int ct = 1;
		Point* it = sc->arr;
		int index;
		while (ct != (sc->count))
		{
			//std::cout << " ct:: " << ct << std::endl;
			if (it->x >= rect.lx && it->x <= rect.hx && it->y >= rect.ly && it->y <= rect.hy) {
				//hp -> insert(*it);
				if (ct != count) {
					temp_arr[ct - 1] = *it;
				}
				else {
					index = check(it);
					if (index != -1)
						temp_arr[index] = *it;
				}
			}
			++ct;
		}
		

		hp->create();
		/* 3rd -  extract "count" numbers from the heap in O(N) */
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
	

		return j;
	}

	__declspec(dllexport) SearchContext*  destroy(SearchContext* sc)
	{
		auto temp = sc->arr;
		for(int i = 1; i <= sc->count; ++i){
			free(temp);
			++temp;
		}

		if (sc->arr == NULL) {
			delete sc;
		}
		if (sc == NULL) {
			return nullptr;
		}
		else
			return sc;
	}
