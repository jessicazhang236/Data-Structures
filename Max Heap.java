class MaxHeap { // Java implementation of a max heap
	private int arr[], lst;
	private final int sz;
	public MaxHeap (int N) {
		sz=N;
		lst=0;
		arr=new int[sz+1];
	}
	public void push (int val) { // inserts element
		arr[++lst]=val;
		for (int i=lst; i>1; i/=2) {
			if (arr[i>>1]<arr[i]) {
				int tmp=arr[i>>1];
				arr[i>>1]=arr[i];
				arr[i]=tmp;
			}
		}
	}
	public int max() { // returns maximum element
		return arr[1];
	}
	public void pop() { // deletes maximum element
		arr[1]=arr[lst--];
		for (int i=1; i<lst;) {
			if (arr[i]<max(arr[i<<1], arr[i<<1|1])) {
				if (arr[i<<1]>arr[i<<1|1]) {
					int tmp=arr[i];
					arr[i]=arr[i<<1];
					arr[i<<1]=tmp;
					i*=2;
				}
				else {
					int tmp=arr[i];
					arr[i]=arr[i<<1|1];
					arr[i<<1|1]=tmp;
					i=i*2+1;
				}
			}
			else break;
		}
	}
	public boolean empty() { // checks if the max heap is empty
		if (!lst) return true;
		return false;
	}
	public int size() { // returns number of elements in the max heap
		return lst;
	}
}