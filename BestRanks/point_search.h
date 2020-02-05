/* Given 10 million uniquely ranked points on a 2D plane, design a datastructure and an algorithm that can find the 20
most important points inside any given rectangle. The solution has to be reasonably fast even in the worst case, while
also not using an unreasonably large amount of memory.
Create an x64 Windows DLL, that can be loaded by the test application. The DLL and the functions will be loaded
dynamically. The DLL should export the following functions: "create", "search" and "destroy". The signatures and
descriptions of these functions are given below. You can use any language or compiler, as long as the resulting DLL
implements this interface. */
#ifndef BESTRANKS__C
#define BESTRANKS__C

#include <stdint.h>

	/* The following structs are packed with no padding. */
#pragma pack(push, 1)

/* Defines a point in 2D space with some additional attributes like id and rank. */
	typedef struct
	{
		int8_t id;
		int32_t rank;
		float x;
		float y;
	}Point;

	/* Defines a rectangle, where a point (x,y) is inside, if x is in [lx, hx] and y is in [ly, hy]. */
	typedef struct
	{
		float lx;
		float ly;
		float hx;
		float hy;
	}Rect;
#pragma pack(pop)

	/* Declaration of the struct that is used as the context for the calls. */
	typedef struct
	{
		//std::vector<Point> arr; //vector of Points 
		Point* arr;
		int count;
	}SearchContext;

	int check(Point* arr, Point temp, int size);
	bool compare(Point A, Point B);
	/* Declaration of the Minim_Heap class that is used for extraction of "count" points*/
	/*class Minim_Heap
	{
	private:
		std::vector <Point> heap;
		int capacity;
	public:
		
		Point* extract_min(); // get the lowest element in the heap
		void min_heapify(int id, int end); // heapify down 
		void insert(Point temp); //insert without heapifying
		void create(); //create the heap
		void swap(Point* X, Point* Y);
		void clean(); // deallocates memory for heap vector
		Minim_Heap(int size);
		bool isFull(); // whether the heap full or not
		void set_capacity(int cap); // set the max size for the heap

		// Helper functions for debugging
		int32_t test(int index);
		int sizeof_heap(); 


	};

	*/
	/* Load the provided points into an internal data structure. The pointers follow the STL iterator convention, where
	"points_begin" points to the first element, and "points_end" points to one past the last element. The input points are
	only guaranteed to be valid for the duration of the call. Return a pointer to the context that can be used for
	consecutive searches on the data. */
	typedef SearchContext* (__stdcall* T_create)(const Point * points_begin, const Point * points_end);

	/* Search for "count" points with the smallest ranks inside "rect" and copy them ordered by smallest rank first in
	"out_points". Return the number of points copied. "out_points" points to a buffer owned by the caller that
	can hold "count" number of Points. */

	typedef int32_t(__stdcall* T_search)(SearchContext* sc, const Rect rect, const int32_t count, Point* out_points);

	/* Release the resources associated with the context. Return nullptr if successful, "sc" otherwise. */
	typedef SearchContext* (__stdcall* T_destroy)(SearchContext* sc);

	extern "C" __declspec(dllexport) SearchContext*  create(const Point* points_begin, const Point* points_end);
	extern "C" __declspec(dllexport) int32_t  search(SearchContext* sc, const Rect rect, const int32_t count, Point* out_points);
	extern "C" __declspec(dllexport) SearchContext*  destroy(SearchContext* sc);

#endif