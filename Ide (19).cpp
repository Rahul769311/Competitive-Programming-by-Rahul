//RANGE QUERY-1 (SEGMENT TREE)
// In this file we will understand why there is a need of segment tree, and how we can build it.
/*
PROBLEM WITH EXISTING DATA STRUCTURES AND TECHNIQUES->

Suppose we are given an array arr=[2,3,1,4,5,2,3]. And we want to tell the sum of all the elements from index
3 to 5 (sum = 4+5+2 = 11), we will simply run a loop from index 3 to index 5 and get the sum which is actually
O(N), N is length of array in worst case. 

Let's make it a little bit complicated suppose we are given 'Q' queries and at each query we are given a range 
of indexes of the form [l,r] and we have to find the sum of all the elements lies in the range [l,r]. If for 
each query we run a loop then the time complexity we be O(Q*N), and we know that Q <= 1e5 and N<= 1e5, so the 
overall time complexity will be of the O(10^10), which will easily failed the time limit.

So we come up with a more optimize approach of Prefix Sum, which will help us to find the required answer in 
O(1) per query. So overall time complexity will be O(Q), where Q is of the order 1e6. 

Let's make the situation a little bit more complicated. Suppose at first instance we are told to find the sum 
of all the elements in the index range [l1,r1], then we are told to update an index to another value (i.e. 
arr[i] = V, we changed value at index i to V), then then we are again asked to find the sum of all elements
in the range [l2,r2]. Now, here we can see that prefix sum won't work efficiently. If we find the answer to the 
sum in the range [l1,r1] using prefix sum, and then update all the values in prefix sum array (because of 
arr[i] = V) and then again find answer to the sum in the range [l2,r2], we can easily see that it will again go 
to the O(N*Q)-> for every query we have to change the value of the array and then again compute prefix sum, which 
is worst case sceanario.

REQUIREMENT OF SEGMENT TREE->

Now we had understood the need of segment tree, we will see it's structure.
Suppose we are given the array arr=[2,1,3,5,4,2,6,1,8];

row1                              32             -> (24+8), we can see this is also the sum of all the elements
row2                    24                     8
row3             11             13            8  -> sum of elements (3+8 = 11 and so on)
row4         3       8       6       7       8   -> sum of elements (2+1 = 3, 3+5=8 and so on).
row5       2   1   3   5   4   2   6   1   8     -> array given in question.
row6       0   1   2   3   4   5   6   7   8     -> indexes

In row 5, we see that 2 written is having index 0, so we can say it has range [0,0], 1 has index 1 so we can 
say that it has range [1,1] and so on. In row 4, 3 is the sum of 1 and 2 so 3 is having the range [0,1],
similary 6 in row 4 has range [4,5] and similary 24 in row 2 has range [0,7] and 32 in row 1 has range [0,8].

Height of this Segment tree is : O(log N) to base 2.
Exp-> In first row we have only one 1 element, in second row we have 2 elements, in third row we have 4 element
and so on. So the k th row has 2^k elements. So we can say k is the height of the tree which is equal to log(N).
So height is log(N).

AGAIN REVISITING OUR PROBLEM

Now if we update any element in the array, let's say we make arr[3] = 18;
So only we have to make log(N) changes in the above segment tree.
I have marked the changes in " " and you will see for the changes we just have to move to the distance of log(N).
i.e height of the tree.
row1                              "45"             
row2                    "37"                     8
row3             "24"             13            8  
row4         3       "21"       6       7       8   
row5       2   1   3   "18"   4   2   6   1   8     
row6       0   1   2   3   4   5   6   7   8     -> indexes

Now how to find the sum of elements in the range [ql,qr].
Suppose we want to find the sum of all elements in the index range [2,7].

row1                                                           [0,8]"45"             
row2                                    [0,7]"37"                                         [8,8]8
row3                   [0,3]"24"                              [4,7]13                    [8,8]8  
row4            [0,1]3           [2,3]"21"            [4,5]6            [6,7]7          [8,8]8   
row5       [0,0]2   [1,1]1   [2,2]3   [3,3]"18"   [4,4]4   [5,5]2   [6,6]6   [7,7]1   [8,8]8     
row6         0         1        2        3          4         5       6        7         8  

This is the same segment tree which i built above, in the brackets i have mentioned the range, that the 
value outside the brackets is the sum of all numbers of given index range. Everyone can built it easily.
I had also mentioned the technique above of building it. 

So if we want to find the sum of all elements in the index range [2,7]. We start traversing from root node,
our root node is [0,8]"45", value of root node is 45 and range =[0,8], We see that [0,8] and [2,7] has an 
intersection so we have to make left and right calls simultaneously, i.e we have to call recursively on 
[0,7]"37" and [8,8]8, Now we see that [8,8] neither intersects and nor lie inside [2,7], so we return 0,
on the other hand we again see that [0,7] has an intersection with [2,7], so we again make recursive calls on
[0,3]"24" and [4,7]13, we see [0,3] has an intersection with [2,7] so we again make recursive calls to 
[0,1] and [2,3]. As [0,1] lies outside the range [2,7] so we return 0, and we also see that [2,3] lies inside
the range [2,7] so we return the value at [2,3]"21" i.e. 21. We also see that [4,7] also lies inside [2,7]
completely, so we return value 13 from there. So we get the answer as 21+13 = 34, which is the sum of all 
elements lies in the range [2,7]. 

Funda-> When you see you node range lies outside the given range, then return 0.
        When you see you node range lies completely inside the given range, then return value at that node 
        range.
        When you node range just intersects with the given range, make recursive calls on left and right.
        
It should be noted that at each level it will explore at max 2 nodes, as the range is continuous.

Time complexity-> O(log N) base 2 -> for updating any number. As for updating any number we also have to update
the tree, traversing log(N) height.
O(log N) base 2-> for getting the sum of the range [l1,r1].
O(N) -> for building the "SEGMENT TREE". We will see to it in the implementation section.

So, segment tree is the only data structure which handle the updates and query in log(N) time.
Segment Tree is also a height balanced Binary Tree.

Another important point that should be noted that, for formation of segment tree array, if index of parent
node is "i" in segment tree then the index of left child node is "2*i+1" and index of right child node is 
"2*i+2".
Let's suppose index of [0,8]"45" is i in segment tree array, then index of [0,7]"37" (left child) will be 
2*i + 1 and index of [8,8]8 is 2*i+2 in segment tree. If we take i =0, then index of [0,8]"45" will be equal
to 0, index of [0,7]37 will be equal to 1 (2*0+1) and index of [8,8]8 will be 2(2*0+2). On the similar fashion
index of [0,3]"24" will be 3, index of [4,7]13 will be 4 and index of [8,8]8 will be 5 and so on.

row1                                                           [0,8]"45"             
row2                                    [0,7]"37"                                         [8,8]8
row3                   [0,3]"24"                              [4,7]13                    [8,8]8  
row4            [0,1]3           [2,3]"21"            [4,5]6            [6,7]7          [8,8]8   
row5       [0,0]2   [1,1]1   [2,2]3   [3,3]"18"   [4,4]4   [5,5]2   [6,6]6   [7,7]1   [8,8]8     
row6         0         1        2        3          4         5       6        7         8  

So, we will implement segment tree in the form of array.
For that we will make three function namely-> build(),update(),query().
*/
#include<iostream>  
using namespace std;
#include<bits/stdc++.h>
#include<cmath>
#include<string.h>
#define ll long long int
#include <tuple>
const ll m = 1000000000+7;

