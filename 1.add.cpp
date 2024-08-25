#include<stdio.h>
int binarySearch(int * num,int target,int left,int right)
{
    if(left>right) return -1;
    int mid = (left+right)/2;
    if(num[mid] == target) return  mid;
    if(num[mid] > target)
        return binarySearch(num,target,left,mid-1);
    else
        return binarySearch(num,target,mid+1,right); 

}

int search(int * num,int numSize,int target)
{
    return binarySearch(num,target,0,numSize-1);
}
int main()
{   
    int arr[] = {1,4,5,6,7,9,10},target=10;
    printf("%d\n",search(arr,7,target));
    return 0;  
} 