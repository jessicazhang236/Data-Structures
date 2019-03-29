#include <stdio.h>
struct Node {
	int val;
	struct Node *next;
}
struct Node *cons (int val, struct Node *nxt) {
	struct Node *res=malloc(sizeof (struct Node));
	res->val=val;
	res->next=nxt;
	return res;
}
int length (struct Node *lst) {
	int res=0;
	for (struct Node *cur=lst; cur; cur=cur->next) ++res;
	return res;
}
struct Node *map (int (*f)(int), struct Node *lst) {
	struct Node *res=cons(0, NULL);
	struct Node *tmp=res;
	for (struct Node *cur=lst; cur; cur=cur->next) {
		tmp->next=cons(f(cur->val), NULL);
		tmp=tmp->next;
	}
	tmp=res->next;
	free(res);
	return tmp;
}
void freelist (struct Node *lst) {
	for (struct Node *cur=lst; cur;) {
		struct Node *tmp=cur;
		cur=cur->next;
		free(tmp);
	}
}
void print (struct Node *lst) {
	for (struct Node *cur=lst; cur; cur=cur->next) printf("%d ", cur->val);
}
struct Node *ins_by_index (struct Node *lst, int ind, int val) {// inserts val such that it is at index ind in lst; 0-indexed
	if (!ind) return cons(val, lst);
	int i=0;
	for (struct Node *cur=lst; cur; cur=cur->next) {
		if (i+1==ind) {
			cur->next=cons(val, cur->next);
			return lst;
		}
		else ++i;
	}
}
struct Node *ins_by_val (struct Node *lst, int val) {// inserts val into an ascending list and maintaining sortedness
	if (!lst||val<=lst->val) return cons(val, lst);
	for (struct Node *cur=lst; cur; cur=cur->next) {
		if (!(cur->next)) {
			cur->next=cons(val, NULL);
			return lst;
		}
		else if (val>=cur->val&&val<=(cur->next)->val) {
			cur->next=cons(val, cur->next);
			return lst;
		}
	}
}
struct Node *del_by_index (struct Node *lst, int ind) {
	if (!lst) return lst;
	if (!ind) {
		struct Node *tmp=lst->next;
		free(lst);
		return tmp;
	}
	int i=0;
	struct Node *prev=lst;
	for (struct Node *cur=lst; cur; cur=cur->next) {
		if (i==ind) {
			prev->next=cur->next;
			free(cur);
			return lst;
		}
		else {
			++i;
			prev=cur;
		}
	}
}
struct Node *del_by_val (struct Node *lst, int val) {// deletes first occurrence of given value
	if (!lst) return lst;
	if (val==lst->val) {
		struct Node *tmp=lst->next;
		free(lst);
		return tmp;
	}
	struct Node *prev=lst;
	for (struct Node *cur=lst; cur; cur=cur->next) {
		if (cur->val==val) {
			prev->next=cur->next;
			free(cur);
			return lst;
		}
		else prev=cur;
	}
	return lst;
}
int query (struct Node *lst, int ind) {// returns element at ind
	if (!lst) return 0;
	int i=0;
	for (struct Node *cur=lst; cur; cur=cur->next) {
		if (i==ind) return cur->val;
		else ++i;
	}
}