// Function will build the segment tree array 
void build(ll beg,ll end,ll pos,vector<ll>&st,vector<ll>&v){
    if(beg==end){// it means we reached our leaf node, i.e. only one value is present from [beg to end] in v.
        st[pos] = v[beg];
        return;
    }
    ll mid = (beg+end)/2;
    build(beg,mid,2*pos+1,st,v); // calling build function on left
    build(mid+1,end,2*pos+2,st,v); // calling build function on right
    st[pos] = st[2*pos+1] + st[2*pos+2]; // as already stated, if index of parent child is "i", then index 
    // of its childrens are 2*i+1 and 2*i+2, and here in above question our parent is the sum of child values.
}

ll query(ll beg,ll end,ll pos,ll ql,ll qr,vector<ll>&st){
    // As discussed earlier the "3 fundas"
    if(beg>=ql and end<=qr){
        return st[pos];
    }
    else if(beg>qr || end<ql){
        return 0;
    }
    ll mid = (beg+end)/2;
    return query(beg,mid,2*pos+1,ql,qr,st) + query(mid+1,end,2*pos+2,ql,qr,st);
}

void update(ll beg,ll end,ll pos,ll index,ll value,vector<ll>&st){
    if(beg==end){
        st[pos] = value;
        return;
    }
    ll mid = (beg+end)/2;
    if(index<=mid){ // if the index we want to reach is less than mid, we will go to left section,else right.
        update(beg,mid,2*pos+1,index,value,st);
    }
    else{
        update(mid+1,end,2*pos+2,index,value,st);
    }
    st[pos] = st[2*pos+1] + st[2*pos+2];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
	cin.exceptions(ios::badbit | ios::failbit);
	ll n;
	cin>>n;// size of the given vector
	vector<ll>v(n); 
	for(ll i =0;i<n;i++){
	    cin>>v[i];
	}
	vector<ll>st(1e5+5); // segment tree array 
	ll beg = 0;
	ll end = n-1;
	ll pos = 0;
	//First i will build the segment tree 
	
	build(beg,end,pos,st,v);
	
	// Secondly i will take a query and find the sum in that range 
	
	ll ql,qr;
	cin>>ql>>qr; //Want to find the sum of the values in the index range [ql,qr].
	
	cout<<query(beg,end,pos,ql,qr,st)<<endl;
	
	// Third, i will update the vector v.
	
	ll index,value;
	cin>>index>>value;
	update(beg,end,pos,index,value,st);
	
	// Fourth, i will again take a query and find the sum in that range.
	// After updation of the vector v let's again find the sum of values in the range [ql,qr].
	
	cout<<query(beg,end,pos,ql,qr,st)<<endl; 
}

/* INPUT
7
1 4 7 34 45 33 23
2 5
4 145

OUTPUT->

119
219


*/

