/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = l1 ? l1 : l2;
        int carry = 0;
        while (l1) {
            //cout << l1->val << " " << (l2 ? l2->val : -1) << endl;
            l1->val += (l2 ? l2->val : 0) + carry;
            carry = l1->val / 10;
            l1->val %= 10;
            if (l1->next) {
                l1 = l1->next;
            }else if (l2 && l2->next) {
                l1->next = l2->next;
                l1 = l1->next;
                l2 = NULL;
            }else{
                break;
            }
            if (l2 && l2->next)
                l2 = l2->next; 
            else
                l2 = NULL;
        }
        if (carry) {
            l1->next = new ListNode (carry);
        }
        return result;
    }
};
