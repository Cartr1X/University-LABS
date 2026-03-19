class BinaryTree:
    class Node:
        def __init__(self, value):
            self.value = value
            self.left = self.right = None
    
    def __init__(self, root_value):
        self.root = self.Node(root_value)
    
    def insert(self, value):
        self._insert(self.root, value)
    
    def _insert(self, node, new_value):
        if new_value < node.value:
            if node.left:
                self._insert(node.left, new_value)
            else:
                node.left = self.Node(new_value)
        else:
            if node.right:
                self._insert(node.right, new_value)
            else:
                node.right = self.Node(new_value)
    
    def display(self):
        lines = self._display(self.root)[0]
        print('\n'.join(lines))
    
    def _display(self, node):
        if not node:
            return [], 0, 0
        
        left, l_width, l_height = self._display(node.left)
        right, r_width, r_height = self._display(node.right)
        
        value = str(node.value)
        val_len = len(value)
        
        if left:
            l_pos = (l_width - 1) // 2
        else:
            l_pos = 0
            
        if right:
            r_pos = (r_width - 1) // 2
        else:
            r_pos = 0
        
        first_line = ' ' * (max(0, l_width - l_pos)) + value
        
        second_line = ''
        if left:
            second_line += ' ' * l_pos + '/'
        if right:
            second_line += ' ' * (val_len + max(0, r_width - r_pos - len(second_line))) + '\\'
        
        result = [first_line, second_line]
        
        for i in range(max(l_height, r_height)):
            l_line = left[i] if i < l_height else ' ' * l_width
            r_line = right[i] if i < r_height else ' ' * r_width
            result.append(l_line + ' ' * val_len + r_line)
        
        return result, l_width + r_width + val_len, len(result)

# Рисуем древо
numbers = [50, 30, 70, 20, 40, 60, 80]
tree = BinaryTree(numbers[0])
for num in numbers[1:]:
    tree.insert(num)

print("Дерево:")
tree.display()

class Node:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def count_nodes(root):
    if root is None:
        return 0
    return 1 + count_nodes(root.left) + count_nodes(root.right)

def Maxdepth(root):
    if not root:
        return 0
    left_depth = Maxdepth(root.left)
    right_depth = Maxdepth(root.right)

    return max(left_depth, right_depth) + 1

def Mindepth(root):
    if not root:
        return 0
    left_depth_1 = Mindepth(root.left)
    right_depth_1 = Mindepth(root.right)
    
    return min(Mindepth(root.left), Mindepth(root.right)) + 1
    
root = Node(50)
root.left = Node(30)
root.right = Node(70)
root.left.left = Node(20)
root.left.right = Node(40)
root.right.left = Node(60)
root.right.right = Node(80)

print(f"Количество узлов: {count_nodes(root)}")
print(f"Максимальная глубина: {Maxdepth(root)- 1}")
print(f"Минимальная глубина: {Mindepth(root) - 1 }")