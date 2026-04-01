import random

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
        tree_str = '\n'.join(lines)
        print(tree_str)
        return tree_str
    
    def save_to_file(self, filename): # СОХРАНЕНИЕ ФАЙЛА
        lines = self._display(self.root)[0]
        tree_str = '\n'.join(lines)
        with open(filename, 'w', encoding='utf-8') as f:
            f.write("Бинарное дерево:\n")
            f.write(tree_str)
            f.write(f"\n\nКоличество узлов: {self.count_nodes()}")
            f.write(f"\nМаксимальная глубина: {self.max_depth()}")
            f.write(f"\nМинимальная глубина: {self.min_depth()}")
        print(f"\nДерево сохранено в файл: {filename}")
    
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
    
    def count_nodes(self):
        return self._count_nodes(self.root)
    
    def _count_nodes(self, node):
        if node is None:
            return 0
        return 1 + self._count_nodes(node.left) + self._count_nodes(node.right)
    
    def max_depth(self):
        return self._max_depth(self.root) - 1
    
    def _max_depth(self, node):
        if not node:
            return 0
        return max(self._max_depth(node.left), self._max_depth(node.right)) + 1
    
    def min_depth(self):
        return self._min_depth(self.root) - 1
    
    def _min_depth(self, node):
        if not node:
            return 0
        if not node.left:
            return self._min_depth(node.right) + 1
        if not node.right:
            return self._min_depth(node.left) + 1
        return min(self._min_depth(node.left), self._min_depth(node.right)) + 1

def generate_random_tree(num_nodes): #РАНДОМ ЧИСЕЛКИ 
    random_numbers = [random.randint(1, 100) for _ in range(num_nodes)]
    tree = BinaryTree(random_numbers[0])
    for num in random_numbers[1:]:
        tree.insert(num)
    return tree, random_numbers

num_nodes = int(input("Введите количество узлов: "))
tree, numbers = generate_random_tree(num_nodes)

print("\nДерево:")
tree.display()

print(f"\nКорень дерева: {tree.root.value}")
print(f"Количество узлов: {tree.count_nodes()}")
print(f"Максимальная глубина: {tree.max_depth()}")
print(f"Минимальная глубина: {tree.min_depth()}")

tree.save_to_file("binary_tree.txt")