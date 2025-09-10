class ListNode:
    def __init__(self, val: int | None = None) -> None:
        self.val = val
        self.next = None

    def __repr__(self):
        return f"{self.__class__.__name__!s}({self.val!r}, {self.next!r})"


class SLL:
    def __init__(self):
        self.head = ListNode()  # dummy node
        self.tail = self.head
        self.size = 0

    def is_empty(self):
        return self.size == 0

    def append(self, val: int):
        newnode = ListNode(val)
        self.tail.next = newnode
        self.tail = newnode
        if self.head.next is None:
            self.head.next = self.tail
        print(f"Appended {newnode}")
        self.size += 1

    def prepend(self, val: int):
        newnode = ListNode(val)
        newnode.next = self.head.next
        self.head.next = newnode
        print(f"Prepended {newnode}")
        self.size += 1

    def delete_first(self):
        if self.is_empty():
            print("Empty list!")
            return

        firstnode = self.head.next
        self.head.next = firstnode.next
        print(f"Deleted {firstnode} at front")
        self.size -= 1

    def delete_last(self):
        if self.is_empty():
            print("Empty list!")
            return

        if self.size == 1:
            self.delete_first()
            return

        curnode = self.head.next

        while curnode.next is not self.tail:
            curnode = curnode.next

        node_to_delete = self.tail
        self.tail = curnode
        self.tail.next = None
        node_to_delete.next = None
        print(f"Deleted {node_to_delete} at the end!")
        self.size -= 1

    def delete_node(self, node: ListNode):
        if self.is_empty():
            print("Empty list!")
            return

        if self.tail is node:
            print("Deleting last node!")
            self.delete_last()
            return

        cur = self.head
        next = cur.next

        while next is not None:
            if next is node:
                cur.next = next.next
                print(f"{next} deleted!")
                next.next = None
                self.size -= 1
                return

            cur = next
            next = next.next

    def insert_after(self, node: ListNode):
        pass

    def delete_at_pos(self, pos: int):
        pass

    def print_list(self):
        print("# Printing nodes #")
        head = self.head.next
        while head is not None:
            print(head)
            head = head.next

    def get_node(self, val: int):
        temp = self.head.next
        while temp is not None:
            if temp.val == val:
                return temp

            temp = temp.next

        return None


def main():
    sll = SLL()
    sll.append(10)
    sll.append(20)
    sll.prepend(30)
    sll.append(110)
    sll.append(220)
    sll.prepend(230)
    sll.print_list()
    print("Phase 1 completed!!")

    print()
    node = sll.get_node(10)
    if node is not None:
        sll.delete_node(node)
    print()

    sll.delete_first()
    sll.delete_last()
    sll.delete_first()
    sll.delete_last()
    sll.print_list()
    print("Phase 2 completed!!")


if __name__ == "__main__":
    main()
