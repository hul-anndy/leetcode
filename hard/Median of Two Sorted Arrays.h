/*There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/
/*#include <vector>
using namespace std;
//use VS
//Attention vector::size() return is not int.
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		double result_media = -1;
        int first_position = 0;
		int second_position = 0;
		int size1 = nums1.size();
		int size2 = nums2.size();
		int max_position1 = size1 -1;
		int max_position2 = size2 -1;
		int total = nums1.size() + nums2.size();
		bool is_even_number = total % 2 == 0;
		if (size1 ==0 || size2 ==0)
		{
			vector<int>* p_not_empty = size1 > 0 ? &nums1: &nums2;
			int median = total / 2;
			result_media = is_even_number ? (double)(p_not_empty->at(median) + p_not_empty->at(median-1)) / 2 : p_not_empty->at(median);
			return result_media;
		}
		if (isInterLaced(nums1,nums2) != 0)
		{
			result_media = getSpecialResult(nums1,nums2);
		}
		else
		{
			if (is_even_number)
			{
				EvenResult even_result = binarySearchMedianEven(nums1,nums2);
				int position = even_result.position;
				if (position == -1)
				{
					even_result = binarySearchMedianEven(nums2,nums1);
					int position = even_result.position;
					
					int second_number = even_result.is_left ? getNext(nums2, nums1, position) : getLast(nums2, nums1, position);
					result_media = (double)(nums2[position]+second_number)/2;
				}
				else
				{
					int second_number = even_result.is_left ? getNext(nums1,nums2 ,position) : getLast( nums1, nums2, position);
					result_media = (double)(nums1[position]+second_number)/2;
				}
			}
			else
			{
				int result = binarySearchMedianOdd(nums1,nums2);
				if (result == -1)
				{
					result = binarySearchMedianOdd(nums2,nums1);
					result_media = (double)nums2[result];
				}
				else
				{
					result_media = (double)nums1[result];
				}
			}
		}
		return result_media;
    }
	int getNext(vector<int>& nums1, vector<int>& nums2, int position)
	{
		int size1 = nums1.size();
		int size2 = nums2.size();
		int nums2_p = binarySearchPosition(nums2, 0, size2 -1, nums1[position]);
		int result = nums1[position];
			if (position < (size1 - 1) && nums2_p < size2 - 1)
			{
				result = min(nums1[position + 1], nums2[nums2_p + 1]);
			}
			else if (position < size1 - 1)
			{
				result = nums1[position + 1];
			}
			else if (nums2_p < size2 - 1)
			{
				result = nums2[nums2_p + 1];
			}
			return result;
	}
	int getLast(vector<int>& nums1, vector<int>& nums2, int position)
	{
		int nums2_p = binarySearchPosition(nums2, 0, nums2.size() - 1, nums1[position]);
		int result = nums1[position];

		if (position > 0 && nums2_p+1 >0)
		{
			result = max(nums1[position - 1], nums2[nums2_p]);
		}
		else if (position > 0)
		{
			result = nums1[position - 1];
		}
		else if (nums2_p+1 >0)
		{
			result = nums2[nums2_p ];
		}
		return result;
	}
	int min(const int first, const int second)
	{
		return first<second?first:second;
	}
	int max(const int first, const int second)
	{
		return first > second ? first : second;
	}
	int binarySearchMedianOdd(vector<int>& nums1, vector<int>& nums2)
	{
		int size1 = nums1.size();
		int size2 = nums2.size();
		int max_position1 = size1 -1;
		int max_position2 = size2 -1;
		int start1 = 0;
		int end1 = max_position1;
		int m1_p = (start1+end1)/2;
		int m2_p = binarySearchPosition(nums2, 0, max_position2, nums1[m1_p]);
		int total_smaller = m1_p+m2_p+1;
		int total = size1+size2;
		int smaller_number = total/2;
				while (total_smaller != smaller_number)
				{
					if (total_smaller < smaller_number)
					{
						start1=m1_p+1;
					}
					else if(total_smaller > smaller_number)
					{
						end1 = m1_p-1;	
					}
					if(start1 > end1)
					{
						m1_p = -1;
						break;
					}
					m1_p = (start1+end1)/2;
					m2_p = binarySearchPosition(nums2, 0, max_position2, nums1[m1_p]);
					total_smaller = m1_p+m2_p+1;
				}
		return m1_p;
	}
	struct EvenResult { int position; bool is_left; };
	EvenResult binarySearchMedianEven(vector<int>& nums1, vector<int>& nums2)
	{
		int size1 = nums1.size();
		int size2 = nums2.size();
		int max_position1 = size1 -1;
		int max_position2 = size2 -1;
		int start1 = 0;
		int end1 = max_position1;
		int m1_p = (start1+end1)/2;
		int m2_p = binarySearchPosition(nums2, 0, max_position2, nums1[m1_p]);
		int total_smaller = m1_p+m2_p+1;
		int total = size1+size2;
		int smaller_number = total/2;
				while (total_smaller != smaller_number-1 && total_smaller != smaller_number)
				{
					if(start1 > end1)
					{
						m1_p = -1;
						break;
					}
						
					if (total_smaller < smaller_number-1)
					{
						start1=m1_p+1;
					}
					else if(total_smaller > smaller_number)
					{
						end1 = m1_p-1;	
					}
					m1_p = (start1+end1)/2;
					m2_p = binarySearchPosition(nums2, 0, max_position2, nums1[m1_p]);
					total_smaller = m1_p+m2_p+1;
				}
				EvenResult result;
				result.position = m1_p;
				result.is_left = total_smaller == smaller_number-1;

		return result;
	}
	//01234*5
	int binarySearchPosition(const vector<int>& nums, const int start, const int end, const int value)
	{
		int median = (start+end)/2;
		if (value == nums[median])
			return median-1;
		if (start >= end)
		{
			int result = start;
			if (value < nums[start])// && result> 0)
				result--;
			return result;
		}
		if (value < nums[median])
			return binarySearchPosition(nums,start,median-1,value);
		if  (value > nums[median])
			return binarySearchPosition(nums,median+1,end,value);
	}
	int isInterLaced(const vector<int>& nums1, const vector<int>& nums2)
	{
		if (nums1[0] < nums2[0] && nums1[nums1.size()-1] < nums2[0])
			return 1;
		else if (nums2[0] < nums1[0] && nums2[nums2.size()-1] < nums1[0])
			return -1;
		else
			return 0;
	}
	double getSpecialResult(vector<int>& nums1, vector<int>& nums2)
	{
		
		vector<int>* p_nums1 = &nums1;
			vector<int>* p_nums2 = &nums2;
			if (isInterLaced(nums1,nums2) == -1)
			{
				p_nums1 = &nums2;
				p_nums2 = &nums1;
			}
			double result_media = -1;
			int size1 = p_nums1->size();
			int size2 = p_nums2->size();
			int total = size1 + size2;
			bool is_even_number = total % 2 == 0;
			int median = (total+1)/2;
			if (is_even_number)
			{
				if (size1 < median)
				{
					int median_position2 = median - size1 -1;
					result_media = (double)(p_nums2->at(median_position2)+p_nums2->at(median_position2+1))/2;
				}
				else if (size1 == median)
				{
					result_media = (double)(p_nums1->at(size1 -1)+p_nums2->at(0))/2;
				}
				else
				{
					result_media = (double)(p_nums1->at(median-1)+p_nums1->at(median))/2;
				}
			}
			else
			{
				if (size1 < median)
				{
					int median_position2 = median - size1 -1;
					result_media = p_nums2->at(median_position2);
				}
				else
				{
					result_media = p_nums1->at(median-1);
				}
			}
		return result_media;
	}
};