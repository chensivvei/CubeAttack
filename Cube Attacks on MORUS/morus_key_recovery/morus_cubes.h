#ifndef morus_cubes_H_
#define morus_cubes_H_

int output[111] = {
	0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	6,6,6,6,6,6,6,6,6,6,6,6,6,
	8,8,8,8,8,8,
	120,120,
	122,122,
	124,124,124,124,124,124,124,124,124,124,124,124,
	126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,
	127,127,127,127,127,127,127 };
int cube[111][24] = {
	{23,114, 120, 119, 18, 24, 15, 41, 78, 6, 33, 89, 70, 127, 52, 91, 73, 97, 103, 112, 75, 25, 7, 8},
	{23,57, 120, 119, 18, 24, 15, 41, 78, 6, 33, 89, 70, 127, 52, 91, 73, 97, 103, 112, 114, 25, 7, 8},
	{23,119, 18, 15, 41, 87, 32, 33, 94, 127, 3, 40, 52, 91, 73, 90, 80, 102, 112, 114, 25, 7, 8, 24},
	{22,114, 18, 15, 25, 41, 78, 33, 89, 94, 70, 127, 112, 40, 91, 73, 90, 97, 102, 3, 7, 8, 113},
	{22,114, 18, 15, 25, 41, 78, 33, 89, 94, 63, 127, 112, 40, 91, 73, 90, 97, 102, 3, 7, 8,24},
	{22,114, 18, 15, 25, 41, 78, 33, 89, 94, 121, 127, 112, 40, 91, 73, 90, 97, 102, 3, 7, 8,24},
	{22,120, 119, 24, 15, 41, 78, 6, 32, 33, 89, 70, 127, 52, 91, 73, 97, 103, 112, 114, 25, 7, 8},
	{22,114, 15, 27, 78, 94, 70, 127, 112, 69, 40, 91, 93, 73, 90, 97, 102, 25, 66, 7, 8, 10, 24},
	{22,114, 15, 27, 78, 94, 70, 127, 112, 69, 40, 91, 93, 73, 90, 97, 102, 25, 116, 7, 8, 10, 24},
	{22,121, 120, 15, 16, 52, 89, 7, 33, 34, 90, 71, 96, 36, 92, 74, 98, 104, 113, 115, 26, 8, 9},
	{23,115, 120, 19, 16, 52, 66, 34, 95, 96, 4, 70, 41, 91, 92, 74, 81, 98, 103, 113, 25, 26, 8, 9},
	{21,120, 16, 52, 49, 82, 34, 90, 95, 115, 96, 36, 41, 92, 74, 98, 103, 113, 26, 8, 9, 42},
	{21,120, 16, 52, 49, 82, 34, 90, 95, 57, 96, 36, 41, 92, 74, 98, 103, 113, 26, 8, 9, 42},
	{21,58, 16, 32, 52, 87, 34, 90, 95, 79, 113, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 57},
	{21,115, 16, 32, 123, 87, 34, 90, 95, 79, 113, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 57},
	{21,115, 16, 32, 52, 8, 34, 90, 95, 79, 113, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 57},
	{21,115, 16, 32, 52, 87, 34, 90, 114, 79, 113, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 57},
	{21,115, 16, 32, 52, 87, 34, 90, 95, 40, 113, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 57},
	{21,115, 16, 32, 52, 87, 34, 90, 95, 79, 74, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 57},
	{21,115, 16, 32, 52, 87, 34, 90, 95, 79, 113, 85, 70, 41, 91, 92, 98, 103, 25, 26, 9, 18},
	{22,123, 100, 0, 11, 27, 4, 49, 50, 76, 41, 68, 105, 87, 126, 115, 25, 75, 10, 19, 21, 60, 43},
	{22,123, 100, 0, 11, 27, 4, 49, 50, 76, 41, 68, 105, 87, 126, 115, 25, 125, 10, 19, 21, 60, 43},
	{21,34, 100, 27, 4, 49, 50, 76, 2, 41, 67, 68, 105, 29, 87, 126, 115, 10, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 98, 50, 76, 2, 41, 67, 68, 105, 29, 87, 126, 115, 10, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 99, 76, 2, 41, 67, 68, 105, 29, 87, 126, 115, 10, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 50, 76, 2, 41, 67, 119, 105, 29, 87, 126, 115, 10, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 50, 76, 2, 41, 67, 68, 105, 29, 87, 126, 115, 10, 108, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 50, 76, 2, 41, 67, 68, 66, 29, 87, 126, 115, 10, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 50, 76, 2, 41, 67, 68, 28, 29, 87, 126, 115, 10, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 50, 76, 2, 41, 67, 68, 105, 29, 87, 126, 115, 99, 19, 21, 60, 43},
	{21,123, 100, 27, 4, 49, 50, 76, 2, 41, 67, 68, 105, 29, 87, 126, 115, 10, 19, 110, 60, 43},
	{21,123, 27, 4, 43, 49, 50, 76, 2, 41, 67, 68, 124, 105, 87, 126, 10, 19, 21, 60, 42, 53},
	{21,61, 29, 55, 92, 37, 93, 66, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 126, 92, 37, 93, 66, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 3, 37, 93, 66, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 92, 30, 93, 66, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 92, 37, 93, 117, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 92, 37, 93, 66, 125, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 92, 37, 93, 66, 35, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 92, 37, 93, 66, 74, 22, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 11, 12},
	{21,118, 29, 55, 92, 37, 93, 66, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 67, 28, 11, 12},
	{21,118, 29, 55, 92, 37, 93, 66, 74, 99, 116, 88, 73, 112, 44, 94, 77, 101, 106, 28, 100, 12},
	{21,35, 101, 18, 29, 55, 92, 91, 10, 36, 37, 74, 99, 112, 56, 77, 84, 107, 116, 118, 11, 12},
	{21,124, 44, 18, 29, 55, 92, 91, 10, 36, 37, 74, 99, 112, 56, 77, 84, 107, 116, 118, 11, 12},
	{21,124, 101, 67, 29, 55, 92, 91, 10, 36, 37, 74, 99, 112, 56, 77, 84, 107, 116, 118, 11, 12},
	{21,124, 101, 18, 29, 55, 92, 91, 10, 36, 37, 74, 99, 112, 56, 77, 84, 68, 116, 118, 11, 12},
	{21,118, 124, 101, 18, 29, 55, 92, 10, 37, 93, 74, 99, 88, 73, 112, 77, 94, 107, 116, 11, 12},
	{21,38, 63, 32, 90, 6, 23, 45, 71, 72, 96, 109, 18, 19, 91, 74, 89, 112, 25, 8, 46, 47},
	{21,127, 63, 103, 90, 6, 23, 45, 71, 72, 86, 96, 109, 18, 19, 91, 74, 112, 25, 8, 46, 47},
	{21,127, 63, 32, 90, 6, 23, 45, 122, 72, 86, 96, 109, 18, 19, 91, 74, 112, 25, 8, 46, 47},
	{21,127, 63, 32, 90, 6, 23, 45, 73, 72, 86, 96, 109, 18, 19, 91, 74, 112, 25, 8, 46, 47},
	{21,127, 63, 32, 90, 6, 23, 45, 71, 72, 86, 89, 109, 18, 19, 91, 74, 112, 25, 8, 46, 47},
	{21,127, 63, 32, 90, 6, 23, 45, 71, 72, 86, 96, 0, 18, 19, 91, 74, 112, 25, 8, 46, 47},
	{21,127, 63, 32, 90, 6, 23, 45, 71, 72, 86, 96, 70, 18, 19, 91, 74, 112, 25, 8, 46, 47},
	{21,127, 63, 32, 90, 6, 23, 45, 71, 72, 86, 96, 109, 18, 19, 91, 74, 112, 25, 8, 7, 47},
	{21,127, 31, 30, 63, 32, 71, 90, 6, 45, 72, 96, 109, 123, 91, 74, 112, 25, 103, 23, 46, 47},
	{21,127, 70, 30, 63, 32, 71, 90, 6, 45, 72, 96, 109, 123, 91, 74, 112, 25, 14, 23, 46, 47},
	{21,127, 31, 30, 63, 32, 24, 90, 6, 45, 72, 96, 109, 123, 91, 74, 112, 25, 14, 23, 46, 47},
	{21,127, 126, 31, 30, 63, 32, 71, 90, 6, 45, 72, 109, 91, 74, 112, 80, 25, 14, 23, 46, 47},
	{21,127, 31, 30, 63, 32, 71, 90, 6, 45, 72, 19, 109, 123, 91, 74, 112, 25, 14, 23, 46, 47},
	{20,48, 6, 82, 92, 25, 30, 54, 73, 74, 98, 119, 0, 93, 76, 99, 94, 65, 27, 10, 33},
	{20,105, 6, 82, 92, 44, 30, 54, 73, 74, 98, 119, 0, 93, 76, 99, 94, 65, 27, 10, 33},
	{20,105, 6, 82, 92, 25, 30, 15, 73, 74, 98, 119, 0, 93, 76, 99, 94, 65, 27, 10, 33},
	{20,105, 6, 82, 92, 25, 30, 54, 124, 74, 98, 119, 0, 93, 76, 99, 94, 65, 27, 10, 33},
	{20,105, 6, 82, 92, 25, 30, 54, 73, 74, 21, 119, 0, 93, 76, 99, 94, 65, 27, 10, 33},
	{20,105, 6, 82, 92, 25, 30, 54, 73, 74, 98, 119, 0, 93, 76, 99, 94, 58, 27, 10, 33},
	{20,55, 103, 1, 23, 2, 56, 70, 89, 24, 25, 38, 49, 126, 44, 12, 95, 72, 74, 96, 16},
	{20,112, 103, 1, 23, 2, 56, 70, 89, 24, 25, 38, 10, 126, 44, 12, 95, 72, 74, 96, 16},
	{21,115, 124, 19, 20, 117, 73, 1, 60, 65, 84, 122, 79, 103, 62, 47, 68, 98, 107, 109, 2, 3},
	{21,115, 124, 19, 20, 36, 26, 1, 60, 65, 84, 122, 79, 103, 62, 47, 68, 98, 107, 109, 2, 3},
	{21,116, 117, 15, 52, 27, 83, 28, 29, 34, 53, 91, 98, 48, 72, 16, 37, 67, 76, 78, 99, 100},
	{21,116, 117, 15, 52, 74, 4, 28, 29, 34, 53, 91, 98, 48, 72, 16, 37, 67, 76, 78, 99, 100},
	{21,116, 117, 15, 52, 74, 83, 30, 29, 34, 53, 91, 98, 48, 72, 16, 37, 67, 76, 78, 99, 100},
	{21,116, 117, 15, 52, 74, 83, 28, 29, 34, 14, 91, 98, 48, 72, 16, 37, 67, 76, 78, 99, 100},
	{21,116, 117, 15, 52, 74, 83, 28, 29, 34, 53, 93, 98, 48, 72, 16, 37, 67, 76, 78, 99, 100},
	{21,117, 116, 11, 93, 38, 85, 94, 3, 62, 67, 124, 105, 32, 49, 70, 77, 100, 109, 111, 4, 5},
	{21,117, 116, 11, 12, 119, 85, 94, 3, 62, 67, 124, 105, 32, 49, 70, 77, 100, 109, 111, 4, 5},
	{21,117, 116, 11, 12, 38, 85, 94, 3, 23, 67, 124, 105, 32, 49, 70, 77, 100, 109, 111, 4, 5},
	{21,117, 116, 11, 12, 38, 85, 94, 3, 62, 67, 126, 105, 32, 49, 70, 77, 100, 109, 111, 4, 5},
	{21,117, 116, 11, 12, 48, 85, 94, 3, 62, 67, 124, 105, 32, 49, 70, 38, 100, 109, 111, 4, 5},
	{21,117, 116, 11, 12, 38, 85, 94, 3, 62, 67, 124, 105, 32, 49, 70, 77, 100, 109, 72, 4, 5},
	{21,117, 15, 6, 61, 74, 83, 28, 29, 19, 91, 48, 4, 16, 37, 66, 67, 76, 78, 99, 100, 44},
	{21,118, 119, 7, 29, 52, 76, 95, 30, 31, 44, 55, 100, 74, 1, 18, 6, 69, 78, 80, 102, 22},
	{21,112, 7, 63, 95, 30, 31, 60, 93, 78, 88, 6, 18, 40, 56, 57, 68, 97, 80, 118, 119, 46},
	{21,118, 119, 7, 29, 52, 76, 95, 30, 31, 44, 55, 100, 74, 1, 18, 56, 69, 78, 80, 102, 22},
	{21,7, 29, 101, 30, 31, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,7, 29, 52, 30, 120, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,7, 29, 52, 30, 31, 21, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,7, 29, 52, 30, 31, 60, 5, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,7, 29, 52, 30, 31, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 61, 80, 118, 119, 22},
	{21,7, 29, 52, 30, 31, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 41, 118, 119, 22},
	{21,7, 29, 52, 30, 31, 60, 44, 55, 39, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,7, 29, 52, 30, 31, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 79, 119, 22},
	{21,7, 29, 52, 30, 31, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 111},
	{21,7, 29, 52, 30, 31, 60, 44, 74, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,88, 7, 52, 30, 31, 60, 44, 55, 78, 1, 6, 18, 40, 56, 57, 95, 68, 80, 118, 119, 22},
	{21,119, 7, 125, 91, 30, 31, 60, 36, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{21,119, 7, 44, 12, 30, 31, 60, 36, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{21,119, 7, 44, 91, 30, 31, 60, 29, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{21,119, 7, 44, 91, 30, 31, 60, 36, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 45, 102, 118},
	{21,119, 7, 44, 91, 0, 31, 60, 36, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{21,119, 7, 44, 91, 49, 31, 60, 36, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{21,119, 7, 44, 91, 30, 31, 79, 36, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{21,119, 7, 44, 91, 30, 31, 60, 87, 55, 78, 74, 1, 6, 18, 56, 95, 68, 80, 84, 102, 118},
	{22,114, 120, 119, 95, 15, 3, 41, 6, 33, 89, 127, 84, 16, 91, 73, 78, 97, 103, 112, 25, 7, 8},
	{22,114, 120, 119, 24, 15, 74, 41, 6, 33, 89, 127, 84, 16, 91, 73, 78, 97, 103, 112, 25, 7, 8},
	{22,114, 120, 119, 24, 15, 3, 41, 6, 26, 89, 127, 84, 16, 91, 73, 78, 97, 103, 112, 25, 7, 8},
	{22,114, 120, 119, 24, 15, 3, 41, 6, 33, 89, 18, 84, 16, 91, 73, 78, 97, 103, 112, 25, 7, 8},
	{22,114, 120, 119, 24, 15, 3, 41, 6, 33, 89, 88, 84, 16, 91, 73, 78, 97, 103, 112, 25, 7, 8},
	{22,114, 120, 119, 24, 15, 3, 41, 6, 33, 89, 127, 84, 16, 91, 73, 78, 90, 103, 112, 25, 7, 8},
	{ 22,114, 120, 119, 24, 15, 3, 41, 6, 33, 89, 127, 84, 16, 91, 73, 78, 97, 103, 112, 25, 96, 8 }
};

#endif // !morus_cubes_H_
#pragma once
