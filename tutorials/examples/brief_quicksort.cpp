//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


// #include<process.h>
#include<iostream>
#include<cstdlib>
// #include<conio.h>


int Partition(int low,int high,int arr[])
{ int i,high_vac,low_vac,pivot/*,itr*/;
    pivot=arr[low];
    while(high>low)
    { high_vac=arr[high];

        while(pivot<high_vac)
        {
            if(high<=low) break;
            high--;
            high_vac=arr[high];
        }

        arr[low]=high_vac;
        low_vac=arr[low];
        while(pivot>low_vac)
        {
            if(high<=low) break;
            low++;
            low_vac=arr[low];
        }
        arr[high]=low_vac;
    }
    arr[low]=pivot;
    return low;
}

void Quick_sort(int low,int high,int arr[])
{
    int Piv_index,i;
    if(low<high)
    {
        Piv_index=Partition(low,high,arr);
        Quick_sort(low,Piv_index-1,arr);
        Quick_sort(Piv_index+1,high,arr);
    }
}

int main()
{
    int *a,n,low,high,i;
    std::cout<<"/**************************Quick Sort Algorithm Implementation*****************/\n";
    std::cout<<"Enter number of elements:\n";
    std::cin>>n;

    a=new int[n];
    for(i=0;i<n;i++)
        a[i]=rand()%100;
    std::cout<<"Initial Order of elements\n";
    for(i=0;i<n;i++)
        std::cout<<a[i]<<"	";
    std::cout<<"\n";

    high=n-1;
    low=0;
    Quick_sort(low,high,a);
    std::cout<<"Final Array After Sorting:\n";

    for(i=0;i<n;i++)
        std::cout<<a[i]<<"	";
    std::cout<<"\n";

    // getch();
}
